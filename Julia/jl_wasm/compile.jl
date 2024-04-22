using Wasm

# load the Julia module
include("example.jl")

# compile the Julia function to Wasm
wasm_module = wasm_module(add_numbers, Tuple(Int, Int), Int)

# Save the Wasm module to a file
wasm_file = "example.wasm"
write(wasm_file, wasm_module)