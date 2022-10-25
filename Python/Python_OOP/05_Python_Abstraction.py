"""

References:
https://www.javatpoint.com/abstraction-in-python

Abstraction in Python

Abstraction in Python
    Abstraction is used to hide the internal functionality of the function from the users. The users only interact with the basic implementation of the function, but inner working is hidden.

Why Abstraction is Important?
    In Python, an abstraction is used to hide the irrelevant data/class in order to reduce the complexity. It also enhances the application efficiency.

Abstraction classes in Python
    In Python, abstraction can be achieved by using abstract classes and interfaces.
    A class that consists of one or more abstract method is called the abstract class. 
    Abstract methods do not contain their implementation. 
    Abstract class can be inherited by the subclass and abstract method gets its definition in the subclass. 

    Abstraction classes are meant to be the blueprint of the other class. 
    An abstract class can be useful when we are designing large functions. 
    An abstract class is also helpful to provide the standard interface for different implementations of components. 

    Python provides the abc module to use the abstraction in the Python program. 

    Syntax
        from abc import ABC  
        class ClassName(ABC):

Abstract Base Classes
    An abstract base class is the common application program of the interface for a set of subclasses. 
    It can be used by the third-party, which will provide the implementations.

Working of the Abstract Classes
    Unlike the other high-level language, Python doesn't provide the abstract class itself. 
    We need to import the abc module, which provides the base for defining Abstract Base classes (ABC). 
    
    The ABC works by decorating methods of the base class as abstract. 
    It registers concrete classes as the implementation of the abstract base. 
    We use the @abstractmethod decorator to define an abstract method or if we don't provide the definition to the method, it automatically becomes the abstract method.

Points to Remember
    An Abstract class can contain the both method normal and abstract method.
    An Abstract cannot be instantiated; we cannot create objects for the abstract class.

"""

# Python program to define   
# abstract class  
  
from abc import ABC  
  
class Polygon(ABC):
    # abstract method   
    def sides(self):
        pass

class Triangle(Polygon):
    def sides(self):
        print("Triangle has 3 sides")
  
class Hexagon(Polygon):
    def sides(self):
        print("Hexagon has 6 sides")

class square(Polygon):
    def sides(self):
        print("Square have 4 sides")   
  
# Driver code
t = Triangle()
t.sides()

s = square()
s.sides()

k = Hexagon()
k.sides()

####################
#   END OF FILE
####################