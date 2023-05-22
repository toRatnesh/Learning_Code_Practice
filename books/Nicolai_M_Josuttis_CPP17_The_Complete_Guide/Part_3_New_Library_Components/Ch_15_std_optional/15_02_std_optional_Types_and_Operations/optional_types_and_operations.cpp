/*********

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/utility/optional

Chapter 15 std::optional<>

    we could have a value of a certain type or we might not have any value at all
    to define an object of a certain type with an additional Boolean member/flag signaling whether a value exists
    std::optional<> provides such objects in a type-safe way

    size usually is one byte larger than the contained object

    as with std::variant<> and std::any the resulting objects have value semantics
    that is, copying is implemented as a deep copy
    Move semantics are supported.

15.2 std::optional<> Types and Operations

15.2.1 std::optional<> Types
    namespace std {
        template<typename T> class optional;
    }

    nullopt of type std::nullopt_t as a “value” for optional objects having no value
    std::bad_optional_access -> std::exception, for value access without having a value
    optional objects also use the object std::in_place (of type std::in_place_t) to initialize the value of an optional object with multiple arguments

15.2.2 std::optional<> Operations

    -------------------------------------------------
    Operation			Effect
    -------------------------------------------------
    constructors		Create an optional object (might call constructor for contained type)
    make_optional<>()	Create an optional object (passing value(s) to initialize it)
    destructor			Destroys an optional object
    =					Assign a new value
    emplace()			Assign a new value to the contained type
    reset()				Destroys any value (makes the object empty)
    has_value()			Returns whether the object has a value
    conversion to bool	Returns whether the object has a value
    *					Value access (undefined behavior if no value)
    ->					Access to member of the value (undefined behavior if no value)
    value()				Value access (exception if no value)
    value_or()			Value access (fallback argument if no value)
    swap()				Swaps values between two objects
    ==,!=,<,<=,>,>=		Compare optional objects
    hash<>				Function object type to compute hash values
    -------------------------------------------------

Construction
	
	you can pass a value to initialize the contained type
	type can be deduced using deduction guide
	
	initialize an optional object with multiple arguments, you have to create the object 
	or add std::in_place as first argument (the contained type can’t be deduced) this avoids the creation of a temporary object
	
	You can copy optional objects
	
	make_optional<>(), which allows an initialization with single or multiple arguments (without the need for the in_place argument)
	as usual for make... functions it decays
	
Accessing the Value
	To check, whether an optional object has a value you can use it in a Boolean expression or call has_value()
	To access the value, operator* can directly access its value, using this without having a value is undefined behavior
	or value(), which throws a std::bad_optional_access exception, if there is no contained value

	value_or() ask for the value and pass a fallback value, which is used, if the optional object has no value
	fallback argument is passed as rvalue reference
	
	both operator* and value() return the contained object by reference
	be careful, when calling these operation directly for temporary return values
	
	std::optional<std::string> getString();
	...
	auto a = getString().value(); // OK: copy of contained object
	
	auto b = *getString();					// ERROR: undefined behavior if std::nullopt
	const auto& r1 = getString().value();	// ERROR: reference to deleted contained object
	auto&& r2 = getString().value();		// ERROR: reference to deleted contained object
	
Comparisons
	operands can be an optional object, an object of the contained type, and std::nullopt
	If both operands are objects with a value, the corresponding operator of the contained type is used.
	If both operands are objects without a value they are considered to be equal
	the operand without a value is considered to be less than the operand with a value
	
	** implicit type conversions for the underlying type are supported

Changing the Value
	using Assignment and emplace() operations
	
	Assigning std::nullopt (or {}) or calling calling reset() removes the value, which calls the destructor of the contained type if there was a value before
	
	because operator* yields the value by reference it can be used modify the value
	this requires that there is a value to modify
	
	std::optional<int> empty;
	*empty = 42;		// undefined behavior
	
Move Semantics
	if you move the object as a whole, the state gets copied and the contained object (if any) is moved

Hashing
	hash value of the contained non-constant type (if any)

************/

#include <iostream>
#include <optional>
#include <string>
#include <complex>
#include <set>

std::optional<std::string> getOptionalString(bool send_str) {
    std::optional<std::string> res{std::nullopt};
    if(send_str) {
        res = "sample string";
    }
    return res;
}

int main() {
    std::cout << "=== construction ===\n";
    {
    std::optional<std::string> empty_op_str;
    std::optional<std::string> op_str{"sample string"};
    std::cout << "*op_str : " << *op_str << '\n';
    }

    std::cout << "\n=== construction using deduction guide ===\n";
    {
    std::optional   op_int{43};    // deduced type is int
    std::optional   op_ccp{"const char *"};
    using namespace std::string_literals;
    std::optional   op_str{"sample string"s}; 
    
    std::cout << "*op_int " << *op_int << '\n';
    std::cout << "*op_ccp " << *op_ccp << '\n';
    std::cout << "*op_str " << *op_str << '\n';
    }

    std::cout << "\n=== optional object with multiple arguments ===\n";
    {
    std::optional   op_com{std::complex{3, 4}};
    std::cout << "op_com->real(): " << op_com->real() << ", op_com->imag(): " << op_com->imag() << '\n';
    std::optional<std::complex<int>>   op_com2{std::in_place, 3, 4};
    std::cout << "op_com2->real(): " << op_com2->real() << ", op_com2->imag(): " << op_com2->imag() << '\n';

    auto compFun = [](int val1, int val2){ return val1 < val2;};
    std::optional<std::set<int, decltype(compFun)>>   op_set{std::in_place, {-2, -1, 0, 1, 2}, compFun};
    std::cout << "set elements are: \n";
    for(const auto elem : *op_set) {
        std::cout << elem << ',';
    }
    std::cout << '\n';
    }

    std::cout << "\n=== optional using make_optional<> ===\n";
    {
    auto op_dbl = std::make_optional(34.25);
    std::cout << "*op_dbl: " << *op_dbl << '\n';
    auto op_int = std::make_optional<int>(34.25);
    std::cout << "*op_int: " << *op_int << '\n';
    auto op_com = std::make_optional<std::complex<double>>(2.3, 3.8);
    std::cout << "op_com->real(): " << op_com->real() << ", op_com->imag(): " << op_com->imag() << '\n';
    }

    std::cout << "\n=== Accessing the Value ===\n";
    {
    std::optional<std::string>  op_str{"sample string"};
    if(op_str) 
        std::cout << "*op_str: " << *op_str << '\n';
    if(op_str.has_value()) 
        std::cout << "op_str.value(): " << op_str.value() << '\n';
    std::cout << "op_str.value_or(\"NONE VALUE\"): " << op_str.value_or("NONE VALUE") << '\n';
    
    std::optional<std::string>   op_empty_str;
    std::cout << "accessing wihtout having a value is undefined behavior, *op_empty_str : " << *op_empty_str << '\n'; // this is UB 
    std::cout << "op_empty_str.value_or(\"NONE VALUE\"): " << op_empty_str.value_or("NONE VALUE") << '\n';

        {
            auto copyval = getOptionalString(true).value();
            std::cout << "copied value: " << copyval << '\n';
        }
        {
            [[maybe_unused]] const auto & constref = getOptionalString(true).value();
            //std::cout << "const reference value: " << constref << '\n'; // dangling reference to a temporary
        }
        {
            [[maybe_unused]] auto && rvalueref = getOptionalString(true).value();
            //std::cout << "rvalueref reference value: " << rvalueref << '\n'; // dangling reference to a temporary
        }
        {
            auto val = *getOptionalString(true);
            std::cout << "val " << val << '\n';     // undefined behavior for nullopt
        } 
        {
            auto val = *getOptionalString(false);
            std::cout << "val " << val << '\n';     // undefined behavior for nullopt
        }
    }

    std::cout << "\n=== std::optional comparisons ===\n";
    {
        std::optional<std::string> emp_op_1;
        std::optional<std::string> emp_op_2;
        if(emp_op_1 == emp_op_2) {
            std::cout << "Empty optional objects are equal\n";
        }
        std::optional<int>    empop_ival;
        std::optional<int>    op_ival_1{-2};
        std::optional<int>    op_ival_2{4};
        std::optional<int>    op_ival_3{4};
        std::cout << "*op_ival_1: " << *op_ival_1 << '\n';
        std::cout << "*op_ival_2: " << *op_ival_2 << '\n';
        std::cout << "*op_ival_3: " << *op_ival_3 << '\n';
        
        if(op_ival_1 < op_ival_2) {
            std::cout << *op_ival_1 << " is less than " << *op_ival_2 << '\n';
        }
        if(empop_ival < op_ival_1) {
            std::cout << "optional without value is less than that with a value " << *op_ival_1 << '\n';
        }
        if(op_ival_2 == op_ival_3) {
            std::cout << *op_ival_2 << " is equal to " << *op_ival_3 << '\n';
        }
        int val = 5;
        if(op_ival_2 < val) {
            std::cout << *op_ival_2 << " is less than " << val << '\n';
        }
        val = 4;
        if(op_ival_2 == val) {
            std::cout << *op_ival_2 << " is equal to " << val << '\n';
        }
        double dval = 4.0;
        if(op_ival_2 == dval) {
            std::cout << *op_ival_2 << " is equal to " << dval << '\n';
        }
        else {
            std::cout << *op_ival_2 << " is not equal to " << dval << '\n';
        }

        std::optional op_dval{4.0};
        if(op_ival_2 == dval) {
            std::cout << *op_ival_2 << " is equal to " << dval << '\n';
        }

        if(empop_ival < 0) {
            std::cout << "std::optional<int> without value is less than " << 0  << '\n';
        }

        std::optional<bool> empty_bval;
        if(empty_bval < false) {
            std::cout << "std::optional<bool> without value is less than false\n";
        } 
    }

    std::cout << "\n=== Changing the Value ===\n";
    {
    std::optional<std::string> op_sval{"sample string"};
    std::cout << "optional string value, *op_sval: " << *op_sval << '\n';

    op_sval = "updated using assignment";
    std::cout << "optional string value, *op_sval: " << *op_sval << '\n';

    *op_sval = "updated using reference";
    std::cout << "optional string value, *op_sval: " << *op_sval << '\n';

    op_sval.emplace("updated using emplace");
    std::cout << "optional string value, *op_sval: " << *op_sval << '\n';

    op_sval = "will remove this using reset()";
    std::cout << "optional string value, *op_sval: " << *op_sval << '\n';
    op_sval.reset();
    //std::cout << "optional string value, *op_sval: " << *op_sval << '\n'; RUN_TIME ERROR
    op_sval = "will remove by assigning {}";
    std::cout << "optional string value, *op_sval: " << *op_sval << '\n';
    op_sval = {};
    //std::cout << "optional string value, *op_sval: " << *op_sval << '\n'; RUN-TIME ERROR
    op_sval = "will remove by assigning std::nullopt";
    std::cout << "optional string value, *op_sval: " << *op_sval << '\n';
    op_sval = std::nullopt;
    //std::cout << "optional string value, *op_sval: " << *op_sval << '\n'; RUN-TIME ERROR

    std::optional<std::string> empty_op_sval;
    // *empty_op_sval = "this is undefined behavior";
    }

    std::cout << "\n=== std::optional move ===\n";
    {
    std::optional<std::string> op_sval;
    std::string str{"this will be moved"};
    op_sval = std::move(str);   // accessing str after this is unspecified
    std::cout << "optinal string value, *op_sval: " << *op_sval << '\n';

    std::string str_copy = *op_sval;     // OK, copy the value
    std::cout << "copied string value from optional, str_copy: " << str_copy << '\n';

    std::string str_move = std::move(*op_sval); // accessing op_sval value after this is unspecified
    std::cout << "moved string value from optional, str_move: " << str_move << '\n';
    std::cout << "optinal string value, *op_sval: " << *op_sval << '\n';
    }

    std::cout << "\n=== std::optional hashing ===\n";
    {
    std::optional<std::string> op_sval{"sample string"};
    std::cout << "Hash value for std::hash<std::optional<std::string>>{}(op_sval): " << std::hash<std::optional<std::string>>{}(op_sval) << '\n';        
    }

    return 0;
}

/*********
    END OF FILE
************/


