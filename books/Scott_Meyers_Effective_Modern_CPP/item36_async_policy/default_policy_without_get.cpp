/*

   $ ./default_policy
   Inside thr_routine(), thread id : 139847484479232
   Inside main(), thread id        : 139847501338432

NOTE:
fun does not execute (since f.get() is not called fun may or may not execute it may deferred)

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
		//f.get();
		std::clog << "Inside thr_routine(), thread id : " << std::this_thread::get_id() << '\n';
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
