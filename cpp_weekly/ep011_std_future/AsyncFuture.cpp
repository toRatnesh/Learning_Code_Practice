/***********************************************
 *
 *	This example shows the uses of std::async and how the policy
 *	std::launch::async and
 *	std::launch::deferred
 *
 *	affects the asynchronous execution.
 *
 * **********************************************/


#include <iostream>
#include <random>
#include <set>
#include <algorithm>
#include <future>

std::set<int> make_sorted_random(const size_t num_elems) {

	std::set<int> retval;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, num_elems - 1);
	std:: generate_n(std::inserter(retval, retval.end()), num_elems, [&](){ return dis(gen); });

	return retval;
}


int main() {

	/* CASE - 01 | Two function call */
	//std::cout << make_sorted_random(1000000).size() << ' ' << make_sorted_random(1000000).size() << '\n';

	/* CASE - 02 | Two async call using default policy */
	/* This will not execute in async way because of default policy */
	//std::cout << std::async(make_sorted_random, 1000000).get().size() << ' ' << std::async(make_sorted_random, 1000000).get().size() << '\n';

	/* CASE - 03 | Two async call using async policy */	
	/* This will not execute in async way because first call will ito get() will be blocked and will cause secondi call of get() to execute in synchronous way */
	//std::cout << std::async(std::launch::async, make_sorted_random, 1000000).get().size() << ' ' << std::async(std::launch::async, make_sorted_random, 1000000).get().size() << '\n';

	/* CASE - 04 | Two async call using async policy */
	/* DO THE BEST THAT YOU THINK | it may or may not execute in async way */
	//auto f1 = std::async(make_sorted_random, 1000000);
	//auto f2 = std::async(make_sorted_random, 1000000);
	//std::cout << f1.get().size() << ' ' << f2.get().size() << '\n';
	
	/* CASE - 05 | Two async call using async policy */
	/* execute in asynchronous way  */
	auto f3 = std::async(std::launch::async, make_sorted_random, 1000000);
	auto f4 = std::async(std::launch::async, make_sorted_random, 1000000);
	std::cout << f3.get().size() << ' ' << f4.get().size() << '\n';

	return 0;
}


/****************
 *	EOF
 * *************/



