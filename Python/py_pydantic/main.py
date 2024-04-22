
# Assuming Pydantic v2

from pydantic import BaseModel

# Define a Pydantic model
class Person(BaseModel):
    name: str
    age: int
    email: str

# Create an instance of the Pydantic model
person_data = {
    "name": "John Doe",
    "age": 30,
    "email": "johndoe@example.com"
}

person = Person(**person_data)

# Access validated data
print(person.model_dump())

# Example input with missing data
invalid_data = {
    "name": "Alice",
    "age": "twenty-five",  # Invalid data type
    "email": "alice@example.com"
}

try:
    person = Person(**invalid_data)
except Exception as e:
    print(f"Validation error: {e}")
