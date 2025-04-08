/*****

$ ./deferred_policy
Inside fun(), thread id         : 140254119454528
Inside main(), thread id        : 140254119454528

NOTE:
For deferred launch policy execution is deferred until get() or wait() is called.
 
 ******/


#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int fun() {
		std::clog << "Inside fun(), thread id 	: " << std::this_thread::get_id() << '\n'; 

		return 5;
}


int main() {
		auto f1 = std::async(std::launch::deferred, fun);
		// f1 will be deferred till get or wait is called for it


		auto f2 = std::async(std::launch::deferred, fun);
		f2.get();	// calling get() will execute fun()

		std::clog << "Inside main(), thread id 	: " << std::this_thread::get_id() << '\n'; 
		
		return 0;
}

/*****
 *	END OF FILE
 * ****/
