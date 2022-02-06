/**************
 *	This exmaple demonstrates what is a lambda.
 *	Lamda are classes with overload operator() for them and their may be function pointer version also.
 *	For equivalent code of a lambda compile and check the code on.
 *	https://cppinsights.io/
 *
 * ************/


int main() {

	// simplest lambda
	[[maybe_unused]] const auto l1 = [](){};

	// lambda - no params and capture list, we can skip () in this case
	[[maybe_unused]] const auto l2 = []{ return true; };

	// lambda - with params 
	[[maybe_unused]] const auto l3 = [](const auto param){ return param; };

	// lambda - with params and capture 
	int val = 7;
	[[maybe_unused]] const auto l4 = [val](const auto param) { return val + param;};

	// lambda - mutable lambda
	//const auto l5 = [val](const auto param){ if(param) return ++val; else val;}; // error: increment of read-only variable 'val'
	[[maybe_unused]]  auto l5 = [val](const auto param) mutable { return ++val + param; }; // l5 cannot be const


	return 0;
}


/***********
 *	END OF FILE
 * ********/
