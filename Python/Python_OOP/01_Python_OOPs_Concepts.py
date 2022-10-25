"""

References:
https://www.javatpoint.com/python-oops-concepts
    
Python OOPs Concepts

Python is also an object-oriented language
OOP Principle:
    Class
    Object
    Method
    Inheritance
    Polymorphism
    Data Abstraction
    Encapsulation

Class:
    The class can be defined as a collection of objects. It is a logical entity that has some specific attributes and methods. 
    For example: if you have an employee class, then it should contain an attribute and method, i.e. an email id, name, age, salary, etc.
    
    Syntax:
    class ClassName:     
        <statement-1>     
        .     
        .      
        <statement-N> 
        
Object:
    The object is an entity that has state and behavior. 
    Everything in Python is an object, and almost everything has attributes and methods. 
    All functions have a built-in attribute __doc__, which returns the docstring defined in the function source code.
    When we define a class, it needs to create an object to allocate the memory.
    
    Syntax:
    c1 = car("Toyota", 2016)    // defining an object
    c1.display()                // calling a method
    
Method:
    The method is a function that is associated with an object. 
    In Python, a method is not unique to class instances. Any object type can have methods.

Inheritance:
    By using inheritance, we can create a class which uses all the properties and behavior of another class. The new class is known as a derived class or child class, and the one whose properties are acquired is known as a base class or parent class.
    It provides the re-usability of the code.

Polymorphism:
    By polymorphism, we understand that one task can be performed in different ways.
    
Encapsulation:
    It is used to restrict access to methods and variables. 
    In encapsulation, code and data are wrapped together within a single unit from being modified by accident.

Data Abstraction:
    Data abstraction and encapsulation both are often used as synonyms. Both are nearly synonyms because data abstraction is achieved through encapsulation.

"""