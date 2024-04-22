"""test script for the extension module"""

import extension

v = extension.get()
add = extension.add(1, 2)
print(f"entrei, get: {v}")
print(f"entrei, add(1,2): {add}")
print("entrei, vetor():")
print(extension.vetor())
print(extension.vetor_n(1000))
