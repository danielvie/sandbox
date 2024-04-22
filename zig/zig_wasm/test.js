const fs = require('fs');
const source = fs.readFileSync("./math.wasm");
const typedArray = new Uint8Array(source);

WebAssembly.instantiate(typedArray, {
  env: {
    print: (result) => { console.log(`The result is ${result}`); }
  }}).then(result => {
  const add = result.instance.exports.add;
  const fib = result.instance.exports.fibonacci;
  const soma = add(166, 28);
  const fibo = fib(11);
  console.log(soma)
  console.log(fibo)
});