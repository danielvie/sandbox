import fibonacci 
import main
import time

N = 5_000_000

ini = time.perf_counter()

x1 = -1
for i in range(N):
    x1 = fibonacci.fibonacci(90)
    
fim = time.perf_counter()

print(f'tempo cython, fib()[{N}]: {x1} :: {fim - ini:.4f} segundos')

ini = time.perf_counter()

x2 = -1
for i in range(N):
    x2 = main.fibonacci(90)

fim = time.perf_counter()


print(f'tempo python, fib()[{N}]: {x2} :: {fim - ini:.4f} segundos')









# python test.py
# tempo cython, fib()[5000000]: 2880067194370816120 :: 1.9282 segundos
# tempo python, fib()[5000000]: 2880067194370816120 :: 12.9541 segundos