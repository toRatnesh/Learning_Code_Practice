############################
# 
# References
#     https://www.javatpoint.com/python-data-types#numbers
#     https://docs.python.org/3/tutorial/introduction.html#numbers
# 
# Numbers
#     Number stores numeric values.
# 
# Types
#     int
#     long
#     float
#     complex
# 
#     int		10, 100, -786, 80, -490, -0x260, 0x69
#     Long	51924361L, -0x19323L, 0122L, 0xDEFABCECBDAECBFBAEl, 535633629843L, -052318172735L, -4721885298529L
#     float	0, 15.2, -21.9, 32.3+e18, -90, -3.25E+101, 70.2-E12
#     complex	3.14j, 45.j, 9.322e-36j, .876j, -.6545+0J, 3e+26J, 4.53e-7j
# 
# NOTE
#     Python allows you to use a lowercase l with long. But it is recommended to use only an uppercase L to avoid confusion with the number 1.
#     type() function to know the data-type
#     isinstance() function is used to check an object belongs to a particular class
# 
# Number Type Conversion
#     Python converts numbers internally in an expression containing mixed types to a common type for evaluation. 
#     Sometimes, you need to coerce a number explicitly from one type to another to satisfy the requirements of an operator or function parameter.
# 
#     int(x)          convert x to a plain integer
#     long(x)         convert x to a long integer
#     float(x)        convert x to a floating-point number
#     complex(x)      convert x to a complex number with real part x and imaginary part zero
#     complex(x, y)   convert x and y to a complex number with real part x and imaginary part y. x and y are numeric expressions
# 
# Mathematical Constants
#     pi	The mathematical constant pi
#     e	The mathematical constant e
# 
############################

int_v = 5
float_v = 3.7
complex_v = 4+5j

print(f"type(int_v) {type(int_v)}")
print(f"type(float_v) {type(float_v)}")
print(f"type(complex_v) {type(complex_v)}")

print("=== int type ===")
num = 10
print(f"num = 10        {num}")
num = 100
print(f"num = 100       {num}")
num = -786
print(f"num = -786      {num}")
num = 80
print(f"num = 80        {num}")
num = -490
print(f"num = -490      {num}")
num = -0x260
print(f"num = -0x260    {num}")
num = 0x69
print(f"num = 0x69      {num}")

print("=== float type ===")
num = 0
print(f"num = 0             {num}")
num = 15.2
print(f"num = 15.2          {num}")
num = -21.9
print(f"num = -21.9         {num}")
#num = 32.3+e18
#print(f"num = 32.3+e18         {num}")
num = -90
print(f"num = -90           {num}")
num = -3.25E+101
print(f"num = -3.25E+101    {num}")
#num = 70.2-E12
#print(f"num = 70.2-E12      {num}")

print("=== complex type ===")
num = 3.14j
print(f"num = 3.14j         {num}")
num = 45.j
print(f"num = 45.j          {num}")
num = 9.322e-36j
print(f"num = 9.322e-36j    {num}")
num = .876j
print(f"num = .876j         {num}")
num = -.6545+0J
print(f"num = -.6545+0J     {num}")
num = 3e+26J
print(f"num = 3e+26J	    {num}")
num = 4.53e-7j
print(f"num = 4.53e-7j      {num}")

print("=== int operations ===")
print(f"(8 + 5) {(8 + 5)}")
print(f"(8 - 5) {(8 - 5)}")
print(f"(8 * 5) {(8 * 5)}")
print(f"(8 / 5) {(8 / 5)}")
print(f"(8.0 / 5) {(8.0 / 5)}")


###################
#   END OF FILE
###################

