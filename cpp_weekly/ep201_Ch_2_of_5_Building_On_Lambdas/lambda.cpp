/*************
  This example demonstrates about implementation of lamda using classes and its
  application

  Also check previous episodes on lambda:
  ep152_Lambdas_The_Key_To_Understanding_CPP
  ep133_What_Exactly_IS_A_Lambda_Anyhow
  ep037_stateful_lambdas
  ep051_Advanced_Stateful_Lambdas
  ep040_Inheriting_From_Lambdas
  ep097_Lambda_To_Function_Pointer_Conversion

  Episodes on concepts related to this example:

  ep150_cpp20_Lambdas_For_Resource_Management
  ep184_Higher_Order_Functions
  ep048_cpp17_variadic_using
  ep049_cpp17_Why_Inherit_From_Lambdas
  ep025_cpp17_Aggregate_Initializations
  ep134_Inherit_From_Lambdas-Improvement_of_Visitor


Assignment:

1. Can you implement this higher order function in C++98?

auto add = [](const auto & lhs, const auto & rhs) { return lhs+rhs;};
auto lazy = [](const auto & func, const auto & lhs, const auto & rhs) {
return [func, lhs, rhs](){
return func(lhs, rhs);
};
};

int main(const int argc, const char * []) {
auto l = lazy(add, argc, 4);
return l();
}

Ans: Implementaion in C++14 (for simplicity) is below



2. Explain the difference between

template<typename First, typename Second>
struct Pair_1 {
First first;
Second second;
};

template<typename First, typename Second>
struct Pair_2 {
First first;
Second second;

template<typename First_, typename Second_>
Pair_2(First_ &&first_, Second_ &&second_) :
first(std::forward<First_>(first_)),
second(std::forward<Second_>(second_))
{
}
};

What happens when I construct one?
What is the constexpr story?
Should Pair_2's constructor be explicit?
In what context can Pair_1 be constructed?

 **************/

// Question 1 (C++98)

// auto add = [](const auto & lhs, const auto & rhs) { return lhs+rhs;};

class Add {
	public:
		/*
		   template <typename T1, typename T2>
		// inline auto operator()(const T1 & lhs, const T2 & rhs) const  // C++14
		inline auto operator()(const T1& lhs, const T2& rhs) const
		-> decltype(lhs + rhs) // C++11
		{
		return lhs + rhs;
		}
		*/

		// C++98
		template <typename T>
			T operator()(const T& lhs, const T& rhs) const {
				return lhs + rhs;
			}

		template <typename T1, typename T2>
			class Return_Type {
				public:
					typedef T1 type;
			};
};
Add add;

/*
   auto lazy = [](const auto & func, const auto & lhs, const auto & rhs) {
   return [func, lhs, rhs](){
   return func(lhs, rhs);
   };
   };
   */

class Lazy {
	template <typename Func_t, typename Lhs_t, typename Rhs_t>  // made template in C++11
		class inner_lazy {
			private:
				Func_t func;
				Lhs_t lhs;
				Rhs_t rhs;

			public:
				// inline auto operator()() const  // C++14
				// inline auto operator()() const -> decltype(func(lhs, rhs))  // C++11
				typename Func_t::template Return_Type<Lhs_t, Rhs_t>::type operator()()
					const {
						return func(lhs, rhs);
					}

				inner_lazy(const Func_t& _func, const Lhs_t& _lhs, const Rhs_t& _rhs)
					: func(_func), lhs(_lhs), rhs(_rhs) {}
		};

	public:
	template <typename Func_t, typename Lhs_t, typename Rhs_t>
		// inline auto operator()(const Func_t& func, const Lhs_t& lhs, const Rhs_t&
		// rhs) const  // C++14
		inline inner_lazy<Func_t, Lhs_t, Rhs_t> operator()(
			const Func_t& func, const Lhs_t& lhs, const Rhs_t& rhs) const  // C++98
		{
			/*  Moved out to private in C++11
				class inner_lazy {
				private:
				Func_t func;
				Lhs_t lhs;
				Rhs_t rhs;

				public:
			//inline auto operator()() const  // C++14
			inline auto operator()() const -> decltype(func(lhs, rhs)) // C++11
			{
			return func(lhs, rhs);
			}

			inner_lazy(const Func_t & _func, const Lhs_t & _lhs, const Rhs_t &
			_rhs) : func(_func), lhs(_lhs), rhs(_rhs) { }

			};

*/
			return inner_lazy<Func_t, Lhs_t, Rhs_t>(func, lhs, rhs);
		}
};
Lazy lazy;

// Question 2 (C++11)
#include <utility>
#include <cstdio>

template <typename First, typename Second>
struct Pair_1 {
	First first;
	Second second;
};

template <typename First, typename Second>
struct Pair_2 {
	First first;
	Second second;

	template <typename First_, typename Second_>
		Pair_2(First_&& first_, Second_&& second_)
		: first(std::forward<First_>(first_)),
		second(std::forward<Second_>(second_)) {}
};

struct Helper {
	Helper() {std::puts("Helper()");}
	~Helper() {std::puts("~Helper()");}

	Helper(const Helper &) {std::puts("Helper(const Helper &)");}
	Helper& operator=(const Helper &) {std::puts("Helper& operator=(const Helper &)"); return *this; }

	Helper(Helper && ) {std::puts("Helper(Helper && )");}
	Helper& operator=(Helper &&) {std::puts("Helper& operator=(Helper &&)"); return *this; }
};

int main(const int argc, const char*[]) {
	/*
	   auto l = lazy.operator()(add, argc, 4);
	   return l();
	   */
	{
		Pair_1<Helper, Helper> p1{Helper{}, Helper{}};
	}
	std::puts("---------------------");
	Pair_2<Helper, Helper> p2{Helper{}, Helper{}};

	return lazy(add, argc, 4)();
}

/*****
  END OF FILE
 ****/

