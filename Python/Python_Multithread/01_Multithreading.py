##################################
# 
# Referencs:
#     https://www.javatpoint.com/multithreading-in-python-3
#     https://docs.python.org/3/library/threading.html
#
# Python Multithreading
#
#   A thread is a single sequence stream within in a process. 
# 	Because threads have some of the properties of processes, 
# 	they are sometimes called lightweight processes.
#
#   Multiple threads run concurrently by rapidly switching between threads 
# 	with a CPU help called context switching.
#   
#   Multithreading allows sharing of its data space with the main threads 
# 	inside a process that share information and communication with other threads
# 	easier than individual processes.
#
#   The Python Global Interpreter Lock (GIL) allows running a single thread 
# 	at a time, even the machine has multiple processors.
#
#   Advantage of Multithreading
#	- increased preformance and speed
#	- shares resources and its state with child threads
#	- less utilization of memory to store multiple threads
#
#
#   Threading Modules
#	threading module is a high-level implementation of multithreading
#
#   Threading Class Methods
#
#	Methods    	Description
#	start()		used to initiate the activity of a thread, 
#			it calls only once for each thread so that the execution of the thread can begin
#	run()		used to define a thread's activity and 
#			can be overridden by a class that extends the threads class
#	join()		used to block the execution of another code 
#			until the thread terminates
#
#   Steps to implement multithreading
#
#   1. Import the threading module
#   	threading module is made up of a Thread class, 
#   	which is instantiated to create a Python thread
#   
#   2. Declaration of the thread parameters
#   	It contains the target function, argument, and kwargs 
#   	as the parameter in the Thread() class.
#
#   	Target: It defines the function name that is executed by the thread
#   	Args:   It defines the arguments that are passed to the target function name
#
#   3. Start a new thread
#   	To start a thread in Python multithreading, call start() method on thread class's object. 
#   	The start() method can be called once for each thread object; otherwise, it throws an exception error.
#
#   4. Join method
#   	used to halt the main thread's execution 
#   	and waits till the complete execution of the thread object.
#
#   5. Synchronizing Threads in Python
#   	Thread synchronization mechanism ensures no two threads can simultaneously execute 
#   	a particular segment inside the program to access the shared resources (critical sections). 
#   	We use a race condition to avoid the critical section condition, 
#   	in which two threads do not access resources at the same time.
#
##################################

import threading
import time

def get_square(nums):
    for anum in nums:
        print(f"square of {anum} is {anum * anum}")
        time.sleep(0.2)

def get_cube(nums):
    for anum in nums:
        print(f"cube of {anum} is {anum * anum * anum}")
        time.sleep(0.2)

alist = [2,3,4,5,6]
print("=== Wihtout multithreading")
start_time = time.time()
get_square(alist)
get_cube(alist)
end_time = time.time()
print(f"time taken : {end_time - start_time}")

print("")
print("=== With multithreading")
start_time = time.time()
sq_th   = threading.Thread(target=get_square,   args=(alist, ))
cube_th = threading.Thread(target=get_cube,     args=(alist, ))
sq_th.start()
cube_th.start()
sq_th.join()
cube_th.join()
end_time = time.time()
print(f"time taken : {end_time - start_time}")

##################
#   END OF FILE
##################



