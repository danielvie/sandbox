""" bla """


def get_prime(n):
    """check if the number if prime"""

    # initializing array of trues
    v = [
        True,
    ] * n

    ni = 2

    while ni < n:
        # return value of prime number
        yield ni

        # mark multiples as False
        idx = ni + ni - 1
        while idx < n:
            v[idx] = False
            idx += ni

        # goto next True in the table
        ni += 1
        while v[ni - 1] is False and ni < n:
            ni += 1

    return True


for p in get_prime(1_000_000):
    print(p)
