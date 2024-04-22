// index.js
import init from "./pkg/rs_cpp_wasm.js";
// import init from "./pkg/rs_cpp_wasm";

init().then(wasm => {
    console.log('estou aqui')
    console.log(wasm)
    const result = wasm.rust_add(3, 4);
    console.log("Result:", result);
})


// fetch('./pkg/rs_cpp_wasm_bg.wasm').then(response => response.arrayBuffer())
//     // .then(bytes => WebAssembly.instantiate(bytes, { env: cppModule }))
//     .then(bytes => WebAssembly.instantiate(bytes, {}))
//     .then(result => {
//         // const rustModule = result.instance.exports;
//         // rustModule.call_cpp_function();
//         console.log(result)
//     });
