##############################
#	This is information to how to check and make sure that the library we are using in our code is error free/ with minimal possible 
##############################


1.	Know what your libraries does
	Are the types/functions constexpr enabled?
	What implicit conversions exist?
	Will the function / constructor implicitly allocate?
	Will allocate
		.	Vector
		.	Deque
		.	Required to allocate for each node
			o	List
			o	Map 
			o	Set
	Might allocate (have small object optimizations)
		.	String
		.	Function 
		.	Any

	Never allocate
		.	Pair
		.	Tuple
		.	Variant
		.	Array (It also has no constructors!!)

		Algorithms that might allocate
		.	Stable
		If algorithm is constexpr enabled (as of C++20) it will never allocate!


	2.	Know they are very well tested and are all open source
	GCC's (libstdc++)
	Clang's (libc++)
	MSVC's

	3.	Read the source code
	Understand how and why things are implemented when you need to


#################
#   END OF FILE
#################
