############################
# 
# Referencs:
#     https://www.javatpoint.com/python-if-else
#     https://docs.python.org/3/tutorial/controlflow.html#if-statements
#     https://docs.python.org/3/tutorial/controlflow.html#match-statements
#     https://peps.python.org/pep-0636/
# 
# Decision Making
#     Python programming language assumes any non-zero and non-null values as TRUE, and any zero or null values as FALSE value.
# 
# 1.	if statements
#     An if statement consists of a boolean expression followed by one or more statements.
#     Syntax
#         if expression:
#             statement(s)
# 
# 2.	if...else statement
#     An else statement contains a block of code that executes if the conditional expression in the if statement resolves to 0 or a FALSE value.
#     The else statement is an optional statement and there could be at the most only one else statement following if.
#     Syntax
#         if expression:
#             statement(s)
#         else:
#             statement(s)
# 
# 3.	The elif Statement
#     The elif statement allows you to check multiple expressions for TRUE and execute a block of code as soon as one of the conditions evaluates to TRUE.
#     There can be an arbitrary number of elif statements following an if.
#     Syntax
#         if expression1:
#             statement(s)
#         elif expression2:
#             statement(s)
#         elif expression3:
#             statement(s)
#         else:
#             statement(s)
# 
# 4. Nested IF Statements
#     In a nested if construct, you can have an if...elif...else construct inside another if...elif...else construct.
#     Syntax
#         if expression11:
#             statement(s)
#             
#             if expression21:
#                 statement(s)
#             elif expression22:
#                 statement(s)
#             else:
#                 statement(s)
#         elif expression12:
#             statement(s)
#         else:
#             statement(s)
# 
# match Statements
#     Similar to Rust, a match statement takes an expression and compares its value to successive patterns given as one or more case blocks
#     Only the first pattern that matches gets executed and it can also extract components (sequence elements or object attributes) from the value into variables.
#     The “variable name” _ acts as a wildcard and never fails to match. If no case matches, none of the branches is executed.
#     You can combine several literals in a single pattern using | (“or”
#     For more detail on pattern match visit:
#     https://peps.python.org/pep-0636/
#     
############################


print("=== if statement ===")
var1 = 100
if var1:
	print(f"1 - Got a true expression value {var1}")

var2 = 0
if var2:
	print(f"2 - Got a false expression value {var2}")


print("=== if-else statement ===")
amount = 1500
discount = 0
if amount < 1000:
	discount = amount * 0.05
else:
	discount = amount * 0.10
print(f"Discount {discount}, Net payable: {amount-discount}", )


print("=== if-elif-else statement ===")
amount = 4500
discount = 0
if amount<1000:
    discount = amount*0.05
elif amount >= 1000 and amount<5000:
    discount = amount*0.10
else:
    discount = amount*0.15
print(f"Discount {discount}, Net payable: {amount-discount}", )


print("=== Nested if statement ===")
amount = 4500
discount = 0
cutomer_type = 1
if cutomer_type == 0:
    if amount<1000:
        discount = amount*0.05
    elif amount >= 1000 and amount<5000:
        discount = amount*0.10
    else:
        discount = amount*0.15
else:
    if amount<1000:
        discount = amount*0.10
    elif amount >= 1000 and amount<5000:
        discount = amount*0.15
    else:
        discount = amount*0.20
print(f"Discount {discount}, Net payable: {amount-discount}", )


print("=== match statement ===")
def which_color(color):
    match color:
        case 1:
            print("color is RED")
            return 
        case 2:
            print("color is GREEN")
            return
        case 3:
            print("color is BLUE")
            return
        case _:
            print("Color different from RED, GREEN, BLUE")

which_color(1)
which_color(2)
which_color(3)
which_color(4)


###################
#   END OF FILE
###################

