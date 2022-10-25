######################################
# 
# References
#     https://www.javatpoint.com/python-dictionary
#     https://docs.python.org/3/library/stdtypes.html#typesmapping
# 
# Dictionary
#     dictionary is the data type in Python
#     mutable data-structure
#     used to store the data in a key-value pair format 
#     Keys must be a unique element and immutable
#     Value can be any Python object
# 
# Creating the dictionary
#     using {}:       key-vaule pair separated by : and enclosed within {}
#     using dict():   dict() method is used to create dictionary from pair of items
# 
# Access value using []
#     use key with [] to get access to element
# 
# Add/Update value using []
#     [] with key is used to add new key and updates existing key
# 
# Delete dictionary using del
#     del dict_name[key]  is used to delete a key
#     del dict_name       is used to delete entire dictionary
# 
# 
# Dictionary Operations
#     Membership(in)      It returns true if a particular key exists in a particular dictionary otherwise false.	
#     Iteration(for loop) The for loop is used to iterate over the keys of dictionary.	
# 
# Dictionary Built-in functions
#     len(dick)   Gives the total number of keys
#     max(dict)   Returns item from the keys with max value
#     min(dict)   Returns item from the keys with min value
#     list(dict)   Gives a list of all keys
#     str(dict)	Produces a printable string representation of a dictionary
#     cmp(dict1, dict2)	Compares elements of both dictionaries. Python 3 does not have cmp
#     reversed(d)		Return a reverse iterator over the keys of the dictionary. This is a shortcut for reversed(d.keys())
#     iter(dictview)	Return an iterator over the keys, values or items (represented as tuples of (key, value)) in the dictionary
# 
# Dictionary Methods
#     NOTE:   default defaults to None in following methods
# 
#     clear()             Remove all items from the dictionary
#     copy()              Return a shallow copy of the dictionary
#     items()             Return a new view of the dictionary’s items ((key, value) pairs)
#     keys()              Return a new view of the dictionary’s keys
#     values()            Return a new view of the dictionary’s values
#     popitem()           Remove and return a (key, value) pair from the dictionary in LIFO order. For empty dictionary raises a KeyError.
#     get(key[, default]) Return the value for key if key is in the dictionary, else default. This method never raises a KeyError.
#     pop(key[, default]) If key is in the dictionary, remove it and return its value, else return default. 
#                         If default is not given and key is not in the dictionary, a KeyError is raised.
#     setdefault(key[, default])  If key is in the dictionary, return its value. 
#                                 If not, insert key with a value of default and return default.
#     update([other])     Update the dictionary with the key/value pairs from other, overwriting existing keys. Return None.
# 
######################################

print("=== Creating the dictionary ===")
empty_dict = {}
print(f"type(empty_dict) {type(empty_dict)}")

single_elem = {'name':'this is single element dictionary'}
print(f"type(single_elem) {type(single_elem)}")
print(f"single_elem: {single_elem}")

multi_elem = {'name':'learning dictionary', 'language':'Python', 'chapter':10, 2:'int as key'}
print(f"multi_elem: {multi_elem}")

dict_using_tupleList = dict([('name', 'dictionary using tuple list'), ('language', 'Python'), ('chapter',10), (2, 'int as key')])
print(f"dict_using_tupleList: {dict_using_tupleList}")

dict_using_strList = dict(['py', 'th', 'on'])
print(f"dict_using_strList: {dict_using_strList}")

#dict_using_strList = dict(['pyt', 'hon']) # ValueError: dictionary update sequence element #0 has length 3; 2 is required


print("=== Access value using [] ===")
print(f"dict_using_tupleList['name'] {dict_using_tupleList['name']}")
print(f"dict_using_tupleList[2] {dict_using_tupleList[2]}")


print("=== Add/Update value using [] ===")
add_update_dict = {}
add_update_dict['key-1'] = 'value-1'
add_update_dict['key-2'] = 'value-2'
add_update_dict['key-3'] = 'value-3'
print(f"add_update_dict: {add_update_dict}")
add_update_dict['key-2'] = 'value-21'
add_update_dict['key-3'] = 'value-31'
print(f"add_update_dict: {add_update_dict}")


print("=== Delete dictionary using del ===")
del add_update_dict['key-2']
print(f"add_update_dict: {add_update_dict}")
del add_update_dict
#print(f"add_update_dict: {add_update_dict}") # NameError: name 'add_update_dict' is not defined


print("=== Dictionary Operations ===")
dict_1 = {'key-1':'value-1', 'key-2':'value-2', 'key-3':'value-3', 'key-4':'value-4'}
print(f"'key-1' in dict_1: {'key-1' in dict_1}")
print(f"'key-7' in dict_1: {'key-7' in dict_1}")

for key_elem in dict_1:
    print(f"dict_1[key_elem] {dict_1[key_elem]}")


print("=== Dictionary Built-in functions ===")
print(f"len(dict_1) {len(dict_1)}")
print(f"max(dict_1) {max(dict_1)}")
print(f"min(dict_1) {min(dict_1)}")
print(f"list(dict_1) {list(dict_1)}")
print(f"str(dict_1) {str(dict_1)}")

print(f"list(reversed(dict_1)): {list(reversed(dict_1))}")
print(f"list(iter(dict_1)): {list(iter(dict_1))}")


print("=== Dictionary Methods ===")
dict_1 = {'key-11':'value-11', 'key-12':'value-12', 'key-13':'value-13', 'key-14':'value-14'}
dict_2 = {'key-21':'value-21', 'key-22':'value-22', 'key-23':'value-23', 'key-24':'value-24'}

print(f"dict_2: {dict_2}")
dict_2.clear()
print(f"dict_2: {dict_2}")

dict_2 = dict_1.copy()
print(f"dict_2: {dict_2}")
dict_1['new-key'] = 'new-value'
print(f"dict_2: {dict_2}")

print(f"dict_1.items(): {dict_1.items()}")
print(f"dict_1.keys(): {dict_1.keys()}")
print(f"dict_1.values(): {dict_1.values()}")

print(f"dict_1: {dict_1}")
print(f"dict_1.popitem(): {dict_1.popitem()}")

print(f"dict_1.get('key-13'): {dict_1.get('key-13')}")
print(f"dict_1.get('key-13', 'custom-default value'): {dict_1.get('key-13', 'custom-default value')}")
print(f"dict_1.get('key-does-not-exist', 'custom-default value'): {dict_1.get('key-does-not-exist', 'custom-default value')}")
try:
    print(f"dict_1.get('key-does-not-exist'): {dict_1.get('key-does-not-exist')}")
except KeyError as keyerr:
    print(f"Exception while get {keyerr}")

print(f"dict_1: {dict_1}")
print(f"dict_1.pop('key-12'): {dict_1.pop('key-12')}")
print(f"dict_1.pop('key-13', 'custom-default value'): {dict_1.pop('key-13', 'custom-default value')}")
print(f"dict_1.pop('key-13', 'custom-default value'): {dict_1.pop('key-13', 'custom-default value')}")
try:
    print(f"dict_1.pop('key-13'): {dict_1.pop('key-13')}")
except KeyError as keyerr:
    print(f"Exception while pop {keyerr}")
print(f"dict_1: {dict_1}")

print(f"dict_1.setdefault('key-13', 'value-13'): {dict_1.setdefault('key-13', 'value-13')}")
print(f"dict_1.setdefault('key-13', 'value-13'): {dict_1.setdefault('key-13', 'value-13')}")
print(f"dict_1: {dict_1}")

dict_1 = {'key-11':'value-11', 'key-12':'value-12', 'key-13':'value-13', 'key-14':'value-14', 'key-same-11':'value-same-11', 'key-same-12':'value-same-12'}
dict_2 = {'key-21':'value-21', 'key-22':'value-22', 'key-23':'value-23', 'key-24':'value-24', 'key-same-11':'value-same-11', 'key-same-12':'value-same-12'}
print(f"dict_1: {dict_1}")
print(f"dict_2: {dict_2}")
dict_1.update(dict_2)
print(f"dict_1: {dict_1}")
print(f"dict_2: {dict_2}")

tup1 = ('py', 'th', 'on')
dict_2.update(tup1)
print(f"dict_2: {dict_2}")

#################
#   END OF FILE
#################