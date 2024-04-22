from libc.stdint cimport uint64_t

def fibonacci(n):
    if n <= 1:
        return n
        
    cdef uint64_t a = 0
    cdef uint64_t b = 1
    cdef uint64_t temp

    for _ in range(2, n+1):
        temp = b
        b += a
        a = temp
        
    return b