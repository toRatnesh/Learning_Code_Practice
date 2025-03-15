/*****

References

	episode https://www.youtube.com/watch?v=AIKAOWs213o
	https://en.cppreference.com/w/cpp/language/structured_binding
	
	Binds the specified names to subobjects or elements of the initializer.
	
	Like a reference, a structured binding is an alias to an existing object.
	Unlike a reference, a structured binding does not have to be of a reference type.

**********/

#include <iostream>
#include <string>

struct Employee {
    std::string name;
    std::string address;
    float       salary;
};

int main() {

    Employee aemployee{"Emp-1", "Addr-1", 235.6f};
    auto [name, addr, salary] = aemployee;	// name addr, salary are refernces to an object internally created by compiler (not guaranteed)

	std::cout << "Name " << name << ", Address " << addr << ", Salary " << salary << '\n';
	std::cout << "Name " << aemployee.name << ", Address " << aemployee.address << ", Salary " << aemployee.salary << '\n';
	
	name = "Emp-2";
	std::cout << '\n';
	std::cout << "Name " << name << ", Address " << addr << ", Salary " << salary << '\n';
	std::cout << "Name " << aemployee.name << ", Address " << aemployee.address << ", Salary " << aemployee.salary << '\n';

    return 0;
}

/*****
    END OF FILE
**********/


