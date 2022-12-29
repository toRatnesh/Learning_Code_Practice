##################################
# 
# Referencs:
#   https://www.javatpoint.com/python-multiprocessing
#   https://docs.python.org/3/library/multiprocessing.html
#
# What is Multiprocessing?
#   to run one or more processes in parallel
#   uses the two or more CPU
#   capable to allocate the tasks between more than one process
# 
#   Processing units share the main memory and peripherals to process programs simultaneously.
#   Multiprocessing Application breaks into smaller parts and runs independently. 
#
# Multiprocessing In Python
#   multiprocessing module provides many classes which are commonly used for building parallel program
#   main classes - Process, Queue and Lock
#
# Commonly Used Functions of Multiprocessing
#   pipe()			returns a pair of connection objects
#   run()			to represent the process activities
# 
#   is_alive()		check if process is alive
#   terminate()		to terminate the process on Linux
#   TerminateProcess()	to terminate the process on Windows
#   kill()			to the terminate() but using the SIGKILL signal on Unix
#   close()			to close the Process object and releases all resources associated with it
# 
#   cpu_count()		returns the number of working CPU within the system
#   task_done()		used to indicate that an enqueued task is completed
#   join_thread()	used to join the background thread
#   current_process()	It returns the Process object corresponding to the current process
#   parent_process()	It returns the parent Process object corresponding to the current process
#
#
# Proxy Objects
# 	proxy objects are referred to as shared objects which reside in a different process
# 	The shared object is said to be the referent of the proxy
# 	Multiple proxy objects may have the same referent
# 
# 	A proxy object has methods which invoke corresponding methods of its referent (although not every method of the referent will necessarily be available through the proxy). In this way, a proxy can be used just like its referent can
#
#   applying str() to a proxy will return the representation of the referent, 
#   whereas applying repr() will return the representation of the proxy.
# 
##################################

import multiprocessing
import time
import queue

def main():

    print(f"This system has {multiprocessing.cpu_count()} CPU") 

    print("")
    print("=== Proxy Objects")
    manager = multiprocessing.Manager()
    list_squares = manager.list([i*i for i in range(10)])
    print(f"{list_squares}")
    print(f"{list_squares[4]}")
    print(f"{list_squares[2:6]}")
    print(f"repr(list_squares) {repr(list_squares)}")
    print(f"str(list_squares) {str(list_squares)}")

if __name__ == '__main__':
    main()


##################
#   END OF FILE
##################
