# Define a custom type called "Person"
struct Person
    name::String
    age::Int
end

∑(a, b) = a + b
∏(a, b) = a * b

# Create an object of type Person
person1 = Person("John Doe", 30)

function add_numbers(a, b)
    c = a + b*2
    return c
end


# Access fields of the object
a = 28
b = 12

# Prints
println("Name: ", person1.name)
println("Age: ", person1.age)
println("∑($(a),$(b)): ", ∑(a,b))
println("∏($(a),$(b)): ", ∏(a,b))

add_numbers(9, 3)
