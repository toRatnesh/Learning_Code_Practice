/*******

References
    Anthony Williams - C++ Concurrency in Action

2 Managing threads

    The C++ Standard Library makes most thread-management tasks relatively easy, 
    with almost everything managed through the std::thread object associated with a given thread.

2.5 Identifying threads

	Thread identifiers are of type std::thread::id and can be retrieved in two ways.
	1. By calling the get_id() member function
	2. By calling std::this_thread:: get_id()

	Objects of type std::thread::id can be freely copied and compared
	If two objects of type std::thread::id are
	equal, they represent the same thread, or both are holding the “not any thread” value
	different, they represent different threads, or one represents a thread and the other is holding the “not any thread” value

	objects of type std::thread::id offer the complete set of comparison operators, 
	which provide a total ordering for all distinct values. 

	This allows them to be used as keys in associative containers, or sorted, 
	or compared in any other way that you as a programmer may see fit.

	Standard Library also provides std::hash<std::thread::id> so that values of type 
	std::thread::id can be used as keys in the new unordered associative containers too.

	You can even write out an instance of std::thread::id to an output stream such as std::cout:
	std::cout<<std::this_thread::get_id();
	The exact output you get is strictly implementation-dependent

***********/

#include <iostream>
#include <thread>
#include <string>
#include <vector>

void thread_routine() {
    std::cout << "Inside thread routine, Thread id: " << std::this_thread::get_id() << '\n';
    return ;
}

int main() {
    std::cout << "Main Thread id: " << std::this_thread::get_id() << '\n';

    std::vector<std::thread> vec_thread;
    std::thread thr(thread_routine);
    vec_thread.push_back(std::move(thr));
    vec_thread.emplace_back(thread_routine);
    vec_thread.emplace_back([](std::string msg){std::cout << "Inside Lambda: " << msg << ", Thread id: " << std::this_thread::get_id() << '\n'; }, "emplace_back lambda as thread routine");

    for(auto & thr_elem : vec_thread) {
        thr_elem.join();
    }

    return 0;
}

/*******
	END OF FILE
***********/


