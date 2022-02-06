/********************
 *	Argument-dependent lookup (ADL):
 *	Argument-dependent lookup, also known as ADL, or Koenig lookup, is the set of rules for looking up the unqualified function names in function-call expressions, including implicit function calls to overloaded operators. These function names are looked up in the namespaces of their arguments in addition to the scopes and namespaces considered by the usual unqualified name lookup.
 *
 *	Argument-dependent lookup makes it possible to use operators defined in a different namespace.
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/language/adl
 *
 * ************/

#include <iostream>

namespace ns {
	struct St { };
	int show(const St &) { std::puts("ns::show"); return 0; }
}

namespace ns1 {
	struct St { };
	int show(const St &) { std::puts("ns1::show"); return 0; }
}

namespace ns2 {
	struct St { };
	int show(const St &) { std::puts("ns2::show"); return 0; }
	int show_diff(const ns1::St &) { std::puts("ns2::show_diff"); return 0; }
}

int main() {
	ns::St ns_st;
	show(ns_st);    // ADL

	ns1::St ns1_st;
	show(ns1_st);   // ADL

	ns2::St ns2_st;
	show(ns2_st);   // ADL
	//show_diff(ns2_st);   // CE error: invalid initialization of reference of type 'const ns1::St&' from expression of type 'ns2::St'

	return 0;
}

/*********
 *	END OF FILE
 * ************/
