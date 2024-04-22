
# def soma(a, b):
#     return a + b

# fun = lambda a, b: a + b


# def multiplier(n):
#     return lambda x : x * n

# retorno = multiplier(5)

# def multiplicador(n):
#     vezesN = lambda a : a * n
#     return vezesN

# print(soma(1, 5))
# print(fun(1, 5))

# print(retorno(4))

# m = multiplicador(10)
# print(m(6))


from functools import reduce

# print(reduce(lambda a, b : a if a > b else b, [42, 123, 42, 3, 50]))

# fun = lambda a, b : a * b
# vet = [1, 2, 3, 4]

fun = lambda a, b : a if a > b else b
vet = [42, 123, 42, 3, 50]

funfilter = lambda x: x % 2 == 0, range(10, 30)
vetfilter = range(10, 30)

print(reduce(fun, vet))

even_numbers = filter(lambda x: x % 4 == 0, range(10, 30))
print(list(even_numbers))


v = [1, 2, 3, 4, 5]

print(list(map(lambda x: x * 10, v)))

# reduce
# filter
# map