############################
# 
# References
#     https://www.javatpoint.com/python-loops
#     https://www.javatpoint.com/python-while-loop
#     https://www.javatpoint.com/python-for-loop
#     https://docs.python.org/3/tutorial/controlflow.html
# 
#     https://www.javatpoint.com/python-break
#     https://www.javatpoint.com/python-continue
#     https://www.javatpoint.com/python-pass
#     https://docs.python.org/3/tutorial/controlflow.html#break-and-continue-statements-and-else-clauses-on-loops
#     https://docs.python.org/3/tutorial/controlflow.html#pass-statements
# 
# Loop
#     A loop statement allows to execute statement(s) multiple times
# 
# Types of loops in Python
#     1. while loop   | Repeats statement(s) while a given condition is TRUE
#                         It tests the condition before executing the loop body
#     2. for loop	    | Executes a sequence of statements multiple times and abbreviates the code that manages the loop variable
#     3. nested loops | One or more loop inside any another while, or for loop
# 
# While loop
#     Syntax
#     while expression:
#         statement(s)
# 
# For loop
#     Syntax
#     for iterating_var in sequence:
#         statements(s)
# 
# Using else Statement with Loops
#     Python supports having an else statement associated with a loop statement
#     When used with a while(or for) loop, the else statement is executed when the condition becomes false
# 
# 
# Loops Control Statements
#     Loop control statements change the execution from its normal sequence.
#     When the execution leaves a scope, all automatic objects that were created in that scope are destroyed.
# 
#     1. break statement      | Terminates the loop statement and transfers execution to the statement immediately following the loop.
#     2. continue statement   | Causes the loop to skip the remainder of its body and immediately retest its condition prior to reiterating.
#     3. pass statement       | used when a statement is required syntactically but you do not want any command or code to execute.
# 
# 1. break statement
#     Used for premature termination of the current loop
#     After abandoning the loop, execution at the next statement is resumed
# 
# 2. continue statement
#     Returns the control to the beginning of the current loop
#     When encountered, the loop starts next iteration without executing the remaining statements in the current iteration
# 
# 3. pass statement
#     It is used when a statement is required syntactically but you do not want any command or code to execute
#     The pass statement is a null operation; nothing happens when it executes
#     The pass statement is also useful in places where your code will eventually go, but has not been written yet i.e. in stubs
# 
############################

print("=== while loop ===")
count = 0
while (count < 5):
	print(f"Count is: {count}")
	count = count + 1

print("=== for loop ===")
for var in [1, 2, 3, 4, 5]:
	print(f"Var: {var}")

print("=== while loop with else ===")
count = 0
while count < 5:
	print(f"{count} is  less than 5")
	count = count + 1
else:
	print("Loop Over")

print("=== for loop with else ===")
for count in range(5):
	print(f"{count} is n range(5)")
	count = count + 1
else:
	print("Loop Over")

print("=== break statement ===")
for letter in 'Python':
	if letter == 'h':
		break
	print(f"Current Letter: {letter}")

print("=== continue statement ===")
for letter in 'Python':
	if letter == 'h':
		continue
	print(f"Current Letter: {letter}")

print("=== pass statement ===")
for letter in 'Python':
    if 'h' == letter:
        pass
    else:
        print(f"Current Letter: {letter}")

#################
#   END OF FILE
#################

