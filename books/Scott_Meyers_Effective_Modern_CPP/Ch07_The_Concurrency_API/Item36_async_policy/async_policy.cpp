/*****

 $ ./async_policy
 Inside thr_routine(), thread id : 140055162935040
 Inside fun(), thread id         : 140055154542336
 Inside main(), thread id        : 140055179794240

NOTE:
Using async launch policy fun() is executed asynchronously 
 
 ******/


#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int fun() {
		std::clog << "Inside fun(), thread id 	: " << std::this_thread::get_id() << '\n'; 

		return 5;
}

int thr_routine() {
		auto f = std::async(std::launch::async, fun);
		std::clog << "Inside thr_routine(), thread id : " << std::this_thread::get_id() << '\n'; 

		return 1;
}

int main() {
		std::thread lth(thr_routine);
		lth.join();
		std::clog << "Inside main(), thread id 	: " << std::this_thread::get_id() << '\n'; 
		return 0;
}

/*****
 *	END OF FILE
 * ****/
