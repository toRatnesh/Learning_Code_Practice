"""
Python Constructor
constructor is used to initialize the instance members of the class

Constructors types.
    1. Parameterized Constructor
        constructor has multiple parameters along with the self
        def __init__(self, name):
            print("This is parametrized constructor")
            self.name = name 

    2. Non-parameterized Constructor
        constructor that has only self as an argument
        def __init__(self):
            print("This is non parametrized constructor")

Creating the constructor
    The method __init__() simulates the constructor of the class.
    This method is called when the class is instantiated.
    It accepts the self-keyword as a first argument which allows accessing the attributes or method of the class.

Default Constructor
    When we do not include the constructor
    It does not perform any task but initializes the objects

Mutiple Constructor
    Constructor overloading is not allowed in Python.
    Internally, the object of the class will always call the last constructor if the class has multiple constructors.

Built-in class functions
    1	getattr(obj,name,default)	It is used to access the attribute of the object.
    2	setattr(obj, name,value)	It is used to set a particular value to the specific attribute of an object.
    3	delattr(obj, name)	        It is used to delete a specific attribute.
    4	hasattr(obj, name)	        It returns true if the object contains some specific attribute.

Built-in class attributes
    1	__dict__	It provides the dictionary containing the information about the class namespace.
    2	__doc__	    It contains a string which has the class documentation
    3	__name__	It is used to access the class name.
    4	__module__	It is used to access the module in which, this class is defined.
    5	__bases__	It contains a tuple including all base classes.

"""

class MovieTicket:
    category = "DEFAULT"
    price = 0

    def __init__(self, category, price):
        self.category   = category
        self.price      = price

    def display(self):
        print(f"category {self.category}, price {self.price}")

    def display2():
        print(f"category {MovieTicket.category}, price {MovieTicket.price}")


premcls = MovieTicket ("premium", 250)
premcls.display()
MovieTicket.display2()


class DefaultConstructor:
    value = 10

    def update(self, val):
        self.value = val

    def display(self):
        print(f"Value {self.value}")

    def display2():
        print(f"Value {DefaultConstructor.value}")

dc = DefaultConstructor()
dc.display()
DefaultConstructor.display2()

DefaultConstructor.value = 15
dc.display()
DefaultConstructor.display2()

dc.update(13)
dc.display()
DefaultConstructor.display2()


class MultipleConstructor:
    def __init__(self):
        print("Non-parameterized constructor")

    def __init__(self, val):
        value = val

#mc1 = MultipleConstructor() # TypeError: MultipleConstructor.__init__() missing 1 required positional argument: 'val'


class BultInFunAndAttr:
    def __init__(self, name, id):
        self.name   = name
        self.id     = id

    def display(self):
        print(f"name {self.name}, id {self.id}")

binfa = BultInFunAndAttr("Built-in", 12)
binfa.display()

print(getattr(binfa, 'name'))
setattr(binfa, 'id', 32)
print(getattr(binfa, 'id'))

print(hasattr(binfa, 'id'))
delattr(binfa, 'id')
print(hasattr(binfa, 'id'))
print(hasattr(binfa, 'doesnotexist'))

binfa = BultInFunAndAttr("Built-in", 12)
print(binfa.__dict__)
print(binfa.__doc__)
#print(binfa.__name__)
print(binfa.__module__)
#print(binfa.__bases__)

###################
#   END OF FILE
###################