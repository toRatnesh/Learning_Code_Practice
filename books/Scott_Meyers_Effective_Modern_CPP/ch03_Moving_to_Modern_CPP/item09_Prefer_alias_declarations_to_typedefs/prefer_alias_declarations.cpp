/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/type_alias
    https://learn.microsoft.com/en-us/cpp/cpp/aliases-and-typedefs-cpp?view=msvc-170


Item 9: Prefer alias declarations to typedefs

alias declarations vs typedefs

    Consider a unique pointer to std::unordered_map<std::string, std::string>

    Writing
        std::unique_ptr<std::unordered_map<std::string, std::string>>
    everytime will be too much verbose 


    Introduce a typedef:
        typedef	std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS;

    C++11 also offers alias declarations:
        using UPtrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;


alias templates
    alias declarations may be templatized (in which case they’re called alias templates), while typedefs cannot

    For example, consider defining a synonym for a linked list that uses a custom allocator, MyAlloc

        template<typename T>
        using MyAllocList = std::list<T, MyAlloc<T>>;	// MyAllocList<T> is synonym for std::list<T, MyAlloc<T>>

        MyAllocList<Widget> lw; // client code



        template<typename T>
        struct MyAllocList { 
            typedef std::list<T, MyAlloc<T>> type;		// MyAllocList<T>::type is synonym for std::list<T, MyAlloc<T>>
        };

        MyAllocList<Widget>::type lw; // client code


accessing nested type 

    If you want to use the typedef inside a template for the purpose of 
    creating a linked list holding objects of a type specified by a template parameter, 

    you have to precede the typedef name with typename

        template<typename T>
        class Widget {
            private:
            typename MyAllocList<T>::type list;	// Widget<T> contains a MyAllocList<T> as a data member
        };


    Here, MyAllocList<T>::type refers to a type that’s dependent on a template type parameter (T). 
    MyAllocList<T>::type is thus a dependent type, and
    one of C++’s many endearing rules is that the names of dependent types must be preceded by type name.

    If MyAllocList is defined as an alias template, this need for typename vanishes

        template<typename T>
        using MyAllocList = std::list<T, MyAlloc<T>>; // as before

        template<typename T>
        class Widget {
            private:
            MyAllocList<T> list;	// no "typename", no "::type"
            …
        };


    When compilers process the Widget template and encounter the use of MyAllocList<T> (i.e., use of the alias template), 
    they know that MyAllocList<T> is the name of a type, because MyAllocList is an alias template: it must name a type.
    MyAllocList<T> is thus a non-dependent type, and a typename specifier is neither required nor permitted.

using alias templates C++11 vs C++14

    C++11 gives you the tools to perform these kinds of transformations in the form of type traits, 
    an assortment of templates inside the header <type_traits>.

    Given a type T to which you’d like to apply a transformation, the resulting type is std::transformation <T>::type. For example:

    C++11 type traits are implemented as nested typedefs inside templatized structs.
    That’s right, they’re implemented using the type synonym technology which is inferior to alias templates!

    the Standardization Committee belatedly recognized that alias templates are the better way to go, 
    and they included such templates in C++14 for all the C++11 type transformations. 

    The aliases have a common form: for each C++11 transformation std::transformation<T>::type, 
    there’s a corresponding C++14 alias template named std::transformation_t.

        std::remove_const<T>::type			// C++11: const T → T
        std::remove_const_t<T>				// C++14 equivalent

        std::remove_reference<T>::type		// C++11: T&/T&& → T
        std::remove_reference_t<T>			// C++14 equivalent

        std::add_lvalue_reference<T>::type	// C++11: T → T&
        std::add_lvalue_reference_t<T>		// C++14 equivalent



Summary

    • typedefs don’t support templatization, but alias declarations do.
    • Alias templates avoid the “::type” suffix and, in templates, the “typename” prefix often required to refer to typedefs.
    • C++14 offers alias templates for all the C++11 type traits transformations.

**********/

#include <iostream>
#include <memory>
#include <map>

namespace using_alias {
    template<typename K, typename V>
    using my_map_t = std::map<K, V, std::greater<K>>;

    template<typename K, typename V>
    class Widget {
        private:
        my_map_t<K, V> m_map;
    };

}

namespace using_tyedef {
    template<typename K, typename V>
    //typedef std::map<K, V, std::greater<K>> my_map_t; error: template declaration of 'typedef'

    struct my_map_t {
        typedef std::map<K, V, std::greater<K>> type;
    };


    template<typename K, typename V>
    class Widget {
        private:
        typename my_map_t<K, V>::type m_map;    // need to use "typename" and "type"
    };
    
    template<typename K, typename V>
    using alias_my_map_t = typename my_map_t<K, V>::type;

    template<typename K, typename V>
    class ImprovedWidget {
        private:
        alias_my_map_t<K, V> m_map;    // need to use "typename" and "type"
    };

}

int main() {

    {   std::puts("alias declarations vs typedefs");
        {
            typedef std::unique_ptr<std::map<std::string, std::string>> up_map_ss_t;
            up_map_ss_t lup_map_ss = std::make_unique<std::map<std::string, std::string>>();
        }

        {
            using up_map_ss_t = std::unique_ptr<std::map<std::string, std::string>>;
            up_map_ss_t lup_map_ss = std::make_unique<std::map<std::string, std::string>>();
        }
    }

    {   std::puts("alias templates");
        {
            using_alias::my_map_t<std::string, std::string> l_map;
            l_map.emplace("key-1", "val-1");
        }
        {
            using_tyedef::my_map_t<std::string, std::string>::type l_map;   // need to use ::type
            l_map.emplace("key-1", "val-1");
        }   

    }

    {   std::puts("accessing nested type");
        {
            using_alias::Widget<std::string, std::string> lw;
        } 
        {
            using_tyedef::Widget<std::string, std::string> lw;
        }     
        
    }

    {
        std::puts("using alias templates C++11 vs C++14");
        {
            using_tyedef::ImprovedWidget<std::string, std::string> lw;
        }         
    }

    return 0; 
}

/*****
    END OF FILE
**********/


