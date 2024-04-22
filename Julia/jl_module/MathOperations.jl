module MathOperations

export sum_numbers, multiply_numbers

"""
    sum_numbers(a, b)

Compute the sum of two numbers.
"""
function sum_numbers(a::Number, b::Number)
    return a + b
end

"""
    multiply_numbers(a, b)

Compute the product of two numbers.
"""
function multiply_numbers(a::Number, b::Number)
    return a * b
end

end # module