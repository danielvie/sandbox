import { Handle, Position } from '@xyflow/react';

interface Attribute {
  name: string;
}

interface Port {
  name: string;
}

interface PartData {
  name: string;
  attributes: Attribute[];
  ports: Port[];
}

interface PartNodeProps {
  data: {
    part: PartData;
  };
}

export function PartNode({ data }: PartNodeProps) {
  const { part } = data;
  const { name, attributes, ports } = part;

  return (
    <div className="sysml-part-node">
      <div className="sysml-node-header">
        <span>{name}</span>
        <span className="sysml-node-badge">part</span>
      </div>

      {attributes.length > 0 && (
        <div 
          className="sysml-node-compartment" 
          style={{ borderBottom: ports.length > 0 ? '1px solid rgba(255, 255, 255, 0.05)' : 'none' }}
        >
          <div className="sysml-compartment-title">attributes</div>
          {attributes.map((attr) => (
            <div key={attr.name} className="sysml-attribute-item">
              <span style={{ color: '#818cf8' }}>✦</span>
              <span>{attr.name}</span>
            </div>
          ))}
        </div>
      )}

      {ports.length > 0 && (
        <div className="sysml-node-compartment">
          <div className="sysml-compartment-title" style={{ marginBottom: '8px' }}>ports</div>
          <div style={{ display: 'flex', flexDirection: 'column', gap: '8px' }}>
            {ports.map((port) => {
              // Heuristic: check if port is output (source) or input (target)
              const isOut = port.name.toLowerCase().includes('out') || port.name.toLowerCase().includes('output');
              const position = isOut ? Position.Right : Position.Left;

              return (
                <div 
                  key={port.name} 
                  style={{ 
                    position: 'relative', 
                    height: '24px', 
                    display: 'flex', 
                    alignItems: 'center', 
                    justifyContent: isOut ? 'flex-end' : 'flex-start',
                    padding: isOut ? '0 12px 0 0' : '0 0 0 12px'
                  }}
                >
                  <span className={`sysml-port-label ${isOut ? 'sysml-port-label-right' : 'sysml-port-label-left'}`}>
                    {port.name}
                  </span>
                  <Handle
                    type={isOut ? 'source' : 'target'}
                    position={position}
                    id={port.name}
                    className="sysml-handle"
                    style={{ 
                      [isOut ? 'right' : 'left']: '-5px',
                      background: isOut ? '#a855f7' : '#818cf8',
                      top: '50%',
                      transform: 'translateY(-50%)',
                    }}
                  />
                </div>
              );
            })}
          </div>
        </div>
      )}
    </div>
  );
}
