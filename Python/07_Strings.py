################################################
# 
# References
#     https://www.javatpoint.com/python-strings
#     https://docs.python.org/3/tutorial/introduction.html#strings
#     https://docs.python.org/3/tutorial/inputoutput.html#fancier-output-formatting
#     https://docs.python.org/3/library/stdtypes.html#textseq
#     https://docs.python.org/3/library/stdtypes.html#string-methods
# 
# String
#     is a standard data-type in Python
#     Strings are immutable
#     In Python 3, all strings are represented in Unicode
# 
# Creating String
#     ' or "  : enclose the characters in single-quotes or double-quotes
#     triple quites     : triple-quotes to represent the string, but it is generally used for multiline string or docstrings
#                         these strings are usually used for documentation
# 
# Strings indexing and splitting
#     [] can be used to acess string index or substring
#     index of string starts from 0
#     [index] to access a particular index
#     [lower:upper] range to access substring, upper is exclusive
#     -ve index starts from -1 and is used to access string elements in reverse 
#     P   Y   T   H   O   N
#     0   1   2   3   4   5   (+ve index)
#    -6  -5  -4  -3  -2  -1   (-ve index)
# 
# Reassigning Strings
#     strings are immutable and does not support assignment
#     updating the content of the strings is as easy as assigning it to a new string
#     a string can only be replaced with new string
# 
# Deleting using del
#     a string varible can be deleted using del statement
# 
# String Operators
#     Concatenation(+)	Adds values on either side of the operator
#     Repetition(*)       Creates new strings, concatenating multiple copies of the same string
#     Slice([])           Gives the character from the given index
#     Range Slice([:])    Gives the characters from the given range
#     Membership(in)      Returns true if a character exists in the given string
#     Membership(not in)  Returns true if a character does not exist in the given string
#     Raw String(r/R)     Suppresses actual meaning of Escape characters
#     Format(%)           Performs String formatting	See String formatting
# 
# Important String Methods
#     For detail visit    https://docs.python.org/3/library/stdtypes.html#string-methods
# 
#     lower()		Return a copy of the string with all the cased characters converted to lowercase
#     upper()		Return a copy of the string with all the cased characters 4 converted to uppercase
#     capitalize()	Return a copy of the string with its first character capitalized and the rest lowercased
#     casefold()		Return a casefolded copy of the string. Casefolded strings may be used for caseless matching
#     zfill(width)	Return a copy of the string left filled with ASCII '0' digits to make a string of length width
#     strip([chars])	Return a copy of the string with the leading and trailing characters removed
#     lstrip([chars])	
#         Return a copy of the string with leading characters removed. 
#         The chars argument is a string specifying the set of characters to be removed. chars defaults to whitespace
#     join(iterable)	
#         Return a string which is the concatenation of the strings in iterable. 
#         A TypeError will be raised if there are any non-string values in iterable, including bytes objects. 
#         The separator between elements is the string providing this method
#     index(sub[, start[, end]])	
#         Like find(), but raise ValueError when the substring is not found
#     endswith(suffix[, start[, end]])
#         Return True if the string ends with the specified suffix, otherwise return False. 
#         suffix can also be a tuple of suffixes to look for.
#     count(sub[, start[, end]])	
#         Return the number of non-overlapping occurrences of substring sub in the range [start, end]
#     find(sub[, start[, end]])	
#         Return the lowest index in the string where substring sub is found within the slice s[start:end]. Return -1 if sub is not found.
#     partition(sep)	
#         Split the string at the first occurrence of sep,
#         If the separator is     found, return a 3-tuple containing the part before the separator, the separator itself, and the part after the separator
#         If the separator is not found, return a 3-tuple containing the string itself, followed by two empty strings
# 
# 
# String Formatting
# 	Escape Sequence
# 		backslash(\) symbol denotes the escape sequence
# 		backslash can be followed by a special character and it interpreted differently
# 		An escape character gets interpreted; in a single quoted as well as double quoted strings
# 		
# 		Escape 		Description
# 		Sequence
# 		\newline	It ignores the new line.
# 		\\			Backslash
# 		\'			Single Quotes
# 		\\''		Double Quotes
# 		\a			ASCII Bell
# 		\b			ASCII Backspace(BS)
# 		\f			ASCII Formfeed
# 		\n			ASCII Linefeed(LF)
# 		\r			ASCII Carriege Return(CR)
# 		\t			ASCII Horizontal Tab
# 		\v			ASCII Vertical Tab
# 		\ooo		Character with octal value
# 		\xHH		Character with hex value.
# 		\s			Space
# 		\M-\C-x		Meta-Control-x
# 		\cx			Control-x
# 		\C-x		Control-x
# 		\e			Escape
# 
# 	The format() method
# 		curly braces {} are used as the placeholder in the string and replaced by the format() method argument
# 		
# 	String Formatting Using % Operator
# 		It uses format specifiers used in C's printf statement
# 		Python provides an additional operator %, which is used as an interface between the format specifiers and their values
# 		
# 		Specifier	Description
# 		%c			Character
# 		%s			string conversion via str() prior to formatting
# 		%i			signed decimal integer
# 		%d			signed decimal integer
# 		%u			unsigned decimal integer
# 		%o			octal integer
# 		%x			hexadecimal integer (lowercase letters)
# 		%X			hexadecimal integer (UPPERcase letters)
# 		%e			exponential notation (with lowercase 'e')
# 		%E			exponential notation (with UPPERcase 'E')
# 		%f			floating point real number
# 		%g			the shorter of %f and %e
# 		%G			the shorter of %f and %E
# 
################################################

print("=== Creating String ===")
empty_str = ""
print(f"type(empty_str): {type(empty_str)}")

name1 = 'this is a "name"'
name2 = "this is a 'name'"
print(f"name1: {name1}")
print(f"name2: {name2}")

multiline_str = """This is a multiline string
    and it will be processed as
it is"""
print(f"multiline_str: {multiline_str}")

two_str_in_line = "these two "      "will be concated"
print(f"two_str_in_line: {two_str_in_line}")

raw_str = r'This is a raw string and it will  \
be processed as it is no escape will be \n processed'
print(f"raw_str: {raw_str}")

long_str_in_parentheses = ('this is a long string in '
                            'multiple line. It will '
                            ' be joined together in single line')
print(f"long_str_in_parentheses: {long_str_in_parentheses}")


print("=== Strings indexing and splitting ===")
astr = 'an hour'
print(f"astr[0] {astr[0]}")
print(f"astr[6] {astr[6]}")
print(f"astr[-1] {astr[-1]}")
print(f"astr[-7] {astr[-7]}")

print(f"astr[0:] {astr[0:]}")
print(f"astr[3:] {astr[3:]}")
print(f"astr[:7] {astr[:7]}")
print(f"astr[:2] {astr[:2]}")
print(f"astr[3:7] {astr[3:7]}")

print(f"astr[-7:] {astr[-7:]}")
print(f"astr[-4:] {astr[-4:]}")
print(f"astr[:-1] {astr[:-1]}")
print(f"astr[:-5] {astr[:-5]}")
print(f"astr[-7:-5] {astr[-7:-5]}")

print(f"astr[::-1] {astr[::-1]}")


print("=== Reassigning Strings ===")
astr = "can not change this"
#astr[0] = 'C' # TypeError: 'str' object does not support item assignment
astr = "Can Not Change This"
print(f"astr: {astr}")


print("=== Deleting using del ===")
del astr
#print(f"astr: {astr}") # NameError: name 'astr' is not defined. Did you mean: 'str'?


print("=== String Operators ===")
str1 = 'sample string'
str2 = 'another string'
print(f"str1: {str1}")
print(f"str2: {str2}")
print(f"str1+str2: {str1 + str2}")
print(f"str1+str2: {str1 * 3}")
print(f"str1[2]: {str1[2]}")
print(f"str1[2:5]: {str1[2:5]}")
print(f"'o' in str1 {'o' in str1}")
print(f"'o' not in str1 {'o' not in str1}")
print(f"'o' in str2 {'o' in str2}")
print(f"'o' not in str2 {'o' not in str2}")
raw_string = r'this will be printed with escape \n sequence \t'
print(f"raw_string: {raw_string}")
val = 7
fstr = "this is a formatted string %d" %(val)
print(f"fstr: {fstr}")
print("this is same string formatted in diffrent style %d" %(val))

print("=== Important String Methods ===")
str1 = 'Title'
str2 = 'Camel Case'
print(f"str1: {str1}")
print(f"str2: {str2}")
print(f"str2.lower(): {str2.lower()}")
print(f"str2.upper(): {str2.upper()}")
print(f"str2.capitalize(): {str2.capitalize()}")
print(f"str2.casefold(): {str2.casefold()}")
print(f"str1.zfill(10): {str1.zfill(10)}")
str1 = 'strip this will remain strip'
print(f"str1.strip('strip') {str1.strip('strip')}")
print(f"str1.lstrip('strip') {str1.lstrip('strip')}")
astr = 'Python'
print(f"'@,'.join(astr) {'@,'.join(astr)}")
print(f"str1.endswith('strip'): {str1.endswith('strip')}")
print(f"str1.count('strip'): {str1.count('strip')}")
print(f"str1.find('strip'): {str1.find('strip')}")
print(f"str1.find('does-not-exist'): {str1.find('does-not-exist')}")
print(f"str1.index('remain'): {str1.index('remain')}")
try:
    print(f"str1.index('does-not-exist'): {str1.index('does-not-exist')}")
except ValueError as verr:
    print(f"Failed to fins sub-string, Error: {verr}")
print(f"str1.partition('remain'): {str1.partition('remain')}")


print("=== Escape Sequence ===")
astr = "This is a string with multiple escape sequence like a tab \t a vertical tab \v  a new line \n printing an octal value \123\125\120 printing a hexadecimal value \xA9\x3F"
print(f"astr: {astr}")

print("=== The format() method ===")
print('"{} has got {} marks".format("Ramesh", 98)')
astr = "{} has got {} marks".format("Ramesh", 98) # Using Curly braces
print(astr)
print()

print('"Highest {1} makr was obtained by {0}".format("Ramesh", 98)')
astr = "Highest {1} makr was obtained by {0}".format("Ramesh", 98) #Positional Argument
print(astr)
print()

print('"{name} student of {standard} has got {mark} marks".format(name="Ramesh", mark=98, standard="12th")')
astr = "{name} student of {standard} has got {mark} marks".format(name="Ramesh", mark=98, standard="12th") #Keyword Argument
print(astr)
print()

print("=== String Formatting Using % Operator ===")
print('"%s has got %d marks" %("Ramesh", 98)')
astr = "%s has got %d marks" %("Ramesh", 98)
print(astr)


print("=== Formatted String Literals ===")
name='Ramesh'
mark=89
standard='12th'
print(f'{name} of {standard} got {mark} mark')
print(f'Student {name=} of {standard=} got {mark=}')

student_table = {'student-1':55, 'student-2':65, 'student-3':85}
for name,mark in student_table.items():
    print(f'{name:10} got {mark:03d} mark')

#################
#   END OF FILE
#################

