########################################
# 
# References
# 	https://www.javatpoint.com/python-variables
# 
# Variables
# 	Variables are nothing but reserved memory locations to store values
# 	Based on the data type of a variable, the interpreter allocates memory and decides what can be stored in the reserved memory
# 
# 	We don't need to specify the type of variable because Python is a infer language and smart enough to get variable type
# 	Variable names can be a group of both the letters and digits, but they have to begin with a letter or an underscore
# 	It is recommended to use lowercase letters for the variable name
# 	Rahul and rahul both are two different variables, also known as an identifier
# 
# Variable Naming
# 	Variables are the example of identifiers. 
# 	An Identifier is used to identify the literals used in the program. 
# 	The rules to name an identifier are given below.
# 		The first character of the variable must be an alphabet or underscore ( _ ).
# 		All the characters except the first character may be an alphabet of lower-case(a-z), upper-case (A-Z), underscore, or digit (0-9).
# 		Identifier name must not contain any white-space, or special character (!, @, #, %, ^, &, *).
# 		Identifier name must not be similar to any keyword defined in the language.
# 		Identifier names are case sensitive; for example, my name, and MyName is not the same.
# 		Identifier can be of any length.
# 	valid identifiers: a123, _n, n_9, etc
# 	invalid identifiers: 1a, n%4, n 9, etc
# 
# Declaring Variable and Assigning Values
# 	When we assign any value to the variable, that variable is declared automatically.
# 	The equal (=) operator is used to assign value to a variable.
# 
# Variables Definition and Initialization
# 	Python variables do not need explicit declaration to reserve memory space
# 	The declaration happens automatically when you assign a value to a variable
# 	You can change the value of a variable in your program at any time, and Python will always keep track of its current value.
# 
# Multiple Assignment
# 	Single value to several variables simultaneously
# 		a = b = c = 1
# 
# 	Multiple value to multiple variables simultaneously
# 		a, b, c = 3, 2.56, "john"
# 
# Global and Local Variables
# 	Local variables are the variables that declared inside the function and have scope within the function.
# 	Global variables can be used throughout the program, and its scope is in the entire program. 
#	We can use global variables inside or outside the function.
# 
# 	“global”
# 	Any variable which is changed or created inside of a function is local, if it hasn’t been declared as a global variable. 
#	To tell Python, that we want to use the global variable, we have to use the keyword “global”,
# 	We only need to use global keyword in a function if we want to do assignments / change them.
# 
# 	global is not needed for printing and accessing. Why? 
# 	Python “assumes” that we want a local variable due to the assignment to s inside of f(), so the first print statement throws this error message. #	 Any variable which is changed or created inside of a function is local, if it hasn’t been declared as a global variable. 
# 
# Delete a variable
# 	We can delete the variable using the del keyword. Syntax:
# 	del <variable_name>  
# 
# Object References
# 	Python is the highly object-oriented programming language; that's why every data item belongs to a specific type of class. 
# 	Variables are a symbolic name that is a reference or pointer to an object. The variables are used to denote objects by that name.
# 
# Object Identity
# 	In Python, every created object identifies uniquely in Python. 
# 	Python provides the guaranteed that no two objects will have the same identifier. 
# 	The built-in id() function, is used to identify the object identifier. 
# 
########################################

print("=== Variables ===")
print("=== Variable Naming ===")
print("=== Declaring Variable and Assigning Values ===")
print("=== Variables Definition and Initialization ===")
avar = 5
print(f"avar {avar}")

print("=== Multiple Assignment ===")
a = b = c = 1
print(f"a {a}   b {b}   c {c}")
a, b, c = 3, 2.56, "john"
print(f"a {a}   b {b}   c {c}")

print("=== Global and Local Variables ===")
# This function uses global variable astr
def use_global_varible():
    print(f"global astr {astr}")

# This function has a variable with name same as astr
def use_local_varible():
	astr = "local varible hide global variable"
	print(f"local astr {astr}")

# This function uses global and then defines varible with same name
def use_global_and_then_local_varible():
    global astr
    print(f"global astr {astr}")
    astr = "local varible hide global variable"
    print(f"local astr {astr}")

# Global scope
astr = "a global varible"
use_global_varible()
use_local_varible()
use_global_and_then_local_varible()

print("=== Delete a variable ===")
astr = "a string"
print(astr)
del astr
#print(astr) # NameError: name 'astr' is not defined
print("=== Object References ===")
astr = "a string"
print(f"type(astr)  {type(astr)}")

print("=== Object Identity ===")
a = 50  
b = a  
print(f"id(a) {id(a)}")  
print(f"id(b) {id(b)}")  
# Reassigned variable a  
a = 500  
print(f"id(a) {id(a)}")  
print(f"id(b) {id(b)}")    


###################
#   END OF FILE
###################


