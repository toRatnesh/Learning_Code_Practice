#####################################
# 
# References
#     https://www.javatpoint.com/python-lists
#     https://docs.python.org/3/tutorial/introduction.html#lists
#     https://docs.python.org/3/tutorial/datastructures.html#more-on-lists
# 
# 
# List
#     List is collection of various type of data
#     List operations which need comparison list elements should have same data type
# 
# Characteristics of List
#     List is ordered and mutable
#     List can store heterogeneous type (elements of different type)
# 
# Defining a List
#     List can be defined as comma separated values inclosed within brackets
# 
# Accessing List Elements
#     List elements can be access using index and slice
# 
# Sub-list of the List
#     Get sub-list of the list using the following syntax
#     list_varible[start:stop:step]
# 
# Update and Delete using index
#     To update an element use 
#         list_name[index] = new_value
#     to delete
#         del list_name[index]
# 
# List Operations
#     Repetition(*)       The repetition operator enables the list elements to be repeated multiple times.	
#     Concatenation(+)    It concatenates the list mentioned on either side of the operator.	
#     Membership(in)      It returns true if a particular item exists in a particular list otherwise false.	
#     Iteration(for loop) The for loop is used to iterate over the list elements.	
# 
# List Built-in functions
#     len(list)   Gives the total length of the list.
#     max(list)   Returns item from the list with max value.
#     min(list)   Returns item from the list with min value.
#     list(seq)   Converts a tuple into list.
#     cmp(list1, list2)	Compares elements of both lists. Python 3 does not have cmp
# 
# List Methods
#     append(x)   Add an item to the end of the list. Equivalent to a[len(a):] = [x].
#     insert(i,x) Insert an item before the index i, so a.insert(0, x) inserts at the front of the list, and a.insert(len(a), x) is equivalent to a.append(x).
#     extend(iterable)    Extend the list by appending all the items from the iterable. Equivalent to a[len(a):] = iterable.
#     remove(x)   Remove the first item whose value is equal to x. If element x is not present raises a ValueError
#     pop([i])    Remove the item at index i, and return it. a.pop() removes and returns the last item.
#     reverse()   Reverse the elements of the list in place.
#     copy()      Return a shallow copy of the list. Equivalent to a[:].
#     clear()     Remove all items from the list. Equivalent to del a[:].
#     count(x)    Return the number of times x appears in the list.
#     sort(*, key=None, reverse=False)    Sort the items of the list in place
#     index(x[, start[, end]])    Return zero-based index in the list of the first item whose value is equal to x. Raises a ValueError if there is no such item. The optional arguments start and end are interpreted as in the slice notation and are used to limit the search to a particular subsequence of the list. The returned index is computed relative to the beginning of the full sequence rather than the start argument.
# 
# NOTE
#     Methods like insert, remove or sort that only modify the list have no return value printed – they return the default None. 1 This is a design principle for all mutable data structures in Python.
#     All data can not be sorted or compared. For instance, [None, 'hello', 10] doesn’t sort because integers can’t be compared to strings and None can’t be compared to other types.
#     Some types don’t have a defined ordering relation. For example, 3+4j < 5+7j isn’t a valid comparison.
# 
#####################################

print("=== Defining a List ===")
empty_list = []
print(f"type(empty_list) {type(empty_list)}")
single_elem_list = [5]
print(f"type(single_elem_list) {type(single_elem_list)}")
list1 = [1 , 3.7, 'word-1', True, False, 31, 4, 33]
print(f"list1 {list1}")

print("=== Accessing List Elements ===")
print (f"list1[2] {list1[2]}", )
print (f"list1[-2] {list1[-2]}")

print (f"list1[1:4] {list1[1:4]}")
print (f"list1[-1:-4] {list1[-1:-4]}")
print (f"list1[-4:-1] {list1[-4:-1]}")

print (f"list1[1:] {list1[1:]}")
print (f"list1[-4:] {list1[-4:]}")

print("=== Sub-List ===")
print(f"{list1[2:8:2]}")

print("=== Update and Delete using index ===")
list1[3] = 'word-3'
print(f"After list1[3] = 'word-3' list1 {list1}")
del list1[3]
print(f"After del list1[3] list1 {list1}")

print("=== List Operations ===")
list1 = [1, 2.5, 'word-1', True]
list2 = [13, 23, 33, 63, 83, 73]
print(f"list1*2 {list1*2}")
print(f"list1+list2 {list1+list2}")
print(f"'word-1' in list1 {'word-1' in list1}")
print(f"'word-3' in list1 {'word-3' in list1}")
print("Iterate over list, the list elements are")
for elem in list1:
    print(f"{elem}", end=' ')
print("")

print("=== List Built-in functions ===")
print(f"len(list1) {len(list1)}")
#print(f"min(list1) {min(list1)}") # TypeError: '<' not supported between instances of 'str' and 'int'
#print(f"max(list1) {max(list1)}") # TypeError: '>' not supported between instances of 'str' and 'float'
print(f"min(list2) {min(list2)}")
print(f"max(list2) {max(list2)}")
str1 = "a sample string"
tup1 = ('a-tupe', 2.3, ('nested-tuple', 4, 5.6, True), 5, False)
print(f"list(str1) {list(str1)}")
print(f"list(tup1) {list(tup1)}")

print("=== List Methods ===")
list1 = [1, 2.5, 'word-1', True]
print(f"list1 {list1}")
print(f"list1.append(7) {list1.append(7)}")
print(f"list1 {list1}")
print(f"list1.insert(3, 'new word') {list1.insert(3, 'new word')}")
print(f"list1 {list1}")
tup1 = ('a-tupe', 2.3, ('nested-tuple', 4, 5.6, True), 5, False)
print(f"list1.extend(tup1) {list1.extend(tup1)}")
print(f"list1 {list1}")
print(f"list1.remove('new word') {list1.remove('new word')}")
print(f"list1.pop(3) {list1.pop(3)}")
print(f"list1.pop() {list1.pop()}")
print(f"list1 {list1}")
reverse_list = list1.reverse()
print(f"list1 {list1}")
print(f"reverse_list {reverse_list}")
copy_list = list1.copy()
print(f"list1 {list1}")
print(f"copy_list {copy_list}")
print(f"list1.clear() {list1.clear()}")
print(f"list1 {list1}")
print(f"copy_list {copy_list}")
print(f"copy_list.count('word-1') {copy_list.count('word-1')}")
#print(f"copy_list.sort() {copy_list.sort()}") # TypeError: '<' not supported between instances of 'tuple' and 'int'
print(f"list2 {list2}")
print(f"list2.sort() {list2.sort()}")
print(f"list2 {list2}")
print(f"list2.index(63) {list2.index(63)}")
print(f"list2.index(63, 2, 6) {list2.index(63, 2, 6)}")

################
#   END OF FILE
################

