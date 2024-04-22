async function loadWasm() {
  try {
    const response = await fetch("/math.wasm");
    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }
    const buffer = await response.arrayBuffer();
    const wasmModule = await WebAssembly.instantiate(buffer, {
      env: {
        print: (result) => {
          console.log(`The result is ${result}`);
        },
      },
    });
    return wasmModule.instance.exports;
  } catch (error) {
    console.error("Error loading wasm module:", error);
    throw error; // Re-throw to ensure it gets picked up in the useEffect hook or other calling location
  }
}

export { loadWasm };
