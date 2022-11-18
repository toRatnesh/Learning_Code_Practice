#######################
#
#   References:
#       https://www.javatpoint.com/python-decorator
#       https://docs.python.org/3/library/functions.html#classmethod
#       https://docs.python.org/3/library/functions.html#staticmethod
#       https://docs.python.org/3/library/functions.html#property
#
#
#   Decorator
#       Decorators provide the flexibility to wrap another function to expand the working of wrapped function, without permanently modifying it.
#       It is also called meta programming where a part of the program attempts to change another part of program at compile time.
#
#   Higher order function
#       A function that accepts other function as an argument
#
#   Decorating functions with parameters
#
#   Syntactic Decorator
#       use decorator in easy way with @symbol (also called "pie" syntax)
#
#   Reusing Decorator
#       We can reuse the decorator as well by recalling that decorator function.       
#
#   Python Decorator with Argument
#       write inner funciton to accept arguments
#
#   Returning Values from Decorated Functions
#       decorator funciton can return value
#
#   Fancy Decorators
#
#   Class Decorators
#   	there are built-in decorators like @classmethod, @staticmethod and @property in Python
#   	@classmethod and @staticmethod define methods inside class that is not connected to any other instance of a class
#   	@property is generally used to modify the getters and setters of a class attributes
#	
#   Nesting Decorators
#	    We can use multiple decorators by using them on top of each other.
#
#   Decorator with Arguments
#   	decorator can be executed several times according to the given value of the argument
#
#   Decorator with Arguments
#	    decorator can be executed several times according to the given value of the argument
#	
#   Stateful Decorators
#	    used to keep track of the decorator state
#
#   Classes as Decorators
#   	create a class that contains __init__() and take func as an argument
#   	The class needs to be callable so that it can stand in for the decorated function
#   	To making a class callable, implement the special __call__() method
#
#######################

print(f"=== Decorating functions with parameters ===")
def divide(x, y):
    return x/y
def outerDivision(fun):
    def innerDivision(x, y):
        if x < y:
            x,y = y,x
            return fun(x,y)
    return  innerDivision

divide1 = outerDivision(divide)
print(f"divide1(2,4) {divide1(2,4)}")
print(f"divide1(9,3) {divide1(9,3)}")
print(f"divide1(6,6) {divide1(6,6)}")

print(f"=== Syntactic Decorator ===")
def outer_div(func):
    def inner(x,y):
        if(x<y):
            x,y = y,x
            return func(x,y)
    return inner
# syntax of generator  
@outer_div
def divide(x,y):
    return x/y

print(f"divide(2,4) {divide(2,4)}")
print(f"divide(9,3) {divide(9,3)}")
print(f"divide(6,6) {divide(6,6)}")

print(f"=== Reusing Decorator ===")
from Decorator_module import decorator_fun
@decorator_fun
def afun():
    print(f"Learning reusing decorator using module")

print(f"=== Python Decorator with Argument ===")
from Decorator_module import decorator_fun_with_args
@decorator_fun_with_args
def fun_with_args(msg):
    print(f"Learning {msg}")
fun_with_args("Python Decorator with Arguments")

print(f"=== Returning Values from Decorated Functions ===")
from Decorator_module import decorator_fun_retval
@decorator_fun_retval
def fun_ret_val(val1, val2):
    return val1 + val2
print(f"fun_ret_val(5,6) {fun_ret_val(5,6)}")

print(f"=== Fancy Decorators ===")
print(f"=== Class Decorators ===")
class Student:
    school = "This is school name" # this is class variable
    def __init__(self, name, subject):
        self._name = name
        self._subject = subject
    @property
    def name(self):
        return self._name() if callable(self._name) else self._name
    @property
    def subject(self):
        return self._subject() if callable(self._subject) else self._subject
    @staticmethod
    def a_static_method(msg):
        print(f"msg {msg}")
    @classmethod
    def a_science_student(cls, name):
        return cls(name, "science")

    def display(self):
        print(f"student name: {self._name} subject {self._subject}")

st1 = Student("student-1", 21)
st2 = Student.a_science_student("student-2")
st1.display()
st2.display()
print(f"student name: {st1.name} subject {st1.subject}")
print(f"student name: {st2.name} subject {st2.subject}")
Student.a_science_student("This is a static method")
print(f"Student.school {Student.school}")
print(f"st1.school {st1.school}")
print(f"st2.school {st2.school}")

print(f"=== Nesting Decorators ===")
from Decorator_module import decorator1, decorator2
@decorator1
@decorator2
def using_nested_decorator(val):
    print(f"Using nested decorator {val}")
using_nested_decorator(5)

print(f"=== Decorator with Arguments ===")
from Decorator_module import decorator_with_args
@decorator_with_args(5)
def use_decorator_with_args(msg, val):
    print(f"msg {msg}")
    return val+1

retval = use_decorator_with_args("Learning decorator with args", 7)
print(f"retval {retval}")
print(f"use_decorator_with_args('Learning decorator with args', 7) {use_decorator_with_args('Learning decorator with args', 7)}")

print(f"=== Stateful Decorators ===")
from Decorator_module import StatefullDecoratorForCount
@StatefullDecoratorForCount
def say_hello():
    print("Say Hello")
@StatefullDecoratorForCount
def say_hi():
    print("Say Hi !")  

say_hello()
say_hello()
say_hi()
say_hello()
say_hi()

print(f"=== Classes as Decorators ===")
import functools

class DecoratorClassForCount:
    def __init__(self, func):
        functools.update_wrapper(self, func)
        self._func = func
        self._num_calls = 0
    def __call__(self, *args, **kwargs):
        self._num_calls += 1
        print(f"Call{self._num_calls} of {self._func.__name__!r}")
        return self._func(*args, **kwargs)  

@DecoratorClassForCount
def say_hello():
    print("Say Hello")  

@DecoratorClassForCount
def say_hi():
    print("Say Hi !")

say_hello()
say_hello()
say_hi()
say_hello()
say_hi()


##################
#   END OF FILE
##################

