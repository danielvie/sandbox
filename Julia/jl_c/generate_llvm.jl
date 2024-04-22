# File: generate_llvm.jl

# Include the function definition
include("my_julia_function.jl")

# Generate lowered code for the function
lowered_code = Base.@code_lowered my_julia_function(Float64)

# Generate typed code for the function
typed_code = Base.@code_typed my_julia_function(Float64)

# Extract LLVM IR from the typed code
llvm_ir = typed_code.code

# Save the LLVM IR code to a file
llvm_file_path = "my_julia_function.ll"
open(llvm_file_path, "w") do file
    print(file, llvm_ir)
end
