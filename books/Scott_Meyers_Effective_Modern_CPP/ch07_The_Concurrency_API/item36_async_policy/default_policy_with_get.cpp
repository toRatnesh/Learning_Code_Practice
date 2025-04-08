/*
   $ ./default_policy
   Inside fun(), thread id         : 140555521271552	
   Inside thr_routine(), thread id : 140555521271552
   Inside main(), thread id        : 140555538130752


NOTE: 
fun() has same thread id as thread routine 
fun() may run in a same or different thread

*/

#include <iostream>
#include <future>
#include <thread>

int fun() {
		std::clog << "Inside fun(), thread id   : " << std::this_thread::get_id() << '\n';
		return 5;
}

int thr_routine() {
		auto f = std::async(fun);
		f.get();
		std::clog << "Inside thr_routine(), thread id   : " << std::this_thread::get_id() << '\n';
		return 1;
}
int main() {
		std::thread lth(thr_routine);
		lth.join();
		std::clog << "Inside main(), thread id  : " << std::this_thread::get_id() << '\n';
		return 0;
}

/***
 *	END OF FILE
 * ***/
