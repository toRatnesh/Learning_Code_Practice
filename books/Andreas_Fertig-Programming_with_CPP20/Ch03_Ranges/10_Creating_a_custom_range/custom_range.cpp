/*****

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/ranges
    https://en.cppreference.com/w/cpp/ranges#Range_concepts

Chapter 3 | Ranges: The next generation STL

	Ranges are a new element of the STL that make using algorithms more concise and add the ability to write code in a functional style.

3.10 Creating a custom range

	we can create a custom view, including its corresponding range adaptor
	Let's implement our own take_view
	
	Check code below
	
3.10.1 Implementing the view

	The first step is to implement the actual view to a range.
	In this view, we need to store the range and the number of elements this view should process from the range.
	While implementing this, we apply the range concepts which are available in C++20.
	
	The concept std::ranges::view checks that R is a range that is movable, default initializable, and is a view.
	The last concept checks whether R is derived from view_base.
	Our custom_take_view derives from view_base with the help of view_interface, using Curiously Recurring Template Pattern (CRTP).
	
	Please note that this is a simplified version.
	The STL has to deal with different range types, depending on whether R is a simple_view or a sized_range.
	We leave this out here.
	
	Without deduction guide, we cannot create a custom_take_view just by passing a range and a count.

	
3.10.2 A range adaptor for custom_take_view

	We start by creating a range-adaptor closure type.
	The current implementation is a bit verbose, the closure type could be a lambda
	
	The range adaptor doesn’t store any data.
	The purpose of the adaptor is to create a custom_take_view when invoked.
	This type comes only with a call operator, which is a variadic template.
	
	custom_take_range_adaptor uses a constexpr if to switch between the oneand two-argument case.
	If only one argument is provided, this is the count. Hence a closure type object is returned.
	A call with two parameters passes a range and the count, allowing us to directly create a custom_take_view.


3.10.3 Add the pipesyntax to custom_take_view

	with operator|, the function is guarded with concepts, requiring a viewable_range. 
	The operator takes a range as the first argument and a custom_take_range_adaptor_closure type as the second. 
	Internally the closure type gets invoked with the range as the parameter. 
	This effectively returns a custom_take_view.


3.10.4 A more generalized pipesyntax implementation
	
	Instead of using this explicit type here, we can use the std::invocable concept 
	to ensure that the second template parameter is an invocable.

**********/

#include <iostream>
#include <ranges>

namespace nonstd {

template<std::ranges::view R>
class custom_take_view : 
    public std::ranges::view_interface<custom_take_view<R>> 
{
    R                                   m_base;
    std::ranges::range_difference_t<R>  m_count;

    public:

    constexpr custom_take_view()      = default;

    constexpr custom_take_view(
        R                                  base,
        std::ranges::range_difference_t<R> count
        ): m_base(std::move(base)), m_count(count) { }

    // view_interface members
    constexpr R base() const &     { return m_base; }
    constexpr R base() &&          { return std::move(m_base); }

    // Actual begin and end
    constexpr auto begin()  { return std::ranges::begin(m_base); }
    constexpr auto end()    { return std::ranges::next(std::ranges::begin(m_base), m_count); }

};

template<std::ranges::range R>  // deduction guide
custom_take_view(R && base, std::ranges::range_difference_t<R>)
    -> custom_take_view<std::ranges::views::all_t<R>>;

    namespace detail {
        template<std::integral T>
        class custom_take_range_adaptor_closure {
            T   m_count;

            public:

            constexpr custom_take_range_adaptor_closure(T count) 
                : m_count(count) { }
            
            // Allow it to be called with a range
            template<std::ranges::viewable_range R> 
            constexpr auto operator()(R&& r) const {
                return custom_take_view(std::forward<R>(r), m_count);
            }
        };

        class custom_take_range_adaptor {
            
            public:

            template<typename ...Args>
            constexpr auto operator()(Args && ...args) {
                if constexpr(sizeof...(Args) == 1) {
                    return custom_take_range_adaptor_closure(args...);
                } else {
                    return custom_take_view(std::forward<Args>(args)...);
                }
            }
        };

        /*
        template<std::ranges::viewable_range R, typename T>
        constexpr auto operator|(R && r, 
                const custom_take_range_adaptor_closure<T> & adap) 
        {
            return adap(std::forward<R>(r));
        }
        */

        // generalized pipe-syntax implementation
        template<std::ranges::viewable_range R,
                std::invocable<R>          Adaptor>
        constexpr auto operator|(R && r, const Adaptor & adap) {
            return adap(std::forward<R>(r));
        }        

    } // namespace detail

    namespace views {
        inline detail::custom_take_range_adaptor custom_take;
    }

}   // namespace nonstd

int main() {

    for (int i : std::views::iota(1) | std::views::take(5)) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    for (int i : std::views::iota(1) | nonstd::views::custom_take(5)) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

	return 0;
}

/*****
    END OF FILE
**********/

