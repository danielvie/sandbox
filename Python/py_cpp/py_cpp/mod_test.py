"""python example"""

import engine
import extension

if __name__ == "__main__":

    v = engine.get()
    v2 = extension.get()
    add = engine.add(1, 2)
    print(f"entrei, get: {v}")
    print(f"entrei, add(1,2): {add}")
    print("entrei, vetor():")
    print(engine.vetor())
    print(engine.vetor_n(1000))
