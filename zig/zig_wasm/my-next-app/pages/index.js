import { useEffect, useState } from 'react';
import loadWasm from '../lib/loadWasm';

function HomePage() {
  const [addResult, setAddResult] = useState(null);
  const [fibResult, setFibResult] = useState(null);

  useEffect(() => {
    async function loadAndRunWasm() {
      try {
        const wasmExports = await loadWasm();
        setAddResult(wasmExports.add(16, 67));
        setFibResult(wasmExports.fibonacci(11));
      } catch (error) {
        console.error("Error in loading and running wasm:", error);
      }
    }
  
    loadAndRunWasm();
  }, []);

  return (
    <div>
        kkkkhhhh asdfasdf
      <div>Result of add(16,67): {addResult}</div>
      <div>Result of fibonacci(11): {fibResult}</div>
    </div>
  );
}

export default HomePage;
