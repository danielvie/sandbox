import { useState, useEffect, useCallback, useMemo, useRef } from 'react';
import { 
  ReactFlow, 
  MiniMap, 
  Controls, 
  Background, 
  useNodesState, 
  useEdgesState, 
} from '@xyflow/react';
import type {
  Connection as FlowConnection,
  Node,
  Edge
} from '@xyflow/react';
import Editor from '@monaco-editor/react';
import { 
  Plus, 
  Trash2, 
  Edit3, 
  AlertCircle, 
  CheckCircle2, 
  Network, 
} from 'lucide-react';
import { PartNode } from './components/CustomNodes';
import '@xyflow/react/dist/style.css';
import { Agentation } from 'agentation';

// Initial SysML v2 source code
const INITIAL_CODE = `package Example {
    part motor {
        attribute horsepower;
        port fuel_in;
    }
    part tank {
        port fuel_out;
    }
    connection c connect tank.fuel_out to motor.fuel_in;
}`;

interface ParseError {
  message: string;
  line: number;
  column: number;
}

interface Attribute {
  name: string;
  start_byte: number;
  end_byte: number;
  name_start_byte: number;
  name_end_byte: number;
}

interface Port {
  name: string;
  start_byte: number;
  end_byte: number;
  name_start_byte: number;
  name_end_byte: number;
}

interface Part {
  name: string;
  start_line: number;
  end_line: number;
  start_byte: number;
  end_byte: number;
  name_start_byte: number;
  name_end_byte: number;
  body_end_byte: number | null;
  attributes: Attribute[];
  ports: Port[];
}

interface Connection {
  name: string | null;
  source: string;
  target: string;
  start_line: number;
  end_line: number;
  start_byte: number;
  end_byte: number;
}

interface Package {
  name: string;
  start_line: number;
  end_line: number;
  start_byte: number;
  end_byte: number;
  body_end_byte: number | null;
  parts: Part[];
  connections: Connection[];
}

interface SysmlModel {
  packages: Package[];
  errors: ParseError[];
}

export default function App() {
  const [code, setCode] = useState(INITIAL_CODE);
  const [model, setModel] = useState<SysmlModel>({ packages: [], errors: [] });
  const [nodes, setNodes, onNodesChange] = useNodesState<Node>([]);
  const [edges, setEdges, onEdgesChange] = useEdgesState<Edge>([]);
  
  // UI interactive states
  const [selectedNodeId, setSelectedNodeId] = useState<string | null>(null);
  const [newPartName, setNewPartName] = useState('');
  const [newPortName, setNewPortName] = useState('');
  const [renameValue, setRenameValue] = useState('');
  const [isRenaming, setIsRenaming] = useState(false);

  // Vim mode references and state initialized from localStorage
  const editorRef = useRef<any>(null);
  const [editorInstance, setEditorInstance] = useState<any>(null);
  const vimModeRef = useRef<any>(null);
  const [vimEnabled, setVimEnabled] = useState<boolean>(() => {
    const saved = localStorage.getItem('vim_mode_enabled');
    return saved === 'true';
  });

  const [clipboardPermission, setClipboardPermission] = useState<string>('unknown');
  const [lastSyncedClipboard, setLastSyncedClipboard] = useState<string>('');
  const [diagnosticLogs, setDiagnosticLogs] = useState<string[]>([]);

  const addDiagnosticLog = (msg: string) => {
    setDiagnosticLogs(prev => [
      `[${new Date().toLocaleTimeString()}] ${msg}`,
      ...prev.slice(0, 19)
    ]);
  };

  // Sync vimEnabled state to localStorage
  useEffect(() => {
    localStorage.setItem('vim_mode_enabled', String(vimEnabled));
  }, [vimEnabled]);

  // Enable Vim Mode and hook registers for system clipboard writing
  const enableVim = (editor: any) => {
    if (vimModeRef.current) return;
    const statusNode = document.getElementById('vim-status-bar');
    import('monaco-vim').then((module: any) => {
      const { initVimMode, VimMode } = module;
      const Vim = (VimMode as any).Vim;
      if (editor && !vimModeRef.current) {
        vimModeRef.current = initVimMode(editor, statusNode);
        enableVimClipboardWriteHook(Vim);
      }
    }).catch(err => {
      console.error("Failed to load monaco-vim:", err);
    });
  };

  const enableVimClipboardWriteHook = (Vim: any) => {
    try {
      const registerController = Vim.getRegisterController();
      const registersToHook = ['"', '*', '+', 'yank'];
      
      registersToHook.forEach(name => {
        try {
          const register = registerController.getRegister(name);
          if (register) {
            if (!register._originalPushText) {
              register._originalPushText = register.pushText;
            }
            if (!register._originalSetText) {
              register._originalSetText = register.setText;
            }

            register.pushText = function(text: string, multiline: boolean) {
              if (register._originalPushText) {
                register._originalPushText.call(this, text, multiline);
              }
              if (navigator.clipboard && navigator.clipboard.writeText) {
                navigator.clipboard.writeText(text).catch(() => {});
              }
            };

            register.setText = function(text: string, multiline: boolean) {
              if (register._originalSetText) {
                register._originalSetText.call(this, text, multiline);
              }
              if (navigator.clipboard && navigator.clipboard.writeText) {
                navigator.clipboard.writeText(text).catch(() => {});
              }
            };
          }
        } catch (e) {
          console.warn("Could not hook register:", name, e);
        }
      });
    } catch (err) {
      console.warn("Failed to enable write hook:", err);
    }
  };

  // Disable Vim Mode
  const disableVim = () => {
    if (vimModeRef.current) {
      vimModeRef.current.dispose();
      vimModeRef.current = null;
      const statusNode = document.getElementById('vim-status-bar');
      if (statusNode) {
        statusNode.innerHTML = '';
      }
    }
  };

  const checkClipboardPermission = async () => {
    if (!navigator.permissions || !navigator.permissions.query) {
      setClipboardPermission('unsupported');
      return;
    }
    try {
      const result = await navigator.permissions.query({ name: 'clipboard-read' as PermissionName });
      setClipboardPermission(result.state);
      result.onchange = () => {
        setClipboardPermission(result.state);
        addDiagnosticLog(`Permission changed: ${result.state}`);
      };
    } catch (e) {
      setClipboardPermission('error');
      addDiagnosticLog(`Error querying permission: ${String(e)}`);
    }
  };

  // Effect to toggle Vim Mode and synchronize system clipboard -> Vim register
  useEffect(() => {
    let focusListener: (() => void) | null = null;
    let copyListener: (() => void) | null = null;
    let pasteListener: ((e: ClipboardEvent) => void) | null = null;
    let editorFocusListener: any = null;

    if (editorInstance) {
      if (vimEnabled) {
        enableVim(editorInstance);

        const syncClipboardToVim = async () => {
          try {
            await checkClipboardPermission();
            if (navigator.clipboard && navigator.clipboard.readText) {
              const text = await navigator.clipboard.readText();
              import('monaco-vim').then((module: any) => {
                const { VimMode } = module;
                const Vim = (VimMode as any).Vim;
                const registerController = Vim.getRegisterController();
                const registersToSync = ['"', '*', '+', 'yank'];
                
                registersToSync.forEach(name => {
                  try {
                    const register = registerController.getRegister(name);
                    if (register) {
                      if (register._originalSetText) {
                        register._originalSetText.call(register, text, false);
                      } else {
                        register.setText(text, false);
                      }
                    }
                  } catch (_) {}
                });
                setLastSyncedClipboard(text);
                addDiagnosticLog(`Synced clipboard text (len: ${text.length}) to registers.`);
              }).catch((e) => {
                console.warn("[Vim Clipboard] Failed to load monaco-vim for read sync:", e);
                addDiagnosticLog(`Failed to load monaco-vim for read sync: ${e.message}`);
              });
            }
          } catch (err) {
            console.warn("[Vim Clipboard] System clipboard read blocked or unavailable:", err);
            addDiagnosticLog(`Read error/blocked: ${String(err)}`);
          }
        };

        const handlePasteEvent = (e: ClipboardEvent) => {
          if (!editorInstance || !editorInstance.hasTextFocus()) return;
          const text = e.clipboardData?.getData('text');
          if (text) {
            import('monaco-vim').then((module: any) => {
              const { VimMode } = module;
              const Vim = (VimMode as any).Vim;
              const registerController = Vim.getRegisterController();
              const registersToSync = ['"', '*', '+', 'yank'];
              
              registersToSync.forEach(name => {
                try {
                  const register = registerController.getRegister(name);
                  if (register) {
                    if (register._originalSetText) {
                      register._originalSetText.call(register, text, false);
                    } else {
                      register.setText(text, false);
                    }
                  }
                } catch (_) {}
              });
              setLastSyncedClipboard(text);
              addDiagnosticLog(`Intercepted native paste (len: ${text.length}). Synced to registers.`);
            }).catch(() => {});
          }
        };

        focusListener = () => {
          setTimeout(syncClipboardToVim, 100);
        };
        copyListener = () => {
          setTimeout(syncClipboardToVim, 50);
        };
        pasteListener = handlePasteEvent;

        window.addEventListener('focus', focusListener);
        document.addEventListener('copy', copyListener);
        document.addEventListener('paste', pasteListener);
        
        // Listen to Monaco editor focusing
        try {
          editorFocusListener = editorInstance.onDidFocusEditorText(() => {
            setTimeout(syncClipboardToVim, 100);
          });
        } catch (e) {
          console.warn("[Vim Clipboard] Failed to bind editor focus listener:", e);
        }

        setTimeout(syncClipboardToVim, 100);
      } else {
        disableVim();
      }
    }

    return () => {
      disableVim();
      if (focusListener) window.removeEventListener('focus', focusListener);
      if (copyListener) document.removeEventListener('copy', copyListener);
      if (pasteListener) document.removeEventListener('paste', pasteListener);
      if (editorFocusListener) {
        try {
          editorFocusListener.dispose();
        } catch (_) {}
      }
    };
  }, [vimEnabled, editorInstance]);

  const handleEditorDidMount = (editor: any) => {
    editorRef.current = editor;
    (window as any).editor = editor; // Expose for testing/diagnostics
    setEditorInstance(editor);
    if (vimEnabled) {
      enableVim(editor);
    }
  };

  // Custom node types for React Flow
  const nodeTypes = useMemo(() => ({
    part: PartNode
  }), []);

  // Parse code on backend
  const parseCode = async (sourceCode: string) => {
    try {
      const response = await fetch('http://127.0.0.1:3000/api/parse', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ code: sourceCode }),
      });
      if (response.ok) {
        const data: SysmlModel = await response.json();
        setModel(data);
        updateFlowGraph(data);
      }
    } catch (e) {
      console.error('Failed to connect to parser backend:', e);
    }
  };

  // Mutate code on backend
  const mutateCode = async (mutation: any) => {
    try {
      const response = await fetch('http://127.0.0.1:3000/api/mutate', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ code, mutation }),
      });
      if (response.ok) {
        const data = await response.json();
        setCode(data.code);
        setModel(data.model);
        updateFlowGraph(data.model);
        
        // Reset states
        setSelectedNodeId(null);
        setIsRenaming(false);
        setNewPortName('');
        setNewPartName('');
      }
    } catch (e) {
      console.error('Failed to mutate code:', e);
    }
  };

  // Initial parse on load
  useEffect(() => {
    parseCode(INITIAL_CODE);
  }, []);

  // Auto-parse on code change (with slight debounce)
  useEffect(() => {
    const timer = setTimeout(() => {
      parseCode(code);
    }, 600);
    return () => clearTimeout(timer);
  }, [code]);

  // Update React Flow nodes and edges based on parsed model
  const updateFlowGraph = (parsedModel: SysmlModel) => {
    const newNodes: Node[] = [];
    const newEdges: Edge[] = [];

    parsedModel.packages.forEach((pkg) => {
      pkg.parts.forEach((part, index) => {
        newNodes.push({
          id: part.name,
          type: 'part',
          position: { x: 80 + index * 300, y: 150 + (index % 2) * 85 },
          data: { part },
        });
      });

      pkg.connections.forEach((conn, index) => {
        const srcParts = conn.source.split('.');
        const tgtParts = conn.target.split('.');
        newEdges.push({
          id: conn.name || `edge-${index}`,
          source: srcParts[0],
          target: tgtParts[0],
          sourceHandle: srcParts[1] || null,
          targetHandle: tgtParts[1] || null,
          animated: true,
          style: { stroke: '#64748b', strokeWidth: 2 }, // Sober slate edge
        });
      });
    });

    setNodes(newNodes);
    setEdges(newEdges);
  };

  // Find currently selected part data from model
  const selectedPart = useMemo(() => {
    if (!selectedNodeId) return null;
    for (const pkg of model.packages) {
      const part = pkg.parts.find(p => p.name === selectedNodeId);
      if (part) return part;
    }
    return null;
  }, [selectedNodeId, model]);

  // Handle graphical connection drawing
  const onConnect = useCallback((params: FlowConnection) => {
    if (model.packages.length === 0) return;
    const pkg = model.packages[0];
    
    const sourcePath = `${params.source}.${params.sourceHandle}`;
    const targetPath = `${params.target}.${params.targetHandle}`;

    mutateCode({
      type: 'add_connection',
      package_body_end_byte: pkg.body_end_byte || 0,
      source: sourcePath,
      target: targetPath,
    });
  }, [code, model]);

  // Handle clicking a node in React Flow
  const onNodeClick = (_event: any, node: Node) => {
    setSelectedNodeId(node.id);
    setRenameValue(node.id);
    setIsRenaming(false);
  };

  // Add a Part
  const handleAddPart = () => {
    if (!newPartName.trim()) return;
    if (model.packages.length === 0) return;
    const pkg = model.packages[0];

    mutateCode({
      type: 'add_part',
      package_body_end_byte: pkg.body_end_byte || 0,
      name: newPartName.trim(),
    });
  };

  // Add a Port to Selected Part
  const handleAddPort = () => {
    if (!newPortName.trim() || !selectedPart) return;

    mutateCode({
      type: 'add_port',
      part_start_byte: selectedPart.start_byte,
      part_end_byte: selectedPart.end_byte,
      part_body_end_byte: selectedPart.body_end_byte,
      name: newPortName.trim(),
    });
  };

  // Delete Selected Part
  const handleDeletePart = () => {
    if (!selectedPart) return;

    mutateCode({
      type: 'delete',
      start_byte: selectedPart.start_byte,
      end_byte: selectedPart.end_byte,
    });
  };

  // Rename Selected Part
  const handleRenamePart = () => {
    if (!renameValue.trim() || !selectedPart) return;

    mutateCode({
      type: 'rename',
      start_byte: selectedPart.name_start_byte,
      end_byte: selectedPart.name_end_byte,
      value: renameValue.trim(),
    });
  };

  return (
    <>
      <div style={{ height: '100vh', display: 'flex', flexDirection: 'column', overflow: 'hidden', backgroundColor: '#f8fafc' }}>
      
      {/* Sober Light Mode Header */}
      <header className="glass-header" style={{ padding: '12px 24px', display: 'flex', justifyContent: 'space-between', alignItems: 'center', zIndex: 10 }}>
        <div style={{ display: 'flex', alignItems: 'center', gap: '12px' }}>
          <div style={{ background: '#475569', padding: '8px', borderRadius: '8px', display: 'flex' }}>
            <Network size={20} color="#fff" />
          </div>
          <div>
            <h1 style={{ margin: 0, fontSize: '1.25rem', fontWeight: 600, letterSpacing: '0.2px', color: '#0f172a' }}>
              SysML v2 Parser & Graphical Editor
            </h1>
            <span style={{ fontSize: '0.75rem', color: '#64748b' }}>Incremental Tree-sitter & React Flow Light Model</span>
          </div>
        </div>

        {/* Compiler Status Indicator */}
        <div style={{ display: 'flex', alignItems: 'center', gap: '16px' }}>
          {model.errors.length > 0 ? (
            <div style={{ display: 'flex', alignItems: 'center', gap: '8px', background: '#fef2f2', border: '1px solid #fecaca', padding: '6px 12px', borderRadius: '20px', color: '#b91c1c', fontSize: '0.85rem', fontWeight: 500 }}>
              <AlertCircle size={16} />
              <span>{model.errors.length} Syntax Error{model.errors.length > 1 ? 's' : ''}</span>
            </div>
          ) : (
            <div style={{ display: 'flex', alignItems: 'center', gap: '8px', background: '#f0fdf4', border: '1px solid #bbf7d0', padding: '6px 12px', borderRadius: '20px', color: '#15803d', fontSize: '0.85rem', fontWeight: 500 }}>
              <CheckCircle2 size={16} />
              <span>Model Parsed</span>
            </div>
          )}
        </div>
      </header>

      {/* Main Split Pane Layout */}
      <main style={{ flex: 1, display: 'flex', overflow: 'hidden' }}>
        
        {/* Left Side: Code Editor */}
        <section style={{ width: '40%', display: 'flex', flexDirection: 'column', borderRight: '1px solid #e2e8f0', background: '#f8fafc' }}>
          <div style={{ padding: '12px 16px', display: 'flex', justifyContent: 'space-between', alignItems: 'center', background: '#f1f5f9', borderBottom: '1px solid #e2e8f0' }}>
            <span style={{ fontSize: '0.85rem', color: '#475569', fontWeight: 600, textTransform: 'uppercase', letterSpacing: '0.5px' }}>
              SysML v2 Source Code
            </span>
          </div>
          
          <div style={{ flex: 1, padding: '12px', display: 'flex', flexDirection: 'column' }}>
            <div style={{ flex: 1, display: 'flex', flexDirection: 'column', borderRadius: '12px', overflow: 'hidden', border: '1px solid #cbd5e1' }}>
              <div style={{ flex: 1 }}>
                <Editor
                  height="100%"
                  defaultLanguage="rust"
                  theme="light"
                  value={code}
                  onChange={(val) => setCode(val || '')}
                  onMount={handleEditorDidMount}
                  options={{
                    minimap: { enabled: false },
                    fontSize: 14,
                    fontFamily: '"JetBrains Mono", Consolas, "Courier New", monospace',
                    lineNumbers: 'on',
                    scrollBeyondLastLine: false,
                    padding: { top: 12, bottom: 12 },
                    scrollbar: {
                      verticalScrollbarSize: 8,
                      horizontalScrollbarSize: 8
                    }
                  }}
                />
              </div>
              
              {/* Vim Status Bar */}
              <div style={{ 
                display: 'flex', 
                justifyContent: 'space-between', 
                alignItems: 'center', 
                background: '#f8fafc', 
                padding: '8px 16px', 
                borderTop: '1px solid #e2e8f0', 
                fontSize: '0.8rem', 
                color: '#475569',
                minHeight: '36px',
                flexWrap: 'wrap',
                gap: '12px'
              }}>
                <div id="vim-status-bar" style={{ display: 'flex', alignItems: 'center' }}></div>
                
                {vimEnabled && (
                  <div style={{ display: 'flex', alignItems: 'center', gap: '12px', fontSize: '0.75rem' }}>
                    <span style={{ 
                      padding: '2px 6px', 
                      borderRadius: '4px', 
                      background: clipboardPermission === 'granted' ? '#dcfce7' : clipboardPermission === 'prompt' ? '#fef9c3' : '#fee2e2', 
                      color: clipboardPermission === 'granted' ? '#166534' : clipboardPermission === 'prompt' ? '#854d0e' : '#991b1b',
                      fontWeight: 600
                    }}>
                      Clipboard: {clipboardPermission}
                    </span>
                    
                    {clipboardPermission !== 'granted' && (
                      <button 
                        onClick={async () => {
                          try {
                            const text = await navigator.clipboard.readText();
                            addDiagnosticLog(`Clipboard read test successful! Read: "${text.substring(0, 15)}..."`);
                            setClipboardPermission('granted');
                            if (editorRef.current) {
                              editorRef.current.focus();
                            }
                          } catch (e) {
                            addDiagnosticLog(`Read permission request failed: ${String(e)}`);
                            alert(`To enable pasting from outside the browser into Vim mode, please click "Allow" when the browser asks for permission.\n\nError details: ${String(e)}`);
                          }
                        }}
                        style={{
                          padding: '3px 8px',
                          background: '#3b82f6',
                          border: 'none',
                          borderRadius: '4px',
                          cursor: 'pointer',
                          fontWeight: 600,
                          color: '#ffffff'
                        }}
                      >
                        Grant Paste Access
                      </button>
                    )}

                    <button 
                      onClick={async () => {
                        try {
                          const testVal = 'DIAGNOSTIC_SYNC_TEST_' + Math.random().toString(36).substring(7);
                          await navigator.clipboard.writeText(testVal);
                          addDiagnosticLog(`Manually wrote to clipboard: ${testVal}`);
                          const readVal = await navigator.clipboard.readText();
                          addDiagnosticLog(`Read back successfully: ${readVal}`);
                          if (editorRef.current) {
                            editorRef.current.focus();
                          }
                        } catch (e) {
                          addDiagnosticLog(`Diagnostic sync failed: ${String(e)}`);
                        }
                      }}
                      style={{
                        padding: '3px 8px',
                        background: '#e2e8f0',
                        border: 'none',
                        borderRadius: '4px',
                        cursor: 'pointer',
                        fontWeight: 500,
                        color: '#334155'
                      }}
                    >
                      Test Sync
                    </button>
                    <button 
                      onClick={() => {
                        alert(`Diagnostic Logs:\n${diagnosticLogs.join('\n') || 'No logs yet.'}\n\nLast Synced Value:\n${lastSyncedClipboard || '(none)'}`);
                      }}
                      style={{
                        padding: '3px 8px',
                        background: '#cbd5e1',
                        border: 'none',
                        borderRadius: '4px',
                        cursor: 'pointer',
                        fontWeight: 500,
                        color: '#334155'
                      }}
                    >
                      Show Logs
                    </button>
                  </div>
                )}

                <label style={{ display: 'flex', alignItems: 'center', gap: '8px', cursor: 'pointer', userSelect: 'none', color: '#475569', fontSize: '0.85rem', fontWeight: 500, marginLeft: 'auto' }}>
                  <input
                    type="checkbox"
                    checked={vimEnabled}
                    onChange={(e) => setVimEnabled(e.target.checked)}
                    style={{ cursor: 'pointer', width: '14px', height: '14px' }}
                  />
                  <span>Vim Mode</span>
                </label>
              </div>
            </div>
          </div>
          
          {/* Syntax Error Drawer - Light Sober Theme */}
          {model.errors.length > 0 && (
            <div style={{ borderTop: '1px solid #fca5a5', background: '#fef2f2', padding: '16px' }}>
              <div style={{ display: 'flex', alignItems: 'center', gap: '8px', color: '#991b1b', fontWeight: 600, fontSize: '0.9rem', marginBottom: '8px' }}>
                <AlertCircle size={18} />
                <span>Compiler Log</span>
              </div>
              <div style={{ maxHeight: '120px', overflowY: 'auto', display: 'flex', flexDirection: 'column', gap: '6px' }}>
                {model.errors.map((err, idx) => (
                  <div key={idx} style={{ fontSize: '0.8rem', color: '#b91c1c', fontFamily: 'JetBrains Mono', padding: '6px', background: 'rgba(239, 68, 68, 0.04)', borderRadius: '4px' }}>
                    [Line {err.line}, Col {err.column}] {err.message}
                  </div>
                ))}
              </div>
            </div>
          )}
        </section>

        {/* Right Side: Visual Canvas & Panels */}
        <section style={{ width: '60%', display: 'flex', flexDirection: 'column', position: 'relative', background: '#f1f5f9' }}>
          
          {/* Canvas Toolbar overlay */}
          <div className="glass-panel" style={{ position: 'absolute', top: '16px', left: '16px', right: '16px', padding: '12px 16px', zIndex: 5, display: 'flex', gap: '16px', flexWrap: 'wrap', alignItems: 'center', background: 'rgba(255, 255, 255, 0.9)' }}>
            
            {/* Create Part control */}
            <div style={{ display: 'flex', alignItems: 'center', gap: '8px' }}>
              <input
                type="text"
                placeholder="Part name (e.g. pump)"
                value={newPartName}
                onChange={(e) => setNewPartName(e.target.value)}
                style={{ background: '#ffffff', border: '1px solid #cbd5e1', padding: '6px 12px', borderRadius: '6px', fontSize: '0.85rem', color: '#0f172a' }}
              />
              <button 
                onClick={handleAddPart}
                style={{ display: 'flex', alignItems: 'center', gap: '6px', background: '#475569', color: '#fff', border: 'none', padding: '6px 12px', borderRadius: '6px', fontSize: '0.85rem', cursor: 'pointer', fontWeight: 500 }}
              >
                <Plus size={16} />
                <span>Add Part</span>
              </button>
            </div>

            <div style={{ height: '20px', width: '1px', background: '#cbd5e1' }} />

            {/* Selected item controls */}
            {selectedPart ? (
              <div style={{ display: 'flex', alignItems: 'center', gap: '12px', flexWrap: 'wrap' }}>
                <span style={{ fontSize: '0.85rem', color: '#334155', fontWeight: 500 }}>
                  Selected: <code style={{ background: 'rgba(71, 85, 105, 0.1)', padding: '2px 6px', borderRadius: '4px', color: '#475569' }}>{selectedPart.name}</code>
                </span>

                {/* Add Port */}
                <div style={{ display: 'flex', alignItems: 'center', gap: '8px' }}>
                  <input
                    type="text"
                    placeholder="Port name"
                    value={newPortName}
                    onChange={(e) => setNewPortName(e.target.value)}
                    style={{ background: '#ffffff', border: '1px solid #cbd5e1', padding: '6px 12px', borderRadius: '6px', fontSize: '0.85rem', color: '#0f172a', width: '100px' }}
                  />
                  <button 
                    onClick={handleAddPort}
                    style={{ display: 'flex', alignItems: 'center', gap: '6px', background: 'rgba(71, 85, 105, 0.08)', border: '1px solid rgba(71, 85, 105, 0.2)', color: '#475569', padding: '6px 12px', borderRadius: '6px', fontSize: '0.85rem', cursor: 'pointer', fontWeight: 500 }}
                  >
                    <Plus size={16} />
                    <span>Port</span>
                  </button>
                </div>

                {/* Rename */}
                {isRenaming ? (
                  <div style={{ display: 'flex', alignItems: 'center', gap: '8px' }}>
                    <input
                      type="text"
                      value={renameValue}
                      onChange={(e) => setRenameValue(e.target.value)}
                      style={{ background: '#ffffff', border: '1px solid #cbd5e1', padding: '6px 12px', borderRadius: '6px', fontSize: '0.85rem', color: '#0f172a', width: '120px' }}
                    />
                    <button 
                      onClick={handleRenamePart}
                      style={{ background: '#16a34a', color: '#fff', border: 'none', padding: '6px 12px', borderRadius: '6px', fontSize: '0.85rem', cursor: 'pointer', fontWeight: 500 }}
                    >
                      Save
                    </button>
                    <button 
                      onClick={() => setIsRenaming(false)}
                      style={{ background: '#dc2626', color: '#fff', border: 'none', padding: '6px 12px', borderRadius: '6px', fontSize: '0.85rem', cursor: 'pointer', fontWeight: 500 }}
                    >
                      Cancel
                    </button>
                  </div>
                ) : (
                  <button 
                    onClick={() => setIsRenaming(true)}
                    style={{ display: 'flex', alignItems: 'center', gap: '6px', background: '#ffffff', border: '1px solid #cbd5e1', color: '#475569', padding: '6px 12px', borderRadius: '6px', fontSize: '0.85rem', cursor: 'pointer' }}
                  >
                    <Edit3 size={14} />
                    <span>Rename</span>
                  </button>
                )}

                {/* Delete */}
                <button 
                  onClick={handleDeletePart}
                  style={{ display: 'flex', alignItems: 'center', gap: '6px', background: '#fee2e2', border: '1px solid #fecaca', color: '#dc2626', padding: '6px 12px', borderRadius: '6px', fontSize: '0.85rem', cursor: 'pointer', fontWeight: 500 }}
                >
                  <Trash2 size={14} />
                  <span>Delete</span>
                </button>
              </div>
            ) : (
              <span style={{ fontSize: '0.85rem', color: '#64748b' }}>
                Select a part node to rename, add ports, or delete. Drag lines between ports to connect.
              </span>
            )}
          </div>

          {/* Interactive React Flow Canvas */}
          <div style={{ flex: 1, height: '100%' }}>
            <ReactFlow
              nodes={nodes}
              edges={edges}
              onNodesChange={onNodesChange}
              onEdgesChange={onEdgesChange}
              onConnect={onConnect}
              onNodeClick={onNodeClick}
              onPaneClick={() => setSelectedNodeId(null)}
              nodeTypes={nodeTypes}
              fitView
            >
              <Background color="#cbd5e1" gap={16} size={1} />
              <Controls style={{ background: '#ffffff', border: '1px solid rgba(15, 23, 42, 0.08)', borderRadius: '8px', color: '#0f172a' }} />
              <MiniMap 
                style={{ background: '#ffffff', border: '1px solid rgba(15, 23, 42, 0.08)', borderRadius: '8px' }}
                nodeColor={() => 'rgba(100, 116, 139, 0.15)'}
                maskColor="rgba(255, 255, 255, 0.6)"
              />
            </ReactFlow>
          </div>
        </section>
      </main>
    </div>
    {import.meta.env.DEV && <Agentation />}
    </>
  );
}
