In this tutorial Jason talks about a few features of cpp-17.

## multiline (since C++17)
Specifies that ^ shall match the beginning of a line and $ shall match the end of a line, if the ECMAScript engine is selected.
For more info check: https://en.cppreference.com/w/cpp/regex/basic_regex/constants


## array support for shared_ptr 	(since C++17) 
operator[] provides indexed access to the stored array
For more info check: https://en.cppreference.com/w/cpp/memory/shared_ptr


## reinterpret_pointer_cast	(since C++17) 
template< class T, class U >
std::shared_ptr<T> reinterpret_pointer_cast( const std::shared_ptr<U>& r ) noexcept; (since C++17)
template< class T, class U >
std::shared_ptr<T> reinterpret_pointer_cast( std::shared_ptr<U>&& r ) noexcept; (since C++20)
For more info check: https://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast


## std::as_const	(since C++17) 
template <class T>
constexpr std::add_const_t<T>& as_const(T& t) noexcept;	(1) (since C++17)
template <class T>
void as_const(const T&&) = delete;		(2) (since C++17)
1) Forms lvalue reference to const type of t
2) const rvalue reference overload is deleted to disallow rvalue arguments
For more info check: https://en.cppreference.com/w/cpp/utility/as_const


## std::to_chars	(since C++17)
Converts value into a character string by successively filling the range [first, last), where [first, last) is required to be a valid range.
For more info check: https://en.cppreference.com/w/cpp/utility/to_chars

For more info visit tutorial video:
https://www.youtube.com/watch?v=TXin7Nz9Knw&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=74
