/*********
 *
 *	This tutorial demonstrates the cost of using lambda.
 *	Check assembly code of follwing exmaple in various condition to check the cost of using lambda.
 *
 * *************/

struct Lambda {
	auto operator() (void) const {
		return 5;
	}
};

int main() {
	// returning using lambda
	//return []{return 5;}();

	// returnin by overloading operator () 
	// this is equivalent to returning using lambda 
	return Lambda()();

	// returning int value 
	//return 5;
}

/****
 *	END OF FILE
 * ****/
