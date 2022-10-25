######################################
# 
# Referencs:
#   https://www.javatpoint.com/python-arrays
# 
# Arrays
#   An array is defined as a collection of fixed number of items of the same type that are stored at contiguous memory locations.
#   Array can be handled in Python by a module named array.
#   Arrays are mutable
# 
# Array Representation
#   Array can be created in Python by importing the array module to the python program.
# 	    from array import *
# 	    arrayName = array(typecode, [initializers])
# 
# Array operations
#   Traverse	- It prints all the elements one by one.
#   Insertion	- It adds an element at the given index.
#   Deletion	- It deletes an element at the given index.
#   Search		- It searches an element using the given index or by the value.
#   Update		- It updates an element at the given index.
# 
# Accessing array elements
# 	using the respective indices of those elements
# 	
# Change or add elements
# 	using indices similarly like list 
# 
# Delete elements
# 	using del statement
# 
# Array Length
# 	Number of elements present in an array
# 
# Array Concatenation
# 	using the + symbol
# 
######################################

from array import *  

arr = array('i', [1, 2, 3, 4, 5, 6])

print(f"{arr}")

print("=== Accessing array elements ===")
print(f"First element: {arr[0]}")
print(f"Second element: {arr[1]}")


print("=== Change or add elements ===")
arr[1] = 12
arr[2:5] = array('i', [13,14,15])
print(f"{arr}")


print("=== Delete elements ===")
print(f"Before delete length {len(arr)}")
del arr[2]
del arr[3]
print(f"{arr}")
print(f"After delete length {len(arr)}")


print("=== Array Length ===")
print(f"Length {len(arr)}")


print("=== Array Concatenation ===")
arr_i = array('i', [1,2,3,4,5])
arr_d1 = array('d', [1.2,2.3,3.4,4.5,5.6])
arr_d2 = array('d', [11.2,12.3,13.4,14.5,15.6])
#arr_c1 = array('d')
#arr_c1 = arr_i + arr_d
#arr_c1 = arr_d + arr_i

#arr_c2 = array('i')
#arr_c2 = arr_i + arr_d
#arr_c2 = arr_d + arr_i

arr_c = array('d')
arr_c = arr_d1 + arr_d2
print(f"{arr_c}")

###################
#   END OF FILE
###################