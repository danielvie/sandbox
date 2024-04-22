"use client";

import { useEffect, useState } from "react";
import { loadWasm } from "../lib/loadWasm";

export default function Home() {
  const [addResult, setAddResult] = useState(null);
  const [fibResult, setFibResult] = useState(null);
  const [fib, setFib] = useState(11);

  useEffect(() => {
    async function loadAndRunWasm() {
      const wasmExports = (await loadWasm()) as {
        add: (a: number, b: number) => number;
        fibonacci: (n: number) => number;
      };

      setAddResult(wasmExports.add(16, 67));
      setFibResult(wasmExports.fibonacci(11));
    }

    loadAndRunWasm();
  }, []);

  async function go() {
    const fib = parseInt(
      (document.getElementById("fib") as HTMLInputElement).value
    );

    const wasmExports = (await loadWasm()) as {
      add: (a: number, b: number) => number;
      fibonacci: (n: number) => number;
    };

    setFibResult(wasmExports.fibonacci(fib));

    // fib 34 :: 3524578
    console.log(" asdfasdfasdf " + fib);
  }

  return (
    <main className="flex min-h-screen flex-col items-center justify-between p-24">
      <div>
        <span>fib: </span>
        <input id="fib" type="text" className="mb-4 border-2 border-black" />
        <button onClick={go}>go</button>

        <div>Result of add(16,67): {addResult}</div>
        <div>Result of fibonacci(11): {fibResult}</div>
      </div>
    </main>
  );
}
