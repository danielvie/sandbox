from time import time

def is_prime(n):
    fim = int(n/2) + 1

    for i in range(2, fim):
        if n%i == 0:
            return False

def is_prime3(n):
    fim = int(n/2) + 1

    if n == 2:
        return True

    if n % 2 == 0:
        return False
    
    i = 3
    while i < fim:
        if n%i == 0:
            return False

        i += 2
            
    return True


def is_prime2(n, P):
    fim = int(n/2) + 1

    # return known responses
    if n == 2:
        return True

    if n%2 == 0:
        return False

    # first test list of primes
    for p in P:
        if n%p == 0:
            return False

    # then test rest of numbers starting from the last prime
    if len(P):
        ini = P[-1]
    else: 
        ini = 2

    # for i in range(ini, fim):
    #     if n%i == 0:
    #         return False


    i = ini
    while i < fim:
        if n%i == 0:
            return False
        i += 2

    return True

def get_prime(init = 2, end = 1_000):
    
    # test vector
    T = [True,]*end

    # run loop to skip range init
    n = 2
    while n < init:
        # mark `False` on numbers and increment to next
        idx = n + n - 1
        while(idx < end):
            T[idx] = False
            idx += n
        n += 1
        
        # skip numbers that are false
        while T[n-1] == False and n < end:
            n += 1

    # run loop returning values
    while n < end:
        # return value after init
        yield n
        
        # mark `False` on numbers and increment to next
        idx = n + n - 1
        while(idx < end):
            T[idx] = False
            idx += n
        n += 1
        
        # skip numbers that are false
        while T[n-1] == False and n < end:
            n += 1

def show_prime1(MAX_NUMBER = 1_000, verb = 10_000):
    ini = time()
    tmark_ = ini
    

    P = []
    for i in range(2,MAX_NUMBER):
        if is_prime3(i):
            P.append(i)
        
        if i % verb == 0:
            tmark = time()
            print(f'alive: {i} of {fim}, iter_time: {tmark - tmark_: .3f} s')
            tmark_ = tmark

    dt = time() - ini
    
    return P,dt
    

def show_prime2(init, end = 1_000):
    ini = time()
    cont = 0
    P = []
    for p in get_prime(init, end):
        P.append(p)
        cont += 1

    dt = time() - ini
    
    return P,dt
    

fim = 10_000

# P1,dt1 = show_prime1(fim, verb=10_000)
# P2,dt2 = show_prime2(2, fim)
P2,dt2 = show_prime2(1, 999_999)

# print(f'number of primes found: {len(P1)}')
# print(f"time 1: {dt1: .3f} s")

print(f'number of primes found: {len(P2)}')
print(f"time 2: {dt2: .3f} s")

# print(P1)
# print(P2)
