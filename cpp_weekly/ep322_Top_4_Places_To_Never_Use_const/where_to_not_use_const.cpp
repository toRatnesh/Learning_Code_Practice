/*************
  This example demonstrates about a few places where use of 'const' 
  will lead to move via copy resulting in performance loss

  For more info visit:
https://www.youtube.com/watch?v=dGCxMmGvocE&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=324

 ****************/

#include <iostream>
#include <optional>

struct S {
	~S() { std::puts("~S()"); }

	S() { std::puts("S()"); }
	S(const S &) { std::puts("S(const S &)"); }
	S(S &&) noexcept { std::puts("S(S&&)"); }

	S &operator=(const S &) {
		std::puts("operator=(const S &)");
		return *this;
	}
	S &operator=(S &&) noexcept {
		std::puts("operator=(S &&)");
		return *this;
	}
};

// #4 don't `const` non-reference return types
// making non-refernce return type as const will break move operation
// and copy will take place inplace where move could had
inline S get4() { return S{}; }

inline const S getConst4() {  // bad non & const return type
	return S{};
}

// #3 don't `const` local values that need take advantage
//    of implicit move-on-return operations (aka automatic move)
inline S get3() {
	S s;
	return s;
}

inline S getConst3() {
	const S s;  // bad because this object and return type are different
	return s;
}

inline std::optional<S> get32() {
	S s;
	return s;
}

inline std::optional<S> getConst32() {
	const S s;  // bad because this object and return type are different
	return s;
}

// #2 don't `const` non-trivial value parameters that you
//    might need to return directly from the function
inline S get2(S s) { return s; }

inline S getConst2( const S s) {  // return statement makes this bad use of `const`
	return s;     // because we return it, const is bad in function definition!
}

// #1 don't `const` *any* member data!
//    it breaks implicit and explicit moves
//    it breaks common use cases of assignment
//    (you might need to write some accessors!)
struct S_ConstMem {
	const S s;
};

struct S_NonConstMem {
	S s;
};

int main() {

	std::puts("=== 4 ===");
	std::puts("Without const return type move will take place");
	{
		S s42;
		s42 = get4();
	}

	std::puts("With const return type copy will take place");
	{
		S s43;
		s43 = getConst4();
	}

	std::puts("=== 3 ===");
	std::puts("Local return value without const");
	{
		S s31;
		s31 = get3();
	}
	std::puts("---------");
	{
		auto s33 = get32();
	}

	std::puts("Local return value with const");
	{
		S s32;
		s32 = getConst3();
	}
	std::puts("---------");
	{
		auto s34 = getConst32();
	}

	std::puts("=== 2 ===");
	std::puts("non-const function parameter return");
	S s21;
	{
		auto s22 = get2(s21);
	}
	std::puts("---------");
	{
		auto s23 = get2(S{});
	}

	std::puts("const function parameter return");
	{
		auto s24 = getConst2(s21);
	}
	std::puts("---------");
	{
		auto s25 = getConst2(S{}); 
	}

	std::puts("=== 1 ===");
	std::puts("Move of struct with const member is performed via copy");
	{
		S_ConstMem s11 = S_ConstMem{};
		S_ConstMem s12 = std::move(s11);
	}
	std::puts("Move of struct with non-const member");
	{
		S_NonConstMem s13 = S_NonConstMem{};
		S_NonConstMem s14 = std::move(s13);
	}

	return 0;
}

/*******
  END OF FILE
 *****/
