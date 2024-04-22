""" bla """

from returns.result import safe


class Maybe:
    """descr"""

    def __init__(self, value):
        self.value = value

    def bind(self, func):
        """descr"""
        if self.value is not None:
            result = func(self.value)
            if isinstance(result, Maybe):
                return result

            return Maybe(result)

        return self

    def __repr__(self):
        return f"Maybe({self.value})"


def save_divide(x, y):
    """descr"""
    if y == 0:
        return None

    return x / y

result = Maybe(10).bind(lambda x: Maybe(4).bind(lab))

# define a function that returns an Either monad
@safe
def divide(a, b):
    """bla"""
    return a / b


# use the Either monad to safely divide two numbers
result1 = divide(10, 1)
result2 = divide(10, 0)

# check if the result is a value or an error
if isinstance(result1, Exception):
    print("Error occurred:", result2.value_or(0))
else:
    print("The result is:", result2)
print("sdfasdf")
