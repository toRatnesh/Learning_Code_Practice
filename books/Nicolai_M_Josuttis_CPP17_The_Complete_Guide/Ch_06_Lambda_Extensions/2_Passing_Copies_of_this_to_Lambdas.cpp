/************

  References
  C++17 - The Complete Guide | Nicolai M. Josuttis

  Lambda
  C++11   Lambda
  C++14   Generic lambdas
  C++17   In constant expression
  In places where you need a copy of the current object

  2. Passing Copies of this to Lambdas
	For lambda inside member function lambda has no implicit access to the object
  In C++11 and C++14
	  You have to pass this either by value or by reference
	  Even copying this captures the underlying object by reference (as only the pointer was copied)
	  This may result into error if lifetime of lambda exceeds lifetime of object upon which member function is invoked
  In C++14
	  We may name caputure *this [copyOfThis=*this] in lambda thus getting a copy of the object and leading to safety
	  It still may lead to error if we capture this, = or & along with name capture *this [copyOfThis=*this]
  In C++17
	Explicitly capture copy of current object using *this

 *************/

#include <iostream>
#include <string>

#include <thread>
#include <chrono>

class St {
	std::string name;
	void display_1() const { std::clog << name << " | "; }
	void display_2() const { std::clog << name << '\n'; }
	public:
	St(std::string name) : name(name) { }
	void display_cpp11_14() {
		// C++11/C++14 
		auto l1 = [this](){ display_1(); name="captured this"; display_2(); };
		auto l2 = [=](){ display_1(); name="captured ="; display_2(); };
		auto l3 = [&](){ display_1(); name="captured &"; display_2(); };
		l1();
		l2();
		l3();
	}

	void display_cpp14() {
		// C++14 
		auto l = [copyOfThis=*this](){ 
			copyOfThis.display_1();
			//copyOfThis.name=std::string("captured this"); // CE error: no match for 'operator=' (operand types are 'const std::string' and 'std::string' )
			copyOfThis.display_2(); 
		};
		l();
	}

	void display_cpp17() {
		// C++17
		auto l = [*this](){
			display_1();
			//name = std::string("capture *this"); // CE error: no match for 'operator=' (operand types are 'const std::string' and 'std::string' )
			display_2(); 
		};
		l();
	}

	auto unsafeThreadUsingThis() const {
		auto l = [this](){ 
			std::this_thread::sleep_for(std::chrono::seconds(3));
			std::clog << name << '\n'; 
		};
		std::thread t(l);
		return t;
	}

	auto safeThreadUsingThis() const {
		auto l = [*this](){ 
			std::this_thread::sleep_for(std::chrono::seconds(3));
			std::clog << name << '\n'; 
		};
		std::thread t(l);
		return t;
	}
};

int main() {
	// 2. Passing Copies of this to Lambdas
	St st1("Lambda capture this in C++11/C++14");
	st1.display_cpp11_14();

	St st2("Lambda capture this in C++14");
	st2.display_cpp14();

	St st3("Lambda capture this in C++17");
	st3.display_cpp17();

	std::thread t1;
	{
		St st("thread using *this in lambda");
		t1 = st.safeThreadUsingThis();
	}
	t1.join();

	std::thread t2;
	{
		St st("thread using this in lambda");
		t2 = st.unsafeThreadUsingThis();
	}
	t2.join();

	return 0;
}

/************
  END OF FILE
 ***********/

