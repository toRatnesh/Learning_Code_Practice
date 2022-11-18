#######################
#
# References:
#   https://www.javatpoint.com/python-generators
#   https://docs.python.org/3/tutorial/classes.html#generators
#   https://docs.python.org/3/tutorial/classes.html#generator-expressions
#
# Generators
#   Generators are the functions that return the traversal object and used to create iterators.
#   It traverses the entire items at once.
#   
#   Generators simplify the process of creating iterators
#   If there is no value found in iteration, it raises StopIteration exception.
#
#   Generators are written like regular functions but use the yield statement whenever they want to return data. 
#   Each time next() is called on it, the generator resumes where it left off
#   local variables and execution state are automatically saved between calls.

#   Generators have advantage over class-based iterators that __iter__() and __next__() methods are created automatically.
#
# Create Generator
#   It is similar to the normal function defined by the def keyword and uses a yield keyword instead of return.
#   
#   yield vs. return
#       yield pauses a function execution, muitple yield statement can be used
#       return  returns a value and terminates the whole function, only one return statement can be used
#
#
# Generator expression
#   Generator's expressions create an anonymous generator function, same as the lambda function creates an anonymous function
#   Its representation is similar to the Python list comprehension, with difference of
#   Generator expression uses () and calculates one item at a time
#
# Advantages of Generators
#   1. Easy to implement:
#	    Generators automatically implement __iter__() and __next__() function
#   2. Memory efficient:
#   	Generators are memory efficient for a large number of sequences
#   	Normal function creates an entire sequence in memory before returning the result, but 
#   	the generator function calculates the value and pause their execution
#   	It resumes for successive call.
#   3. Pipelining with Generators
#   	Data Pipeline provides the facility to process large datasets or stream of data without using extra computer memory.
#   4. Generate Infinite Sequence
#   	Since infinite sequences cannot be contained within the memory
#   	As generators produce only one item at a time, It can be used to generate infinite sequence
#
#######################

print(f"=== Generator with single yield statement  ===")
def generator_fun():
    for i in range(10):
        if(0 == (i%2)):
            yield i

for elem in generator_fun():
    print(f"{elem}", end=", ")
print(f"")

print(f"=== Generator with multiple yield statement  ===")
def generator_fun():
    for i in range(10):
        if(0 == (i%2)):
            yield i
        else:
            yield i*i

for elem in generator_fun():
    print(f"{elem}", end=", ")
print(f"")

def generator_fun():
    str="First time called"
    yield str
    str="Second time called"
    yield str
    str="Third time called"
    yield str

gf = generator_fun()
print(f"{gf}")
try:
    # NOTE: When we call the next(), Python calls __next__() on the function in which we have passed it as a parameter.
    print(f"next(gf) {next(gf)}")
    print(f"next(gf) {next(gf)}")
    print(f"next(gf) {next(gf)}")
    print(f"next(gf) {next(gf)}")
except StopIteration as sie:
    print(f"Genrator function execution completed, {sie}")


print(f"=== Generator expression ===")
alist = [1, 2, 3, 4, 5]
alist_comph = [x**x for x in alist]
print(f"alist_comph {alist_comph}")

agen_exp = (x**x for x in alist)
print(f"agen_exp {agen_exp}")
print(f"\Iterating using next()")
try:
    print(f"next(agen_exp) {next(agen_exp)}")
    print(f"next(agen_exp) {next(agen_exp)}")
    print(f"next(agen_exp) {next(agen_exp)}")
    print(f"next(agen_exp) {next(agen_exp)}")
    print(f"next(agen_exp) {next(agen_exp)}")
    print(f"next(agen_exp) {next(agen_exp)}")
except StopIteration as sie:
    print(f"Genrator expression execution completed, {sie}")
# only one will work at a time next() or for loop so to print using for loop comment iteration using next()
print(f"Iterating using for loop")
for elem in agen_exp:
    print(f"{elem}", end=", ")


import sys
print(f"=== Memory efficiency using Generator  ===")
alist_comph = [x**x for x in range(1000)]
agen_exp    = (x**x for x in range(1000))
print(f"Memory by list comprehension {sys.getsizeof(alist_comph)}")
print(f"Memory by generator expression {sys.getsizeof(agen_exp)}")


##################
#   END OF FILE
##################
