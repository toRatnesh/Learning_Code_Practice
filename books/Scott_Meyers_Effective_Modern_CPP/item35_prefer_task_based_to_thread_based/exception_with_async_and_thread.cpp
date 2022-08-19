/**************
 *
 * 	This example demonstrates the handling of exception in async and thread.
 *
 * ************/

#include <iostream>
#include <future>
#include <chrono>

int fun(const int fp) {

		if(0 == (fp % 2)) {
				std::cerr << "Number is even\n";
		}
		else {
				throw std::runtime_error("Exception : Number is odd");
		}

		return fp;
}

int main() {
		try {
				auto fo = std::async(fun, 3);
				auto fe = std::async(fun, 4);
				std::thread lth(fun , 3);	// exception from thread will not be caught

				//auto val = fe.get();
				//std::cerr << "return value of fe.get() : " << val << '\n';
				
				auto val2 = fo.get();
				std::cerr << "return value of fo.get() : " << val2 << '\n';

				//lth.join();	
		}
		catch (const std::exception & exp) {
				std::cerr << "Exception caugth, " << exp.what() << '\n';
		} 
		catch(...) {
				std::cerr << "Unknown exception";

		} 

		while(true) {
				std::this_thread::sleep_for(std::chrono::seconds(15));
		}

		return 0;
}


/**********
 *	END OF FILE
 * ********/
