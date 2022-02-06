/***************
 *	This exmaple demonstrates about c++20 jthread and stop_token.
 *
 *	std::jthread
 *	The class jthread represents a single thread of execution. It has the same general behavior as std::thread, except that jthread automatically rejoins on destruction, and can be cancelled/stopped in certain situations.
 *
 *	std::stop_token
 *	The stop_token class provides the means to check if a stop request has been made or can be made, for its associated std::stop_source object. It is essentially a thread-safe "view" of the associated stop-state.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/thread/jthread
 *	https://en.cppreference.com/w/cpp/thread/stop_token
 *
 * *****************/

#include <iostream>
#include <vector>

#include <thread>
#include <stop_token>

void routine(std::stop_token stp_token, int num) {
	while(!stp_token.stop_requested()) {
		printf("routine: %d - waiting for stop token\n", num);
	}
	using namespace std::literals::chrono_literals;
	std::this_thread::sleep_for(3s);
}

int main() {          
	std::vector<std::jthread> l_threads;

	for(uint8_t i = 0; i < 5; ++i) {
		l_threads.push_back(std::jthread(routine, i));
	}

	using namespace std::literals::chrono_literals;
	std::this_thread::sleep_for(10s);

	return 0;
}

/*******
 *	END OF FILE
 * **********/
