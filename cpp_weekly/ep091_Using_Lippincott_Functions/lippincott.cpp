/***********
 *	This example demonstrates the use of lippincott function for centtralized exception handling.
 *
 *	If you got multiple functions that need same kind of exception handling then you can use lippincott function
 *	for centerlized exception handling from all those functions. 
 *	Lippincott function will eliminate code bloat that will result if we handle all those exceptions in all those functons. 
 *
 * ***********/


#include <iostream>
#include <type_traits>

void do_something1 () { }
void do_something2 () { }

void lippincott() {
	try {
		throw;  // rethrow the exception
	} catch(const std::runtime_error & exp) {
		std::clog << "runtime error: " << exp.what() << '\n';
	} catch(const std::exception & exp) {
		std::clog << "exception: " << exp.what() << '\n';
	}
	catch(...) {
		std::clog << "unknown" << '\n';
	}

	return;
}

void func1() {
	try {
		do_something1();
		throw std::runtime_error("test exception - 1");
	} catch (...) {
		lippincott();
	}

	/*  BEFORE lippincott
	    try {
	    do_something1();
	    } catch(const std::runtime_error & exp) {
	    std::clog << "runtime error: " << exp.what() << '\n';
	    } catch(const std::exception & exp) {
	    std::clog << "exception: " << exp.what() << '\n';
	    }
	    catch(...) {
	    std::clog << "unknown" << '\n';
	    }
	    */
}

void func2() {
	try {
		do_something2();
		throw std::runtime_error("test exception - 2");
	} catch (...) {
		lippincott();
	}

	/*  BEFORE lippincott
	    try {
	    do_something1();
	    } catch(const std::runtime_error & exp) {
	    std::clog << "runtime error: " << exp.what() << '\n';
	    } catch(const std::exception & exp) {
	    std::clog << "exception: " << exp.what() << '\n';
	    }
	    catch(...) {
	    std::clog << "unknown" << '\n';
	    }
	    */
}


// FOR TEMPLATE CODE
template<typename T>
extern void do_something3(T t) { 
	std::cout << t << '\n'; 
	throw std::runtime_error("test exception - 3");
}

template<typename T>
struct S {
	static void func() {
		try {
			do_something3(T{});
		} catch (...) {
			lippincott();
		}
	}
};

int main() {
	func1();
	func2();

	S<std::integral_constant<int, 7>> s1;
	s1.func();

	S<int> s2;
	s2.func();

	return 0;
}

/**********
 *	END OF FILE
 * ********/
