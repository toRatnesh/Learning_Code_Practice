"""

Rererences:
https://www.javatpoint.com/inheritance-in-python

Python Inheritance

1. Inheritance
    Inheritance provides code reusability to the program because we can use an existing class to create a new class instead of creating it from scratch.
    In inheritance, the child class acquires the properties and can access all the data members and functions defined in the parent class. 
    A child class can also provide its specific implementation to the functions of the parent class.

    Base Class
        ^
        |
        |
    Derived Class

    Syntax
        class derived-class(base class):  
            <class-suite> 

2. Multi-Level inheritance
    Multi-level inheritance is archived when a derived class inherits another derived class. 
    There is no limit on the number of levels up to which, the multi-level inheritance is archived in python.

    Syntax
        class class1:  
            <class-suite>   
        class class2(class1):  
            <class suite>  
        class class3(class2):  
            <class suite>

3. Mutiple Inheritance
    A class can inherit multiple classes by mentioning all of them inside the bracket.

    Syntax
        class Base1:  
            <class-suite>  
        class Base2:  
            <class-suite>  
        .
        .
        class BaseN:  
            <class-suite>  
        
        class Derived(Base1, Base2, ...... BaseN):  
            <class-suite>

issubclass(sub,sup) method
    It returns true if the first class is the subclass of the second class, and false otherwise

isinstance (obj, class) method
    It returns true if the first parameter, i.e., obj is the instance of the second parameter, i.e., class.

Method Overriding
    When the parent class method is defined in the child class with some specific implementation, then the concept is called method overriding.

Data abstraction in python
    In python, we can also perform data hiding by adding the double underscore (___) as a prefix to the attribute which is to be hidden. After this, the attribute will not be visible outside of the class through the object.

"""

class Base_1:
    def __init__(self):
        print("Base 1 initialized")

    def fun(self):
        print("Inside Base 1 fun")

class Base_2:
    def __init__(self):
        print("Base 2 initialized")

    def fun(self):
        print("Inside Base 2 fun")

# 1 Inheritance
class Derived_1(Base_1):
    def __init__(self):
        print("Derived 1 initialized")

    def fun(self):  # overriding Base_1's fun() method
        print("Inside Derived 1 fun")

d1 = Derived_1()
d1.fun()

# 2 Multilevel Inheritance
class Derived_21(Base_1):
    def __init__(self):
        print("Derived 21 is initialized")
    
    def fun(self):
        print("Inside derived 21 fun")

class Derived_22(Derived_21):
    def __init__(self):
        print("Derived 22 is initialized")
    
    def fun(self):
        print("Inside derived 22 fun")

d22 = Derived_22()
d22.fun()

# 3 Multiple Inheritance
class Derived_3(Base_1, Base_2):
    def __init__(self):
        print("Derived 3 initialized")

    def fun(self):
        print("Inside Derived 3 fun")

d3 = Derived_3()
d3.fun()

print(issubclass(Derived_1, Base_1));
print(issubclass(Derived_3, Derived_21));

print(isinstance(d3, Derived_3));
print(isinstance(d1, Derived_3));

class DataAbstraction:
    __data = 0;

    def __init__(self):
        __data = 5
    
    def display(self):
        print("Data value is ", DataAbstraction.__data) # AttributeError: 'DataAbstraction' object has no attribute '__data'

dabs = DataAbstraction()
try:
    print(dabs.__data)
finally:
    dabs.display()
    

##################
#   END OF FILE
##################