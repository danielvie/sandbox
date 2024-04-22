#include <julia.h>

#ifdef __cplusplus
extern "C" {
#endif

// Define the C function to compute the sum
double my_sum(double *array, int length) {
    double result = 0.0;
    for (int i = 0; i < length; i++) {
        result += array[i]*8;
    }
    return result + 30;
}

double my_sum_plus_12(double *array, int length) {
    double result = 0.0;
    for (int i = 0; i < length; i++) {
        result += array[i];
    }
    return result + 12.0;
}

// Define the Julia entry point for the C function
void jl_init_my_sum(void) {
    // Create a Julia function object for my_sum
    jl_eval_string("const MySum = cfunction(my_sum, Float64, (Ptr{Float64}, Csize_t))");

    // Define the Julia function sum(array) that calls MySum
    jl_eval_string("sum(array::Vector{Float64}) = ccall(MySum, Float64, (Ptr{Float64}, Csize_t), array, length(array))");
}

void jl_init_my_sum_plus_12(void) {
    // Create a Julia function object for my_sum_plus_12
    jl_eval_string("const MySumPlus12 = cfunction(my_sum_plus_12, Float64, (Ptr{Float64}, Csize_t))");

    // Define the Julia function sum_plus_12(array) that calls MySumPlus12
    jl_eval_string("sum_plus_12(array::Vector{Float64}) = ccall(MySumPlus12, Float64, (Ptr{Float64}, Csize_t), array, length(array))");
}

#ifdef __cplusplus
}
#endif
