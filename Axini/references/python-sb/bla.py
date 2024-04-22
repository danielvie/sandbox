import logging
from typing import Callable, Any

def with_logging(func: Callable[..., Any]) -> Callable[..., Any]:
    def wrapper(*args: Any, **kwargs: Any) -> Any:
        logging.info(f"Calling {func.__name__}")
        value = func(*args, **kwargs)
        logging.info(f"Finished calling {func.__name__}")
        return value

    return wrapper

@with_logging
def bla():
    logging.warning('bla')

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    logging.warning('asdfasdfasdf')
    logging.info('info')
    
    bla()