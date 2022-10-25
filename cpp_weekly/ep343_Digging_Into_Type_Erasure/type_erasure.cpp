/************

  This example demonstrates about type erasure

  Type erasure:
  hide the exact type of an object when you go to work with it
  simpler and faster to compile interfaces
  can work with any type that might be declared in the future
  compilation firewall to prevent recompile the entire library for adding a new type

  For more info visit
https://www.youtube.com/watch?v=iMzEUdacznQ&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=346
https://www.modernescpp.com/index.php/type-erasure


 ***********/

#include <iostream>
#include <functional>

class Base {
	public:
		Base() = default;
		virtual ~Base() = default;

	protected:
		Base(const Base &) = default;
		Base(Base &&) = default;

		Base& operator=(const Base &) = default;
		Base& operator=(Base &&) = default;

};

class Derived_1 : public Base{};
class Derived_2 : public Base{};

void use_base(const Base & base) {
	auto * d1 = dynamic_cast<const Derived_1 *>(&base);
	if(nullptr != d1) {
		std::puts("Base is of type Derived_1");
	}
}

void break_assumtipon_of_dynamic_cast() {
	struct Another_Derived : public Base {};
	use_base(Another_Derived{});

	use_base(Derived_1{});
	use_base(Derived_2{});
}

int function_as_parm(std::function<int (int , int)> func) {
	return func(1, 3);
}

int add(int m, int n) { return m+n; }

int use_function_as_parm() {

	struct S {
		int operator()(int m, int n) {return m+n +value;}
		int value = 0;
	};
	S s1{42};

	return function_as_parm(add) + 
		function_as_parm([](int m, int n) {return m+n;}) +
		function_as_parm(std::bind_front(&S::operator(), &s1));
}

class Animal {
	const void * object;
	void (*speak_impl)(const void *);

	public:
	template<typename Speakable>
		explicit Animal(const Speakable & speakable) : 
			object(&speakable), 
			speak_impl([](const void * obj){
				return static_cast<const Speakable *>(obj)->speak();
			}) 
	{}

	void speak() const { speak_impl(object); }
};

void animal_speak(Animal animal) { animal.speak(); }

void use_animal() {
	// no polymorphism, no dynamic allocations, but still a function indirection
	// from performance prespective we have not gained anything over a virtual function call
	struct Cow { void speak() const { std::puts("Moo"); } };
	struct Sheep { void speak() const { std::puts("Baa"); } };
	animal_speak(Animal{Cow{}});
	animal_speak(Animal{Sheep{}});
}

int main() {
	break_assumtipon_of_dynamic_cast();
	std::puts(std::to_string(use_function_as_parm()).c_str());
	use_animal();
	return 0;
}

/********
  END OF FILE
 *******/


