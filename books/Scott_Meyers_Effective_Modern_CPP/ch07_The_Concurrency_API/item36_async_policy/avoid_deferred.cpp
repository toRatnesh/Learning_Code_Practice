/**
 
 
 
 
 * **/



#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int fun() {
		std::clog << "Inside fun(), thread id 	: " << std::this_thread::get_id() << '\n'; 

		return 5;
}

int thr_routine() {
		auto f = std::async(fun);

		// WORKAROUND TO AVOID DEFERRED TASK
		if(std::future_status::deferred == f.wait_for(std::chrono::seconds(0))) {
			std::clog << "Task is deferred\n Calling get() on future object to call fun()";
			f.get();
		}
		else {
				std::clog << "Task is not deferred\n";
				while(std::future_status::ready != f.wait_for(std::chrono::seconds(1))) {
						std::clog << "Waiting for status to be ready \n";
						std::this_thread::sleep_for(std::chrono::seconds(5));
						break;
				}
		}

		std::clog << "Inside thr_routine(), thread id : " << std::this_thread::get_id() << '\n'; 

		return 1;
}

int main() {
		std::thread lth(thr_routine);
		lth.join();
		std::clog << "Inside main(), thread id 	: " << std::this_thread::get_id() << '\n'; 
		return 0;
}


