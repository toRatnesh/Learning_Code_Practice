######################################
# 
# References:
#     https://www.javatpoint.com/python-list-comprehension
#     https://docs.python.org/3/tutorial/datastructures.html#list-comprehensions
#     https://docs.python.org/3/tutorial/datastructures.html#nested-list-comprehensions
# 
# List Comprehension
#     List comprehension allows us to develop sophisticated functionality with just one line of code.
# 
#     Syntax
#     newlist = [expression for item in iterable if condition == True]  
# 
# Advantages
#     List comprehension has better performance than for loop
#     It is a single tool that can be used in various circumstances
#     It may be leveraged for mapping or filtering and basic list generation
#     Easier to read and grasp than loops since they are more declarative
#     We can concentrate on what we want to put in the list and allow Python to handle the list generation
# 
# Using Conditions in List Comprehension
#     Conditional statements can be used by list comprehensions to change existing lists
# 
# Nested List Comprehensions
#     Nested List Comprehensions are similar to nested for loops in that they are a list comprehension inside another list comprehension
# 
######################################

import time

alist = [2, 3, 4, 5, 12, 35, 43, 24]
another_list = []

print("=== using for loop ===")
for n in alist:
    another_list.append(n**2)
print(f"another_list {another_list}")

print("=== using list comprehension ===")
another_list = [n**2 for n in alist]
print(f"another_list {another_list}")

another_list = [n**2 for n in alist if 0 == n%2 ] # using condition
print(f"another_list {another_list}")


def listUsingForLoop(num):
    alist = []
    for n in range(num):
        alist.append(n)
    return alist

def listUsingListComprehension(num):
    return [n for n in range(num)]

print("=== performance comparison using for loop and nested comprehension ===")
start = time.time()
listUsingForLoop(1000000)
end = time.time()
print(f"time taken by using for loop {end - start}")

start = time.time()
listUsingListComprehension(1000000)
end = time.time()
print(f"time taken by using list comprehension {end - start}")


print("=== Nested List Comprehensions ===")

print("=== using nested for loop ===")
nested_list = []
for i in range(3):
    nested_list.append([])
    for j in range(5):
           nested_list[i].append(i + j) 
print(f"nested_list {nested_list}")

print("=== usnig nested list comprehension ===")
nested_list = [[i + j for j in range(5)] for i in range(3)]
print(f"nested_list {nested_list}")

####################
#   END OF FILE
####################
