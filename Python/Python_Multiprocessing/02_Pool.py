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
# Python Multiprocessing Pool
# 	pool is essential for parallel execution of a function across multiple input values
# 	used to distribute the input data across processes (data parallelism)
# 
##################################

import multiprocessing
import time

def check_even(num):
    if 0 == num%2:
        msg = f"Process-{multiprocessing.current_process().name}, {num} is even"
    else:
        msg = f"Process-{multiprocessing.current_process().name}, {num} is odd"
    return msg

def process_using_pool():
    data = [1,3,4,5,7,8,9]
    prc_pool = multiprocessing.Pool(3)
    res = prc_pool.map(check_even, data)
    print(f"{res}")
    for elem in res:
        print(f"{elem}")


def main():

    print(f"This system has {multiprocessing.cpu_count()} CPU") 

    print("")
    print("=== Multiprocessing using Pool")
    process_using_pool()


if __name__ == '__main__':
    main()


##################
#   END OF FILE
##################
