######################################
# 
# References
#     https://www.javatpoint.com/python-magic-method
# 
# Magic Methods
#     "magic methods" are special methods which improve the structure of our classes
#     __init__, __new__, __add__
# 
# __init__ Method
#     After construction of an instance of the class, but before that instance is returned to the caller of the class, the _init_ method is executed
#     _init_ method is invoked after _new_ and therefore are referred to as initialising
#     We should define the instance parameters here
# 
# __new__() Method
#     __new__() is called implicitly by the __init__() method. The new instance returned by the __new__() method is initialised
#     to modify the creation of objects in a user-defined class, define __new__() magic method
#     __new__() method is static method
#     first argument to __new__() method is the reference to the class whose object is to be created 
# 
# __add__ Method
#     It is used to add two attributes of two instances of different classes
# 
# __repr__ Method
# 	It represents a class instance as a string, which is produced as its output
# 	It is automatically called whenever we attempt to print an object of that class
# 
# __contains__ Method
#     The 'in' membership operator of Python implicitly calls the __contains__ method
#     It can beused to determine if an element is contained in an object's attributes
# 
# __call__ Method
#     When a class instance is called, the Python interpreter calls the method __call__
# 
# __iter__ Method
#     For the given instance, a generator object is supplied using the __iter__ method
#     To benefit from the __iter__ method, we can leverage the iter() and next() methods
# 
######################################

print("=== __init__ method ===")
class InitMethod:
    def __init__(self, *args):
        self.m0 = args[0]
        self.m1 = args[1]

init_m = InitMethod("init-method", 5)
print(f"init_m {init_m}")
print(f"init_m.m0 {init_m.m0} init_m.m1 {init_m.m1}")


print("=== __new__ method ===")
class CustomizedNew:
    def __new__(cls):
        print("Customized __new__ method")
        return super(CustomizedNew, cls).__new__(cls)

    def __init__(self):
        print("Initializing after new")

cnew = CustomizedNew()


print("=== __add__ Method ===")
class Method1:
    def __init__(self, parm):
        self.m = parm
    def __add__(self, obj):
        return self.m + obj.m

class Method2:
    def __init__(self, parm):
        self.m = parm
    #def __add__(self, obj):
    #    return self.m + obj.m

m1 = Method1(11)
m2 = Method2(12)

print(f"m1+m2 {m1+m2}")
#print(f"m2+m1 {m2+m1}") # TypeError: unsupported operand type(s) for +: 'Method2' and 'Method1'
# to support m2+m1 we need to define __add__ in class of m2

# if __add__ is not defined
print(f"m2.m + m1.m {m2.m + m1.m}")
print(f"m1.m + m2.m {m1.m + m2.m}")


print("=== __repr__ Method ===")
class ReprMethod:
    def __init__(self, *args):
        self.name = args[0]
        self.age = args[1]
        self.department = args[2]

    def __repr__(self):
        retstr = f"name: {self.name},  age: {self.age}, department: {self.department}"
        return retstr

repr_m = ReprMethod("overriding-repr", 2, "learning")
print(f"repr_m: {repr_m}")


print("=== __contains__ Method ===")
class ContainsMethod:
    def __init__(self, parm):
        self.m = parm
    
    def __contains__(self, parm):
        return parm in self.m

cont_m = ContainsMethod((1, 2.5, True, 'word'))
print(f"2.5 in cont_m {2.5 in cont_m}")
print(f"'word' in cont_m {'word' in cont_m}")
print(f"3 in cont_m {3 in cont_m}")


print("=== __call__ Method ===")
class CallMethod:
    def __init__(self, parm):
        self.m = parm

    def __call__(self, parm):
        return self.m * parm

callm_m = CallMethod([1, 2, 3])
print(f"callm_m(3) {callm_m(3)}")


print("=== __iter__ Method ===")
class IterMethod:
    def __init__(self, start, stop):
        self.start = start
        self.stop = stop
    
    def __iter__(self):
        for num in range(self.start, self.stop):
            yield num ** 2

iter_obj = IterMethod(4, 10)
iter_m = iter(iter_obj)
print(f"next(iter_m) {next(iter_m)}")
print(f"next(iter_m) {next(iter_m)}")
print(f"next(iter_m) {next(iter_m)}")
print(f"next(iter_m) {next(iter_m)}")
print(f"next(iter_m) {next(iter_m)}")
print(f"next(iter_m) {next(iter_m)}")

#################
#   END OF FILE
#################

