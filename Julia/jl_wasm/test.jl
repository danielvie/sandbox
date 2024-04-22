include("wasm_target.jl")

function add(a::Int32,b::Int32)
    return a+b
end

obj = build_obj(add, Tuple{Int32,Int32})

write("test_add.o", obj)