######################################
# 
# References
#     https://www.javatpoint.com/python-tuples
#     https://www.javatpoint.com/python-list-vs-tuple
#     https://docs.python.org/3/tutorial/datastructures.html#tuples-and-sequences
# 
# Tuple
#     A tuple is a sequence of immutable objects
# 
# Characteristics of Tuple
#     Tuples are ordered and immutable
#     Tuple can contain heterogeneous (different type) elements
# 
# Defining Tuple
#     Tuple can be defined using ()
#     Although using parenthesis is not required, it is recommended to do so.
# 
# Accessing Tuple Elements
#     Tuple element can be accessed using index and slicing
# 
# Sub-tuple of a Tuple
#     Sub-tuple can be obtained by syntax
#         tuple-variable[start:stop:step]
# 
# Tuple Operations
#     Repetition(*)       The repetition operator enables the tuple elements to be repeated multiple times.	
#     Concatenation(+)    It concatenates the tuples mentioned on either side of the operator.	
#     Membership(in)      It returns true if a particular item exists in a particular tuple otherwise false.	
#     Iteration(for loop) The for loop is used to iterate over the tuple elements.	
# 
# Tuple Built-in functions
#     len(tuple)   Gives the total length of the tuple.
#     max(tuple)   Returns item from the tuple with max value.
#     min(tuple)   Returns item from the tuple with min value.
#     tuple(seq)   Converts a sequence into tuple.
#     cmp(tuple1, tuple2)	Compares elements of both tuple. Python 3 does not have cmp
# 
# NOTE
# We may create tuple from a sequence in 3 way 
#     1. using tuple() function
#     2. usning tuple() funciton with list comprehension
#     3. using parameter unpack and , in ()
# 
# Tuple Methods
#     Tuple is immutable so it does not provide any method which modifies the tuple
#     count(x)    Return the number of times x appears in the tuple.
#     index(x[, start[, end]])    Return zero-based index in the tuple of the first item whose value is equal to x. Raises a ValueError if there is no such item. The optional arguments start and end are interpreted as in the slice notation and are used to limit the search to a particular subsequence of the tuple. The returned index is computed relative to the beginning of the full sequence rather than the start argument.
# 
# NOTE
#     
# Differences between Lists and Tuples
#     List is mutable, Tuple is immutable
#     As a result, tuples can be used as keys to a dictionary if required, while list can not be.
# 
######################################

print("=== Defining tuple ===")
empty_tup = ()
this_is_int = (5)
print(f"this_is_int = (5) {type(this_is_int)}")
single_elem_tup = (5,)
print(f"single_elem_tup = (5,) {type(single_elem_tup)}")
tup_without_parenthesis = 1, 3.7, 'word-1'
print(f"type(tup_without_parenthesis) {type(tup_without_parenthesis)}")
tup1 = (1, 2, 'a', 'b', "word1", "word3", 4.5, 6.9, True, False, 11, 12)
print(f"tup1 {tup1}")

print("=== Accessing Tuple Elements ===")
print(f"tup1[2]: {tup1[2]}")
print(f"tup1[-2]: {tup1[-2]}")
print(f"tup1[1:4]: {tup1[1:4]}")
print(f"tup1[-1:-4]: {tup1[-1:-4]}")
print(f"tup1[-4:-1]: {tup1[-4:-1]}")
print(f"tup1[1:]: {tup1[1:]}")
print(f"tup1[-4:]: {tup1[-4:]}")

print("=== Sub tuple ===")
print(f"sub-tuple tup1[2:10:2] : {tup1[2:10:2]}")

print("=== Tuple Operations ===")
tup1 = (1, 2.3, 'word-1', False)
tup2 = (23, 3, 43, 33, 73, 6)
print(f"tup1*2 {tup1*2}")
print(f"tup1+tup2 {tup1+tup2}")
print(f"'word-1' in tup1 {'word-1' in tup1}")
print(f"'word-1' in tup1 {'word-1' not in tup1}")
print("Iterating over tuple using for loop")
for elem in tup1:
    print(f"{elem}", end=' ')
print("")

print("=== Tuple Built-in functions ===")
tup1 = (1, 2.3, 'word-1', False)
tup2 = (23, 3, 43, 33, 73, 6)
print(f"len(tup1) {len(tup1)}")
#print(f"min(tup1) {min(tup1)}") # TypeError: '<' not supported between instances of 'str' and 'int'
#print(f"max(tup1) {max(tup1)}") # TypeError: '>' not supported between instances of 'str' and 'float'
print(f"min(tup2) {min(tup2)}")
print(f"max(tup2) {max(tup2)}")
# we may create tuple from a sequence in 3 way 
# 1. using tuple() function, 2. usning tuple() funciton with list comprehension, 3. using parameter unpack and , in ()
str1='a sample string'
print(f"tuple(str1) {tuple(str1)}")
list1= [11, 12, 13, 14, 15]
print(f"tuple(list1) {tuple(list1)}")
print(f"tuple(elem for elem in list1) {tuple(elem for elem in list1)}")
print(f"(*list1, ) {(*list1, )}")

print("=== Tuple Methods ===")
tup1 = (1, 2.3, 'word-1', False, 93, 'word-3', 33)
print(f"tup1.count(93) {tup1.count(93)}")
print(f"tup1.index(93) {tup1.index(93)}")
print(f"tup1.index(93, 2, 6) {tup1.index(93, 2, 6)}")


###################
#   END OF FILE
###################

