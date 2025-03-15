/*****

References
    Programming with C++20 | Andreas Fertig

    https://en.cppreference.com/w/cpp/concepts
    https://en.cppreference.com/w/cpp/language/requires

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.

1.13 Concepts ordering

	So how does the compiler decide which one to pick?
	The rule is that the lookup in the overload-set for a match starts with 
	the most constrained function and walks its way down to the least constrained one.

    A function with no constraint counts as least constrained as well.

    What if things get more complicated?
    For example, consider a type that do not release their data in the destructor, as they are shared.
    Instead, it has a release method.
    Now, we assume that wrapper should act differently on a type with a Release method.

	write mutually exclusive requires-clauses.

	For the constraint evaluation, one constraint can subsume another constraint.
	Consider concepts a and b, and least and most constrained combinations of these. 
	Using boolean algebra, we can formulate the following:

	a∧(a∨b) = a∨b		(1.1)
	a∨(a∧b) = a			(1.2)

	In Eq. (1.1) a∨b subsumes a, while in Eq. (1.2) a subsumes a∧b.

	Constraint subsumption works only with concepts. This is a strong case to define named concepts instead of applying requires-clauses.

	To summarize, prefer named concepts over ad hoc constraints or type-traits.

1.13.1 Subsumption rule details

	Subsumption rules of concepts can get very complex.

	The compiler sees the template arguments in this case as the textual values we use, 
	not the types after or during instantiation. With that, we have IsSame<U, T> vs. IsSame<T, U>.

    To evaluate whether both concepts are the same, the compiler looks 
    into their definition, which is is_same_v<U, T> and is_same_v<T, U>.

	Once again, the textual names are kept, no types are involved.
	So far, IsSame is seen as different by the compiler.

    To make multi-parameter concepts work regardless of the argument order, 
    we need to add a concept that does that swapping.

1.13.2 One more thing, never say not

	The moment we apply not or ! to a concept, the operands become part of the expression.
	In this context, an expression can be seen as a source location.
	Two concepts are only equal if they originate from the same written source (location).
	By adding the not and making that entire part an expression, 
	the two negated IsSame are different concepts in the compiler’s view.

	A guiding rule here, stay positive with your concepts and try to avoid negating them.

**********/

#include <iostream>
#include <string>


/*
    What if things get more complicated?
    For example, consider a type that do not release their data in the destructor, as they are shared.
    Instead, it has a release method.
    Now, we assume that wrapper should act differently on a type with a Release method.
*/
template<typename T>
concept has_release = requires(T t) { t.release(); };

template<typename T>
concept not_trivially_destructible = not std::is_trivially_destructible_v<T>;


template<typename T>
union storage_t {
    using aligned_storage_t = std::aligned_storage_t<sizeof(T), alignof(T)>;
    aligned_storage_t data;
    
    storage_t() = default;
    storage_t(T t) : data{t} {}
    T* as() { return reinterpret_cast<T*>(&data); }
    // use placement new to create an instance of T inside this union
};

struct Td { };

struct NonTd {
    ~NonTd()    { std::cout << "~NonTd\n"; }
    NonTd()     { std::cout << "NonTd\n"; }
};

struct WithRelease {
    ~WithRelease()    { std::cout << "~WithRelease\n"; }
    WithRelease()     { std::cout << "WithRelease\n"; }
    void release()     { std::cout << "release\n"; }
};

struct TdWithRelease { 
    void release()     { std::cout << "release for TdWithRelease\n"; }
};

template<typename T>
class my_wrapper_cpp20
{
    storage_t<T>    data;
    bool            has_value{false};

    public:

    my_wrapper_cpp20() : data() {

    };

    my_wrapper_cpp20(T val) : data(val) {
        has_value = true;
    };

    my_wrapper_cpp20(const my_wrapper_cpp20 & other)  
    requires std::is_copy_constructible_v<T>
    : data(other.data) {
        has_value = true;
    }
/* 

    This doesn’t compile. 
    The compiler ends up finding two destructors, A and B . 
    The reason is that both requires-clauses yield true and both destructors are constrained. 
    Before, we had the case of a constrained and an unconstrained one. 
    One way to handle this is to write mutually exclusive requires-clauses.

    For the constraint evaluation, one constraint can subsume another constraint.

    To solve the situation with the destructors, we need to define a second concept not_trivially_destructible 
    and replace the type-trait in the destructors requires-clauses with that.


    THESE DESTRUCTORS HAVE ISSUES OF CONSTRAINT SUBSUMPTION
    // destructor A
    ~my_wrapper_cpp20() 
    requires(not std::is_trivially_destructible_v<T>) {
        if(has_value) { 
            data.as()->~T();
            std::cout << "non trivial destructor\n";
        }
    }

    // destructor B
    ~my_wrapper_cpp20() 
    requires(not std::is_trivially_destructible_v<T> and has_release<T>) {
        if(has_value) { 
            data.as()->release();
            data.as()->~T();
            std::cout << "release and destructor\n";
        }
    }

 */
    // FOLLOWING DESTRUCTORS ARE CORRECT

    /*
        Now the compiler sees that both clauses contain not_trivially_destructible, but B has has_release in addition.
        This results in B subsuming A, giving us the final destructor for this type.

        The defaulted default destructor is unconstrained, making it the least constrained method.
    */
    // destructor A
    ~my_wrapper_cpp20() 
    requires(not_trivially_destructible<T>) {
        if(has_value) { 
            data.as()->~T();
            std::cout << "non trivial destructor\n";
        }
    }

    // destructor B
    ~my_wrapper_cpp20() 
    requires(not_trivially_destructible<T> and has_release<T>) {
        if(has_value) { 
            data.as()->release();
            data.as()->~T();
            std::cout << "release and destructor\n";
        }
    }

    // destructor C
    ~my_wrapper_cpp20() 
    requires(has_release<T>) {
        if(has_value) { 
            data.as()->release();
            
            std::cout << "release\n";
        }
    }

    ~my_wrapper_cpp20() = default;

};

// 1.13.1 Subsumption rule details


template<typename T, typename U>
concept incorrect_is_same = std::is_same_v<T, U>;

template<typename T, typename U>
concept is_same_helper = std::is_same_v<T, U>;
template<typename T, typename U>
concept correct_is_same = is_same_helper<T, U> and is_same_helper<U, T>;
// The latter one is a concept. Remember that only concepts can take part in subsumption.


// only purpose of this concept is to have a second, different concept
template<typename T>
concept always_true = true;

template<typename T, typename U>
requires incorrect_is_same<T, U>
auto xadd(const T & t, const U & u) {
    std::cout << "Less constraint add\n";
    return t+u;
}

template<typename T, typename U>
requires incorrect_is_same<T, U> and always_true<T>
auto xadd(const T & t, const U & u) {
    std::cout << "More constraint add\n";
    return t+u;
}   

// Following xsub is same as xadd example but to demonstrates
// it has dirrent sequence in requires clause in 1st xsub
// this is
template<typename T, typename U>
//requires incorrect_is_same<U, T>
requires correct_is_same<U, T>
auto xsub(const T & t, const U & u) {
    std::cout << "Less constraint sub\n";
    return t-u;
}

template<typename T, typename U>
//requires incorrect_is_same<T, U> and always_true<T>
requires correct_is_same<T, U> and always_true<T>
auto xsub(const T & t, const U & u) {
    std::cout << "More constraint sub\n";
    return t-u;
}

// 1.13.2 One more thing, never say not

template<typename T, typename U>
concept not_is_same = not correct_is_same<T, U>;

template<typename T, typename U>
// requires(not correct_is_same<T, U>)
requires not_is_same<T, U>
auto xconcat(const T & t, const U & u) {
    std::cout << "Less constraint concat\n";
    return t+u;
}

template<typename T, typename U>
// requires((not correct_is_same<T, U>) and always_true<T>)
requires not_is_same<T, U> and always_true<T>
auto xconcat(const T & t, const U & u) {
    std::cout << "More constraint concat\n";
    return t+u;
}

int main() {

    static_assert(std::is_trivially_destructible_v<Td>);
    static_assert(std::is_trivially_destructible_v<my_wrapper_cpp20<Td>>);

    static_assert(not std::is_trivially_destructible_v<NonTd>);
    static_assert(not std::is_trivially_destructible_v<my_wrapper_cpp20<NonTd>>);

    static_assert(not_trivially_destructible<NonTd>);
    static_assert(not_trivially_destructible<my_wrapper_cpp20<NonTd>>);


    {
        std::cout << "--- trivially destructible ---\n";
        my_wrapper_cpp20<Td> td;
        my_wrapper_cpp20<Td> ctd{td};
    }
    {
        std::cout << "--- non trivially destructible ---\n";
        my_wrapper_cpp20<NonTd> nontd;
        my_wrapper_cpp20<NonTd> cnontd{nontd};
    }
    {
        std::cout << "--- non trivially destructible with release ---\n";
        my_wrapper_cpp20<WithRelease> rel;
        my_wrapper_cpp20<WithRelease> crel{rel};
    }
    {
        std::cout << "--- trivially destructible with release ---\n";
        my_wrapper_cpp20<TdWithRelease> trel;
        my_wrapper_cpp20<TdWithRelease> ctrel{trel};
    }


    {
        std::cout << "=== 1.13.1 Subsumption rule details ===\n";
        // second xadd function is selected because this one is the more constrained one.
        [[maybe_unused]] auto res1 = xadd(3, 5);
        [[maybe_unused]] auto res2 = xadd(3.5, 5.9);

        {
            // error: call to 'xsub' is ambiguous in case we use xsub with incorrect_is_same
            [[maybe_unused]] auto res = xsub(5, 3);
        }
    }

    {
        std::cout << "=== 1.13.2 One more thing, never say not ===\n";
        // error: call to 'xconcat' is ambiguous in case we use not in requires clause
        [[maybe_unused]] auto res = xconcat(3, 5.8);
    }    

    return 0; 
}

/*****
    END OF FILE
**********/


