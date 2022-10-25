######################################
# 
# References:
#     https://www.javatpoint.com/python-exception-handling
#     https://docs.python.org/3/tutorial/errors.html
# 
# Python Exceptions
#     When a Python program meets an error, it stops the execution of the rest of the program. 
#     An error in Python might be either an error in the syntax of an expression or a Python exception.
# 
# What is an Exception?
#     When a Python code comes across a condition it can't handle, it raises an exception. 
#     An object in Python that describes an error is called an exception.
#     When a Python code throws an exception, it has two options: handle the exception immediately or stop and quit.
# 
# Exceptions versus Syntax Errors
#     When the interpreter identifies a statement that has an error, syntax errors occur.
#     When syntactically valid Python code produces an error, this is known as exception error. 
#     Python displays information about the sort of exception error that occurred.
# 
# Try and Except Statement - Catching Exceptions
#     The try clause contains the code that can raise an exception, while the except clause contains the code lines that handle the exception. 
# 
# How to Raise an Exception
#     We can intentionally raise an exception using the raise keyword. We can use a customized exception in conjunction with the statement.
# 
# Try with Else Clause
#     Python also supports the else clause, which should come after every except clause, in the try, and except blocks. 
#     Only when the try clause fails to throw an exception the Python interpreter goes on to the else block.
# 
# Finally Keyword in Python
#     The finally is always used after the try-except block. 
#     It is executed after the try block has terminated normally or after the try block has terminated for some other reason.
# 
# Assertions in Python
#     The simplest way to understand an assertion is to compare it with an if-then condition. 
#     An exception is thrown if the outcome is false when an expression is evaluated.
#     
#     The assert Statement
#     Python examines the adjacent expression, preferably true when it finds an assert statement.
#     Python throws an AssertionError exception if the result of the expression is false.
#     syntax
#         assert Expressions[, Argument]
#     Python uses ArgumentException, if the assertion fails, as the argument for the AssertionError.
#     We can use the try-except clause to catch and handle AssertionError exceptions.
# 
# User-Defined Exceptions
#     By inheriting classes from the typical built-in exceptions, Python also lets us design our customized exceptions.
# 
# Summary:
#     Syntax of try, except, else, and finally clauses.
#     
#     try:  
#         # Code block
#         # These statements are those which can probably have some error
#     except:  
#         # This block is optional
#         # If the try block encounters an exception, this block will handle it
#     else:  
#         # If there is no exception, this code block will be executed by the Python interpreter
#     finally:  
#         # Python interpreter will always execute this code
# 
######################################

print("=== Exceptions versus Syntax Errors ===")
str1 = "Python exceptions and syntax error"
for s in str1:
    #if S != o   # SyntaxError: expected ':'
    #if s != o: # NameError: name 'o' is not defined
        pass


print("=== Try and Except Statement ===")
arr = ["try", "exception", "to", "catch", "exception"]
try:
    for i in range(6):
        print(arr[i])
except:
    print("Index out of range")


print("=== How to Raise an Exception ===")
num = 14
try:
    if 0 != num % 5:
        raise Exception(f"Number {num} is not divisble by 5")
except Exception as exp:
    print(exp)


print("=== Try with Else Clause/Finally Keyword ===")
def mydiv(num):
    try:
        if 0 != num:
            res = 15/num
        else:
            raise Exception(f"Division with {num} not possible")
    except Exception as exp:
        print(exp)
    else:
        print(f"15/{num} is {res}")
    finally:
        print("This is final clause")

mydiv(3)
mydiv(5)
mydiv(0)


print("=== Assertions ===")
def factorial(num):
    assert(0 < num), "-ve numbers are not accpted to calculate factorial"
    res = 1
    while 1 != num:
        res = res * num;
        num = num -1
    return res

print(f"Factorial of 4 is {factorial(4)}")
#print(f"Factorial of 4 is {factorial(-1)}")


print("=== User-Defined Exceptions ===")
class MyException(Exception):
    def __init__(self, arg):
        self.arg = arg

try:
    raise MyException("This is my exception")
except MyException as exp:
    print(exp)

##################
#   END OF FILE
##################        
