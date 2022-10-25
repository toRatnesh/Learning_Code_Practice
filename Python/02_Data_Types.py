##################################
# 
# Referencs:
#     https://www.javatpoint.com/python-data-types
# 
# Standard Data Types
#     Python has five standard data types:
#     1.	Numbers
#     2.	String
#     3.	List
#     4.	Tuple
#     5.	Dictionary
# 
# Type Conversion in Python
#     Python defines type conversion functions to directly convert one data type to another
#     1.	int(a,base): This function converts any data type to integer. ‘Base’ specifies the base in which string is if data type is string.
#     2.	float(): This function is used to convert any data type to a floating point number
#     3.	ord(): This function is used to convert a character to integer.
#     4.	hex(): This function is to convert integer to hexadecimal string.
#     5.	oct(): This function is to convert integer to octal string.
#     6.	complex(real,imag): This function converts real numbers to complex(real,imag) number.
#     7.	str(): Used to convert integer into a string.
#     8.	tuple(): This function is used to convert to a tuple.
#     9.	set(): This function returns the type after converting to set.
#     10.	list(): This function is used to convert any data type to a list type.
#     11.	dict(): This function is used to convert a tuple of order (key,value) into a dictionary.
# 
##################################

s = "10010"

c = int(s,2)
print(f"After converting to integer base 2 : {c}")

e = float(s)
print (f"After converting to float : {e}")

s = '4' 
c = ord(s)
print (f"After converting character to integer : {c}")
 
c = hex(56)
print (f"After converting 56 to hexadecimal string : {c}")
 
c = oct(56)
print (f"After converting 56 to octal string : {c}")

c = complex(5)
print (f"After converting 5 to complex number : {c}")

a = 1
c = str(a)
print (f"After converting integer to string : {c}")

s = 'a sentence'
c = tuple(s)
print (f"After converting string to tuple : {c}")

c = set(s)
print (f"After converting string to set : {c}")
 
c = list(s)
print (f"After converting string to list : {c}")

tup = (('a', 1) ,('f', 2), ('g', 3))
c = dict(tup)
print (f"After converting tuple to dictionary : {c}")

###################
#   END OF FILE
###################
