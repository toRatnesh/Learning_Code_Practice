/*****

References
    Effective Modern C++ | Scott Meyers


Item 3: Understand decltype

Given a name or an expression, decltype tells you the name’s or the expression’s type

In C++11, perhaps the primary use for decltype is declaring function templates where the function’s return type depends on its parameter types.


C++11’s trailing return type syntax
	function’s return type will be declared following the parameter list (after the “->”)
	Advantage: the function’s parameters can be used in the specification of the return type


C++11 permits return types for single-statement lambdas to be deduced

C++14 extends this to both all lambdas and all functions, including those with multiple statements
that means that in C++14 we can omit the trailing return type, leaving just the leading auto
With that form of declaration, auto does mean that type deduction will take place.

Consider example:
template<typename Container, typename Index>	// C++14
auto accessIndex(Container& c, Index i)
{
	return c[i];	// return type deduced from c[i]
}


operator[] for most containers-of-T returns a T&, 
but Item 1 explains that during template type deduction, the reference-ness of an initializing expression is ignored

This is contrary to the return type of container which returns a reference


C++14 decltype(auto)
	auto specifies that  the type is to be deduced, and decltype says that decltype rules should be used during the deduction

    template<typename Container, typename Index>	// C++14
    decltype(auto) accessIndex(Container& c, Index i)	// return whatever c[i] returns
    {
        return c[i];			// return type deduced from c[i]
    }


decltype(auto) can also be convenient for declaring variables when 
you want to apply the decltype type deduction rules to the initializing expression

to accept both lvalues and rvalues use universal references and apply std::forward

    template<typename Container, typename Index>	
    auto accessIndex(Container && c, Index i) -> decltype(std::forward<Container>(c)[i]) // C++11
    decltype(auto) accessIndex(Container && c, Index i) // C++14
    {
        return std::forward<Container>(c)[i];			// return type deduced from c[i]
    }


Applying decltype to a name yields the declared type for that name.
For lvalue expressions more complicated than names, however, decltype ensures that the type reported is always an lvalue reference.
That is, if an lvalue expression other than a name has type T, decltype reports that type as T&.

Insignificant details in the expression whose type is being deduced can affect the type that decltype(auto) reports

Summary:
• decltype almost always yields the type of a variable or expression without any modifications.
• For lvalue expressions of type T other than names, decltype always reports a type of T&.
• C++14 supports decltype(auto), which, like auto, deduces a type from its initializer, but it performs the type deduction using the decltype rules.

**********/

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <bitset>

class Aclass {
    int             ival;
    std::string     sval;
};

int fun(const Aclass & arg) {
    return 0;
}

auto returnAutoValueAtIndex(std::vector<std::string> & svec, const size_t index) {
    return svec[index];
}

decltype(auto) returnDecltypeAutoValueAtIndex(std::vector<std::string> & svec, const size_t index) {
    return svec[index];
}


auto returnAutoValueAtIndex(std::vector<bool> & bvec, const size_t index) {
    return bvec[index];
}

decltype(auto) returnDecltypeAutoValueAtIndex(std::vector<bool> & bvec, const size_t index) {
    return bvec[index];
}

std::string get_string() {
    return "returning string value";
}

std::vector<std::string> get_svector() {
    return std::vector<std::string>{"string-1", "string-2", "string-3", "string-4"};
}

template<typename Container>
decltype(auto) useUniversalRef(Container && cont, const size_t index) {
    return std::forward<Container>(cont)[index];
}

decltype(auto) returnName() {
    int x = 5;
    return x;
}

decltype(auto) returnNameExpression() {
    int x = 5;
    return (x);
}

int main() {

    const int ival = 5;
    static_assert(std::is_same_v<decltype(ival), const int>);

    static_assert(std::is_same_v<decltype(fun), int(const Aclass &)>);

    {
        Aclass obj;
        Aclass & ref = obj;
        static_assert(std::is_same_v<decltype(ref), Aclass &>);
        static_assert(std::is_same_v<decltype(fun(ref)), int>);
    }

    {
        std::vector<std::string> svec;
        static_assert(std::is_same_v<decltype(svec), std::vector<std::string>>);

        // no issue in accessing any index here in decltype, as it will only check return type
        static_assert(std::is_same_v<decltype(svec[1]), std::string &>);
    }

    {
        std::vector<std::string>    svec{"string-1", "string-2", "string-3", "string-4"};
        static_assert(std::is_same_v<decltype(returnAutoValueAtIndex(svec, 1)), std::string>);
        static_assert(std::is_same_v<decltype(returnDecltypeAutoValueAtIndex(svec, 1)), std::string &>);
        
        std::vector<bool>    bvec{true, true, false, true, false, false};
        static_assert(std::is_same_v<decltype(returnAutoValueAtIndex(bvec, 1)), std::_Bit_reference>);
        static_assert(std::is_same_v<decltype(returnDecltypeAutoValueAtIndex(bvec, 1)), std::_Bit_reference>);

        //std::cout << typeid(decltype(returnAutoValueAtIndex(bvec, 1))).name() << '\n';
        //std::cout << typeid(decltype(returnDecltypeAutoValueAtIndex(bvec, 1))).name() << '\n';
                
    }
    {
        std::string sval = "string value";
        auto asval = sval;
        decltype(auto) dasval = sval;
        static_assert(std::is_same_v<decltype(asval), std::string>);
        static_assert(std::is_same_v<decltype(dasval), std::string>);

        const std::string csval = "const string value";
        auto acsval = csval;
        decltype(auto) dacsval = csval;
        static_assert(std::is_same_v<decltype(acsval), std::string>);
        static_assert(std::is_same_v<decltype(dacsval), const std::string>);

        std::string & rsval = sval;
        auto arsval = rsval;
        decltype(auto) darsval = rsval;
        static_assert(std::is_same_v<decltype(arsval), std::string>);
        static_assert(std::is_same_v<decltype(darsval), std::string &>);        

        const std::string & crsval = "const string ref value";
        auto acrsval = crsval;
        decltype(auto) dacrsval = crsval;
        static_assert(std::is_same_v<decltype(acrsval), std::string>);
        static_assert(std::is_same_v<decltype(dacrsval), const std::string &>);        


        {
        std::string && rrsval{get_string()};
        auto arrsval{rrsval};
        // CE error: cannot bind rvalue reference of type 'std::__cxx11::basic_string<char>&&' to lvalue of type 'std::string' {aka 'std::__cxx11::basic_string<char>'}
        //decltype(auto) darrsval{rrsval};
        static_assert(std::is_same_v<decltype(arrsval), std::string>);
        //static_assert(std::is_same_v<decltype(dacrsval), const std::string &>);             
        }

        auto arrsval{get_string()};
        decltype(auto) darrsval{get_string()};
        static_assert(std::is_same_v<decltype(darrsval), std::string>);

    }

    {
        std::vector<std::string>    svec{"string-1", "string-2", "string-3", "string-4"};
        static_assert(std::is_same_v<decltype(useUniversalRef(svec, 2)), std::string &>);
        static_assert(std::is_same_v<decltype(useUniversalRef(get_svector(), 2)), std::string &>);
    }

    {
        static_assert(std::is_same_v<decltype(returnName()), int>);
        static_assert(std::is_same_v<decltype(returnNameExpression()), int &>);
    }

    return 0; 
}

/*****
    END OF FILE
**********/
