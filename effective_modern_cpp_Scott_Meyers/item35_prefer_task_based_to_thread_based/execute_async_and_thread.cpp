/******
 *	This example demonstrates hoe async and thread execution takes place.
 *
 *********/

#include <iostream>
#include <future>
#include <chrono>

int fun(const int fp) {
		while(true) {
				std::cerr << "Going to sleep in fun(), thread id : " << std::this_thread::get_id() << '\n'; 
				std::this_thread::sleep_for(std::chrono::seconds(15));

		}
		return fp;
} 

int main() {

		std::thread lth(fun, 5);
		const auto f = std::async(fun, 3);
		while(true) {
				std::cerr << "Waiting inside main ..., thread id : " << std::this_thread::get_id() << '\n'; 
				std::this_thread::sleep_for(std::chrono::seconds(30));
		}
		return 0;
}

/*******
 *	END OF FILE
 * ******/
