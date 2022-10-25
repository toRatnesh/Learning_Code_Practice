######################################
# 
# References
#   https://www.javatpoint.com/python-lambda-functions
#   https://docs.python.org/3/tutorial/controlflow.html#lambda-expressions
# 
# Lambda Functions
#     Use lambda keyword to define a lambda functions
#     Lambda functions are anonymous functions
#     Syntax
#         lambda arguments: expression
#     
#     It can be used whenever function arguments are necessary
#     As per syntax, lambda functions are limited to a single statement
# 
#     It differs from regular function in way that it evaluates only a single expression and yields a funciton object
# 
# Lambda with Multiple Statements
#     Contrsuct multiple lambda and call one lambda with another as an argument
# 
######################################

print("=== lambda ===")
getSquare = lambda val: val * val
print(f"{getSquare(5)}")


print("=== Using lambda ===")
my_List = [[3, 5, 8, 6], [23, 54, 12, 87], [1, 2, 4, 12, 5]]
sort_List = lambda num : ( sorted(n) for n in num )
third_Largest = lambda num, func : [ lt[ len(lt) - 2] for lt in func(num)]
result = third_Largest( my_List, sort_List)
print(f"List {my_List}")
print(f"Third largest {result}")


alist = [13, 33, 46, 67, 86, 56, 57, 37, 84, 37, 67, 43, 56, 78, 53]
oddlist = list(filter(lambda num : 0 != num %2, alist))
evenlist = list(filter(lambda num : 0 == num %2, alist))
print(f"A list {alist}")
print(f"Odd list {oddlist}")
print(f"Even list {evenlist}")

numbers_list = [2, 4, 5, 1, 3, 7, 8, 9, 10]
squared_list = list(map(lambda num: num ** 2 , numbers_list ))
print(f"Square list {squared_list}")

#################
#   END OF FILE
#################

