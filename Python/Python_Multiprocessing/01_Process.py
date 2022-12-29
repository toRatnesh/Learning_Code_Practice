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
# Python Multiprocessing Process Class
#   Process class is used to create process object. It has following methods
#   start()			to start the process
#   join([timeout])	to block the process until the process whose join() method is called terminates
#
# 
# Python Multiprocessing Queue Class
#   Queue is used to store Python object and share data between processes
#   get()			to get elements from the queue. It removes and returns an element from queue.
#   put()			to insert an element into the queue
#   get_await()		This method is equivalent get(False)
#   empty()			If queue is empty, it returns True
#   full()			If queue is full, it returns True
#   qsize()			returns the approximate size of the queue.
#
# 
# Python Multiprocessing Lock Class
#   used to acquire a lock on the process so that we can hold the other process to execute a similar code until the lock has been released
#   acquire()	to acquire a lock
#   release()	to release the lock
#
# Python Multiprocessing Pool
# 	pool is essential for parallel execution of a function across multiple input values
# 	used to distribute the input data across processes (data parallelism)
# 
##################################

import multiprocessing
import time
import queue

def get_square(nums):
    for anum in nums:
        print(f"square of {anum} is {anum * anum}")
        time.sleep(0.2)

def get_cube(nums):
    for anum in nums:
        print(f"cube of {anum} is {anum * anum * anum}")
        time.sleep(0.2)

alist = [2,3,4,5,6]

def get_sum(atuple):
    res_sum = atuple[0] + atuple[1]
    return res_sum

def process_routine(data_que, res_que):
    while True:
        try:
            atuple = data_que.get_nowait()
        except queue.Empty:
            break
        else:
            res_val = get_sum(atuple)
            msg = f"{res_val} is calculated by {multiprocessing.current_process().name}"
            res_que.put(msg)

def process_using_queue():
    data_que    = multiprocessing.Queue()
    res_que     = multiprocessing.Queue()
    prcs_list   = []
    total_process = 5

    for i in range(25):
        data_que.put((i,i+2))

    for i in range(total_process):
        prc = multiprocessing.Process(target=process_routine, args=(data_que, res_que))
        prcs_list.append(prc)
        prc.start()

    for prc in prcs_list:
        prc.join()

    while not res_que.empty():
        print(res_que.get())


def main():

    print(f"This system has {multiprocessing.cpu_count()} CPU") 

    print("")
    print("=== Without multiprocessing")
    start_time = time.time()
    get_square(alist)
    get_cube(alist)
    end_time = time.time()
    print(f"time taken : {end_time - start_time}")

    print("")
    print("=== With multiprocessing")
    start_time = time.time()
    sq_prc   = multiprocessing.Process(target=get_square,   args=(alist, ))
    cube_prc = multiprocessing.Process(target=get_cube,     args=(alist, ))
    sq_prc.start()
    cube_prc.start()
    sq_prc.join()
    cube_prc.join()
    end_time = time.time()
    print(f"time taken : {end_time - start_time}")

    print("")
    print("=== Multiprocessing using Queue")
    process_using_queue()


if __name__ == '__main__':
    main()


##################
#   END OF FILE
##################
