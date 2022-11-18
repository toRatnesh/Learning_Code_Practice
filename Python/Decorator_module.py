##################
#
#   This is a sample module for decorator functions used to understand decorator example
#
##################

def decorator_fun(func):
    def inner_decorator_fun():
        func()
        func()
    return inner_decorator_fun

# To accept decorator function args we need to modify wrapper fun to accept args
def decorator_fun_with_args(func):
    def inner_decorator_fun(*args, **kwargs):
        func(*args, **kwargs)
        func(*args, **kwargs)
    return inner_decorator_fun

def decorator_fun_retval(func):
    def inner_decorator_fun(*args, **kwargs):
        retval = func(*args, **kwargs)
        return retval
    return inner_decorator_fun

def decorator1(func):
    def inner_fun(*args, **kwargs):
        func(*args, **kwargs)
    return inner_fun

def decorator2(func):
    def inner_fun(*args, **kwargs):
        func(*args, **kwargs)
    return inner_fun

def decorator_with_args(num):
    def decorator(func):
        def inner_fun(*args, **kwargs):
            retval = 0
            for _ in range(num):
                retval += func(*args, **kwargs)
            return retval
        return inner_fun
    return decorator

import functools
def StatefullDecoratorForCount(func):
    @functools.wraps(func)
    def wrapper_count_calls(*args, **kwargs):
        wrapper_count_calls.num_calls += 1
        print(f"Call {wrapper_count_calls.num_calls} of {func.__name__!r}")
        return func(*args, **kwargs)
    wrapper_count_calls.num_calls = 0
    return wrapper_count_calls

##################
#   END OF FILE
##################

