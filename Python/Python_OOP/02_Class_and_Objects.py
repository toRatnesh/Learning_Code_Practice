"""

Class and Objects

Reference:
https://www.javatpoint.com/python-objects-classes
    
Class:
    A class is a virtual entity and can be seen as a blueprint of an object. The class came into existence when it instantiated.
    
Object:
    The object is the instance of a class. The process of creating an object can be called instantiation.

Creating classes in Python:
    
    Syntax:
    class ClassName:    
        #statement_suite

    Each class is associated with a documentation string which can be accessed by using <class-name>.__doc__. 
    A class contains a statement suite including fields, constructor, function, etc. definition.

    The self-parameter:
    The self is used as a reference variable, which refers to the current instance of the class and accesses the class variables.
    We can use anything instead of self, but it must be the first parameter of any function which belongs to the class.
    However, using self is optional in the function call.

    Static method does not need self.

Creating an instance of the class:

    Syntax:
    <object-name> = <class-name>(<arguments>) 

Delete the Object:
    We can delete the properties of the object or object itself by using the del keyword

    Syntax:
    del <attribute>
"""

# class
class Student:
    stid = 10
    name = "Student-10"

    def display1(self):
        print(self.stid, self.name)

    def display2(me):    # using me instead of self
        print(me.stid, me.name)

    def display3():
        print("This function does not uses self")

# object
st = Student()
st.display1()
st.display2()

# delete
st2 = Student()
st2.display1()

Student.display3()

del Student.stid
#delattr(Student, 'stid')  # AttributeError: stid

del st2
#st2.display1()  # NameError: name 'st2' is not defined. Did you mean: 'st'?


###################
#   END OF FILE
###################