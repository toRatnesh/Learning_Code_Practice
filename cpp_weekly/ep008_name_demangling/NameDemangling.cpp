/*****************************************
 *
 *	This example demonstrate name demangling in cpp.
 *	It also uses Application Binary Interface(ABI) to print demangled name.
 * **************************************/

#include <iostream>
#include <string>
#include <stdexcept>

#include <list>
#include <vector>

#include <typeinfo>
#include <cxxabi.h>

struct NameDemangling {

	std::vector<std::string> m_vs;
	std::list<std::vector<std::pair<std::string, std::string>>> m_lvpss;
};

std::string demangled_name(const char * mangled_name) {

	int status = 0;
	char * deman_name = nullptr;

	deman_name = abi::__cxa_demangle(mangled_name, nullptr, 0, &status);
	if(0 != status) {
		throw std::runtime_error("Name demanglined failed");
	}
	
	const std::string retval(deman_name);
	if(nullptr != deman_name) {
		free(deman_name);
		deman_name = nullptr;
	}

	return retval;

}

int main(int argc, char * argv[]) {

	const char * name = nullptr;

	name = typeid(int).name();
	std::cout << name << '\n';
	std::cout << demangled_name(name) << '\n' << '\n'; 

	name = typeid(std::string).name();
	std::cout << name << '\n';
	std::cout << demangled_name(name) << '\n' << '\n'; 

	name = typeid(NameDemangling).name();
	std::cout << name << '\n';
	std::cout << demangled_name(name) << '\n' << '\n'; 

	name = typeid(&NameDemangling::m_vs).name();
	std::cout << name << '\n';
	std::cout << demangled_name(name) << '\n' << '\n'; 

	name = typeid(&NameDemangling::m_lvpss).name();
	std::cout << name << '\n';
	std::cout << demangled_name(name) << '\n' << '\n'; 

	return 0;
}

