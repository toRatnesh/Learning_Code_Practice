######################################
# 
# References:
#     https://www.javatpoint.com/python-set
#     https://docs.python.org/3/library/stdtypes.html#set-types-set-frozenset
#     
# Python Set
#     Set is the collection of the unique and immutable items in unordered way.
#     Sets are mutable.
# 
#     We cannot directly access any element of the set by the index.
#     However, we can print them all together, or we can get the list of elements by looping through the set.
# 
#     Set cannot contain any mutable elements (list, dictionary, set).
# 
# Creating a set
#     1. Using curly braces
#         By enclosing the comma-separated immutable items with the curly braces {}.
#         weekdays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}
# 
#     2. Using set() method
#         Python set() method, can also be used to create the set by the passed sequence.
#         weekdays = set(["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"])    
# 
#     NOTE:
#         TO create an empty set use set method without any arg i.e. set()
#         {} without any element creates a dictionary
# 
# Adding items to the set
#     1. add()    method is used to add a single element
#     2. update() method is used to add multiple elements. It accepts iterable as an argument.
# 
# Removing items from the set
#     1. remove() method will through an error if item does not exist in set
#     2. discord() 
#     3. clear()  remove all the items from the set
#     4. pop()    remove an arbitrary element from the set
# 
# Python Set Operations
#     1. Union        (|, union())        The union The union of the two sets contains all the items that are present in both the sets.
#     2. Intersection (&, intersection()) The intersection of the two sets is given as the set of the elements that common in both sets.
#     3. intersection_update()            The intersection_update() method removes the items from the original set that are not present in both the sets (all the sets if more than one are specified).
#     4. Difference   (-, difference())   Suppose there are two sets A and B, and the difference is A-B that denotes the resulting set will be obtained that element of A, which is not present in the set B.
#     5. Symmetric Difference (^, symmetric_difference())
#             Symmetric difference of sets, it removes that element which is present in both sets.
# 
# Set comparisons
#     By using <, >, <=, >= , == with the sets we can check whether a set is a subset, superset, or equivalent to other set.
# 
# FrozenSets
#     The frozen sets are the immutable form of the normal sets, i.e., the items of the frozen set cannot be changed and therefore it can be used as a key in the dictionary.
#     The frozenset() method is used to create the frozenset object. The iterable sequence is passed into this method which is converted into the frozen set as a return type of the method.
# 
######################################

print("=== Creating set ===")
#Creating a set: 1. Using curly braces
weekdays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}

#Creating a set: 1. Using set() method
weekdays = set(["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"])

set_with_different_type = {1, 2.5, "A string", ("tuple element", 5)}

#set_with_mutable_elem = {1, 2.5, "A string", ["a list", 3]} # TypeError: unhashable type: 'list'

empty_set = set()
print(type(empty_set))  

this_is_empty_dict = {}
print(type(this_is_empty_dict))  

set_with_duplicate_elem = {1, 2, 2, 3, 3, 4, "A string", "sample string", "A string", "a string", 4}
print(f"Set with duplicate elements will not keep duplicate items {set_with_duplicate_elem}")


print("=== Adding items to the set ===")
months = {"Jan", "Feb", "Mar", "Apr"}
print(f"set of months: {months}")

months.add("May")
print(f"After add months: {months}")

months.update(["Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"])
print(f"After update months: {months}")


print("=== Removing items from the set ===")
print(f"months: {months}")
months.discard("Dec")
months.discard("DoesNotExist")

#months.remove("Dec") # KeyError: 'Dec'
months.remove("Nov")
print(f"months: {months}")

months.pop()
months.pop()
print(f"months: {months}")

months.clear()
print(f"months: {months}")


print("=== Python Set Operations ===")
set_a = {'a', 'b', 'c', 'd', 'e', 'f'}
set_b =               { 'd', 'e', 'f', 'g', 'h', 'i', 'j'}
print(f"set_a {set_a}")
print(f"set_b {set_b}")
print(f"set_a | set_b {set_a | set_b}")
print(f"set_a & set_b {set_a & set_b}")
print(f"set_a - set_b {set_a - set_b}")
print(f"set_a ^ set_b {set_a ^ set_b}")
print(f"set_a {set_a}")
print(f"set_b {set_b}")
print(f"set_a.intersection_update(set_b) {set_a.intersection_update(set_b)}")
print(f"set_a {set_a}")
print(f"set_b {set_b}")

print("=== Set comparisons ===")
set_1 = {1, 2, 3}
set_2 = {1, 2, 3}
set_3 = {1, 2, 3, 4, 5}
print(f"set_1 {set_1}")
print(f"set_2 {set_2}")
print(f"set_3 {set_3}")

print(f"set_1 == set_2 {set_1 == set_2}")
print(f"set_1 == set_3 {set_1 == set_3}")

print(f"set_1 <= set_2 {set_1 <= set_2}")
print(f"set_1 <= set_3 {set_1 <= set_3}")

print(f"set_1 >= set_2 {set_1 >= set_2}")
print(f"set_1 >= set_3 {set_1 >= set_3}")

print(f"set_1 < set_2 {set_1 < set_2}")
print(f"set_1 < set_3 {set_1 < set_3}")

print(f"set_1 > set_2 {set_1 > set_2}")
print(f"set_1 > set_3 {set_1 > set_3}")

print("=== FrozenSets ===")
dict_country = {"Name":"India", "Currency":"Rupee", "Continent":"Asia"}
key_using_frozensets = frozenset(dict_country)
for k in key_using_frozensets:
    print(k)
#key_using_frozensets.add("CanNotAdd") # AttributeError: 'frozenset' object has no attribute 'add'

##################
#   END OF FILE
##################        
