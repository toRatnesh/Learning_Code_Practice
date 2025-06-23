/*****


Chapter 7: Templates and Generic Programming

	Generic programming — the ability to write code that is independent of the types of objects being manipulated

	It can be used to compute any computable value. That led to template metaprogramming: the creation of programs 
	that execute inside C++ compilers and that stop running when compilation is complete.


Item 42: Understand the two meanings of typename

	template<class T>		class Widget;	// uses “class”
	template<typename T>	class Widget;	// uses “typename”

	from C++’s point of view, class and typename mean exactly the same thing when declaring a template parameter.
	C++ doesn’t always view class and typename as equivalent, however.

	**Sometimes you must use typename**

	Consider a template for a function


	template <typename C>              // print 2nd element in
	void print2nd(const C& container)  // container;
	{                                  // this is not valid C++!
		if (container.size() >= 2) {
			C::const_iterator iter(
				container.begin());  // get iterator to 1st element
			++iter;                  // move iter to 2nd element
			int value = *iter;       // copy that element to an int
			std::cout << value;      // print the int
		}
	}

	Nested dependent type name:
		The type of iter is C::const_iterator, a type that depends on the template parameter C. 
		Names in a template that are dependent on a template parameter are called dependent names. 
		When a dependent name is nested inside a class, I call it a nested dependent name. 
		C::const_iterator is a nested dependent name. 
		In fact, it’s a nested dependent type name, i.e., a nested dependent name that refers to a type.
		
	
	Non-dependent names:
		Value, has type int.
		int is a name that does not depend on any template parameter. 
		Such names are known as non-dependent names.
		
	
	Nested dependent names can lead to parsing difficulties.
	By default, nested dependent names are not types.
	
	Until C is known, there’s no way to know whether C::const_iterator is a type or isn’t, 
	and when the template print2nd is parsed, C isn’t known.
	C++ has a rule to resolve this ambiguity: if the parser encounters a nested dependent name in a template, 
	it assumes that the name is not a type unless you tell it otherwise. 
	
	By default, nested dependent names are not types.
	
	The general rule is simple: anytime you refer to a nested dependent type name in a template, 
	you must immediately precede it by the word typename.
	
	typename should be used to identify only nested dependent type names; other names shouldn’t have it.
	
	Exception:
		typename must not precede nested dependent type names in a list of base classes or 
		as a base class identifier in a member initialization list.


	template <typename T>
	class Derived : public Base<T>::Nested {    // base class list: typename not allowed
	   public:
		explicit Derived(int x)
			: Base<T>::Nested(x)        // base class identifier in mem.
										// init. list: typename not allowed
			
			// use of nested dependent type name not in a base class list or
			// as a base class identifier in a mem. init. list: typename required

			typename Base<T>::Nested temp;  
			...                             
			
		}  
	};
	
	typedef with typename can be used to make code less verbose
	template <typename IterT>
	void workWithIterator(IterT iter) {

		//typename std::iterator_traits<IterT>::value_type temp(*iter);

		typedef typename std::iterator_traits<IterT>::value_type value_type;
		value_type temp(*iter);
		...
	}
	
	
	the rules surrounding typename varies from compiler to compiler.
	Some compilers accept code where typename is required but missing; 
	some accept code where typename is present but not allowed; 
	and a few (usually older ones) reject typename where it’s present and required. 
	This means that the interaction of typename and nested dependent type names can lead to some mild portability headaches.
	
Summary
	.	When declaring template parameters, class and typename are interchangeable.
	.	Use typename to identify nested dependent type names, except in base class 
		lists or as a base class identifier in a member initialization list.
		
**********/

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <typeinfo>


template<typename T>
void display(const T & val) {
    std::cout << val << '\n';
}

template<class T>
void logit(const T & val) {
    std::cout << val << '\n';
}

template<typename T, typename K>
void extract_node(T & cont, const K key) {
    
    //class T::node_type    node = cont.extract(key);   // Compialtion error
    typename T::node_type    node = cont.extract(key);

    if(node.empty()) {
        std::cout << "node is empty\n";
    }
    else {
        std::cout << node.key() << ' ' << node.mapped() << '\n';
    }
}

template<class T>
void display_map(const T & vmap) {
    std::cout << "Map entry: \n";
    for(const auto & [k, v] : vmap) {
        std::cout << k << ' ' << v << '\n';
    }
    std::cout << '\n';
}


template<typename T>
class Base {

    public:
    class Id_t {
        std::string     m_id;
        T               m_val;

        public:
        Id_t(std::string id, T val) : m_id{id}, m_val{val} { std::cout << "Id(std::string id, T val)\n"; }
        std::string id() { return m_id; }
        T           value() { return m_val; }
    };

    virtual ~Base( ) {  std::cout << "~Base()\n"; }
    Base(Id_t id) : mid{id} { std::cout << "Base(Id_t id)\n"; }
    virtual Id_t        get_id() { return mid; }

    private:
    Id_t    mid;
};


template<typename T>
class Derived : public Base<T>::Id_t {

    // error: need 'typename' before 'Base<T>::Id_t' because 'Base<T>' is a dependent scope
    //using base_id_t = Base<T>::Id_t;
    using base_id_t = typename Base<T>::Id_t;

    public:

    virtual ~Derived( ) {  std::cout << "~Derived()\n"; }
    Derived(std::string id, T val) : Base<T>::Id_t{id, val} { std::cout << "Derived(std::string id, T val)\n"; }
    Derived(base_id_t vid) : Base<T>::Id_t{vid} { std::cout << "Derived(base_id_t vid)\n"; }

    static base_id_t get_id(std::string id, T val) { return base_id_t{id, val}; }
};


int main() {

    std::cout << "=== Accessing nested dependent type names ===\n";

    display("a string value");
    logit("a string value");

    std::map<std::string, std::string>  lmap{
        {"key-1", "val-1"},
        {"key-2", "val-2"},
        {"key-3", "val-3"}
    };

    display_map(lmap);
    extract_node(lmap, "key-2");
    display_map(lmap);


    std::cout << "=== Accessing nested dependent type names in a list of base classes \n or as a base class identifier in a member initialization list ===\n";
    { Derived dobj{"id-1", "value-1"}; }

    //{  Derived<std::string>::base_id_t val = Derived<std::string>::get_id("id-2", "value-2"); }    

    {   std::cout << '\n';
        auto val = Derived<std::string>::get_id("id-2", "value-2"); 
        std::cout << typeid(decltype(val)).name() << '\n';

        decltype(val) val2 = Derived<std::string>::get_id("id-3", "value-3");
    }  
    
    {   std::cout << '\n';
        auto val2 = Derived<std::string>::get_id("id-3", "value-3"); 
        Derived<std::string>     dobj(val2);
    }     


    return 0;
}

/*****
    END OF FILE
**********/
