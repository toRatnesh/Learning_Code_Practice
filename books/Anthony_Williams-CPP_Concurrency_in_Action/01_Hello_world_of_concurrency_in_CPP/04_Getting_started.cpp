/*******

References
Book | Anthony Williams - C++ Concurrency in Action

1. Hello, world of concurrency in C++

1.4 Getting started
	In order to run functions concurrently, specific functions and objects must be used to manage the different threads.

	1.4.1 Hello, Concurrent World

		Following Example
        #include <thread> - the functions and classes for managing threads are declared in <thread>
        std::thread object named thr
        
        After the new thread has been launched, the initial thread continues execution.
        If it didn’t wait for the new thread to finish, 
        it would merrily continue to the end of main() 
        and end the program—possibly before the new thread had a chance to run. 
        
        This is why the call to join() is there, 
        this causes the calling thread (in main()) to 
        wait for the thread associated with the std::thread object, in this case, thr.
	
***********/

#include <iostream>
#include <thread>       // heade

void printMsg() {
    std::cout << "Learning multithreading\n";
}

int main() {
    std::thread thr(printMsg);
    thr.join();
    return 0;
}

/*******
	END OF FILE
***********/
