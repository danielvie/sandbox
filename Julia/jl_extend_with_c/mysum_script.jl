# mysum_script.jl

import Libdl

# Load the shared library
const libpath = "/Users/danielvieira/Sandbox/julia/jl_extend_with_c/mysum.so"

try
    Libdl.dlopen(libpath, 2)  # Use the integer value 2 for RTLD_GLOBAL

    # Initialize the custom sum function
    ccall(:jl_init_my_sum, Cvoid, ())
    ccall(:jl_init_my_sum_plus_12, Cvoid, ())
    
    # Test the custom sum function
    data = [1.0, 2.0, 3.0, 4.0]
    result = sum(data)
    # result = sum_plus_12(data)
    println("Custom sum result: $result")
catch e
    println("Error loading the shared library: $e")
end
