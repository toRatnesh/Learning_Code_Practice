######################################
#
# References
#    https://www.javatpoint.com/python-tutorial
#    https://docs.python.org/3/tutorial/controlflow.html#defining-functions
#    https://docs.python.org/3/tutorial/controlflow.html#more-on-defining-functions
#
# Functions
#    Function: A block of organized, reusable code that is used to perform a single, related action
#
# Advantages of Functions
#	code reusability
#	redability and modularity using code refactoring
#	can return as many outputs as we want with different arguments
#
# Function
#	Syntax
#	def name_of_function( parameters ):  
#		"""optional function docstring"""  
#		# code block
#
# Calling a Function
#    You can execute it by calling it from another function or directly from the Python prompt
#       name_of_function(args)
#   
# Return Statement
#   The statement return [expression] exits a function, optionally passing back an expression to the caller
#   A return statement with no arguments is the same as return None
#        return num +2
#
# Pass by Reference vs. Value
#   All parameters (arguments) in the Python language are passed by reference
#
# Function Arguments
#	Default arguments
#		It takes as input a default value if no value is supplied for the argument when the function is called
#	Keyword arguments
#		When providing keyword arguments while calling a function, the user uses the parameter label to identify which parameters value it is
#	Required arguments
#		The arguments given to a function while calling in a pre-defined positional sequence are required arguments.
#		The count of required arguments in the method call must be equal to the count of arguments provided while defining the function.
#	Variable-length arguments
#		To pass multiple arguments
#		1. *args -These are Non-Keyword Arguments
#		2. **kwargs - These are Keyword Arguments
#
# Scope and Lifetime of Variables
#	A function's arguments and variables are not accessible outside the defined function. As a result, they only have a local domain.
#	Variables within a function have the same lifespan as the function itself. They are erased with function call stack
#
# Nested Funciton
#   Inner or local or nested function refers to a function defined within another defined function. 
#   Inner functions can access the parameters of the outer scope. 
#   Inner functions are constructed to cover them from the changes that happen outside the function. 
#   Many developers regard this process as encapsulation.
#
# Anonymous Functions
#	Anonymous functions are not declared in the standard manner by using the def keyword
#	Anonymous functions are defined using lambda for more detail check lambda
#
######################################

print('=== Defining Functions ===')
def get_sqaure(num):
    """This function will return square of a number"""
    return num ** 2

print(get_sqaure(4))
print(get_sqaure(1.6))


print('=== Pass by Reference vs. Value ===')
def changeme(changed, not_changed):
    print("Inside function changeme() - before: ")
    print(f'changed {changed}')
    print(f'not_changed {not_changed}')

    changed[2] = 7
    not_changed = [1,2,3,4]	# This would assign new reference in mylist

    print("Inside function changeme() - afer: ")
    print(f'changed {changed}')
    print(f'not_changed {not_changed}')    
    
    return

# Now you can call changeme function
changed = [11, 12, 13]
not_changed = [61, 62, 63]

print("Before changeme() function: ")
print(f'changed {changed}')
print(f'not_changed {not_changed}')

changeme(changed, not_changed)

print("Ater changeme() function: ")
print(f'changed {changed}')
print(f'not_changed {not_changed}')


print('=== Default arguments ===')
def default_arguments(num1, num2=5):
    return num1+num2
print(f'default_arguments(5, 7): {default_arguments(5, 7)}')
print(f'default_arguments(5): {default_arguments(5)}')


print('=== Keyword arguments ===')
def keyword_arguments(num1, num2):
    return num1+num2
print(f'keyword_arguments(5, 7): {keyword_arguments(5, 7)}')
print(f'keyword_arguments(num1=5, num2=7): {keyword_arguments(num1=5, num2=7)}')
print(f'keyword_arguments(num2=5, num1=7): {keyword_arguments(num2=5, num1=7)}')


print('=== Required arguments ===')
def required_arguments(num1, num2):
    return num1+num2
print(f'required_arguments(5, 7): {required_arguments(5, 7)}')
try:
    print(f'required_arguments(5): {required_arguments(5)}')
except TypeError as terr:
    print(f'Error while calling required_arguments(), {terr}')


print('=== Variable-length arguments ===')
def fun_args(*args):
    r_list = []
    for item in args:
        r_list.append(item)
    return r_list
print(f'fun_args("a string", 2.5, False, 3) {fun_args("a string", 2.5, False, 3)}')

def fun_args(**kargs):
    r_list = []
    for k, v in kargs.items():
        r_list.append((k, v))
    return r_list
print(f'fun_args(name="Ramesh",  age=2.5, subject="Physics", mark=98) {fun_args(name="Ramesh",  age=2.5, subject="Physics", mark=98)}')

def fun_args_kargs(*args, **kargs):
    r_list = []
    for item in args:
        r_list.append(item)
    
    for k, v in kargs.items():
        r_list.append((k, v))

    return r_list

print(f'fun_args_kargs("a string", 2.5, False, 3) {fun_args_kargs("a string", 2.5, False, 3)}')
print(f'fun_args_kargs(name="Ramesh",  age=2.5, subject="Physics", mark=98) {fun_args_kargs(name="Ramesh",  age=2.5, subject="Physics", mark=98)}')
print(f'fun_args_kargs("a string", 2.5, False, 3, name="Ramesh",  age=2.5, subject="Physics", mark=98) {fun_args_kargs("a string", 2.5, False, 3, name="Ramesh",  age=2.5, subject="Physics", mark=98)}')

print('=== Nested Funciton ===')
def function_label1():
    msg_l1 = 'funciton_label1'

    def function_label2():
        msg_l2 = 'funciton_label2'

        def function_label3():
            msg_l3 = 'funciton_label3'
            return msg_l3
        
        print(f'function_label3() {function_label3()}')
        return msg_l2

    print(f'function_label2() {function_label2()}')
    return msg_l1

print(f'function_label1() {function_label1()}')


#################
#   END OF FILE
#################

