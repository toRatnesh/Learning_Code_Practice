/*********
 *	This example demonstrates the use of following c++20 lambda features for resource management.
 *	Lambdas in unevaluated contexts
 *	Default constructible and assignable stateless lambdas
 *
 * *********/

#include <iostream>
#include <memory>

int main() {

	auto file_deleter = [](FILE * fp){ fclose(fp); };
	auto fp = std::unique_ptr<FILE, decltype(file_deleter)>(
			fopen("somefile.txt", "w"), 
			file_deleter
			);

	auto fp_in_cpp20 = std::unique_ptr<FILE, decltype([](FILE * fp){ fclose(fp); })>( // lambda in UC 
			fopen("somefile.txt", "w")
			// default constructible lambda
			);

	return 0;
}

/********
 *	END OF FILE
 * *******/
