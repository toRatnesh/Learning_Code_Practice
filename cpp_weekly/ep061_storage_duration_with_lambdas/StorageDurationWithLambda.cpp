/************
 *
 *	This example demonstrates the lambda variable scope and their pro and cons.
 *
 * *********/

#include <iostream>
#include <thread>
#include <future>

int main() {
	// simple mutable lambda
	//auto l = [val = 0]() mutable { return ++val; };

	// make local static variable to overcome mutable
	// but this leads to race condition issue 
	/*
	   const auto l = []() { 
	   static auto val = 0;
	   return ++val; 
	   };
	   */

	// to overcome race condition 
	// change static varible to thread_local
	const auto l = []() { 
		thread_local auto val = 0;
		return ++val; 
	};

	auto l2 = l;

	auto f = std::async(std::launch::async, l);
	f.get();

	l2();
	l2();
	l2();
	l2();
	l2();

	l();
	l();
	l();
	l();
	const auto ret = l();
	std::cout  << ret << '\n';

	return 0;
}

/********
 *	END OF FILE
 * ********/
