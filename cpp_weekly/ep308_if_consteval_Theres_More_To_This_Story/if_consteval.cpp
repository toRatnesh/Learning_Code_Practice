/******************

	This example demonstrates about use of consteval and how it's better to use over std::is_constant_evaluated() 

**************/


#include <cassert>
#include <type_traits>

// immediate function evaluated at compile time
consteval int get_value(int i) {
	return 42 + i;    
}

// immediate function evaluated at compile or run time
constexpr int fun(int i) {

	//if (std::is_constant_evaluated())  #although it's a compile time known constant we'r checking it at run time
	if consteval    # actual compile time construct
	{
		return get_value(i);
	}
	else {
		return 24;    
	}

}

int main() {    
	static_assert(43 == fun(1));
	assert(24 == fun(1)); 
	return 0;    
}
/**********
	END OF FILE
********/
