/*****

References

    Programming with C++20 | Andreas Fertig
	

Chapter 7 | Lambdas in C++20: New features
	
	There are several changes therein to make lambdas even more powerful.

7.2 Default-constructible lambdas

	Lambdas are considered default-constructible, if they have no captures.
	
	Let's create a map with a custom compare function
	
	The tricky part is that we need to pass the cmp-function as an argument during construction of the map.
	Not only that, a user needs to pass cmp as a constructor argument, so they also need to know the name of the function.
	
	Passing a different function than cmp will lead to a compiler error in this case.
	If we had chosen a function instead of a lambda, passing an entirely different function would be possible.
	Only the function’s signature has to match. With that, it would break the promise of the type’s name.
	
	Why do we need to pass cmp not only as a type to the std::map but also as a constructor argument?
	std::map can default construct an object of the compare-type, if we provide no custom compare function.
	Now, here is the but, in C++17 and before, lambdas are not default-constructible.
	The standard defines them with a deleted default constructor.
	
	This restriction is lifted in C++20.
	We can drop naming the compare function from the constructor’s argument list.
	With that, users no longer need to know the name of the compare function and don’t have to type it.

**********/

#include <iostream>
#include <string>
#include <map>

struct Book {
    std::string     m_title;
    std::string     m_isbn;
};

struct Price {
    double          m_price;
};

auto cmp_book = [](const Book & b1, const Book & b2) {
    return b1.m_isbn > b2.m_isbn;
};

auto cmp_book_fun(const Book & b1, const Book & b2) {
    return b1.m_isbn > b2.m_isbn;
};

auto another_cmp_book_fun(const Book & b1, const Book & b2) {
    return b1.m_isbn > b2.m_isbn;
};


int main() {
    const Book  book{"Book-1", "2025-01"};
    const Price price{256.39};

    {   std::puts("using lambda to compare");

        using map_book_price_t = std::map<Book, Price, decltype(cmp_book)>;

#if __cplusplus == 201703L
        {
            map_book_price_t mp_bp{cmp_book};

            // CE error: no matching constructor for initialization of '(lambda at <source>:57:17)'
            //map_book_price_t mp_bp;
            //map_book_price_t mp_bp{cmp_book_fun};       // NOK different type
        }
#endif

#if __cplusplus == 202002L
        {
            map_book_price_t mp_bp;
            mp_bp.emplace(book, price);
            //map_book_price_t mp_bp{cmp_book};         // this is also OK

            //map_book_price_t mp_bp{cmp_book_fun};     // NOK different type
        }
#endif

    }


    {   std::puts("using function instead of lambda to compare");

        using another_map_book_price_t = std::map<Book, Price, bool (*)(const Book &, const Book &)>;

#if __cplusplus == 201703L
        {
            another_map_book_price_t mp_bp(cmp_book_fun);
            another_map_book_price_t mp_bp2(another_cmp_book_fun);  // different comparison func with same signature
            another_map_book_price_t mp_bp3(cmp_book);              // capture less lambda is compatible with FP
        }
#endif

#if __cplusplus == 202002L
        {
            another_map_book_price_t mp_bp;
            mp_bp.emplace(book, price);

            another_map_book_price_t mp_bp1(cmp_book_fun);
            another_map_book_price_t mp_bp2(another_cmp_book_fun);  // different comparison func with same signature
            another_map_book_price_t mp_bp3(cmp_book);              // capture less lambda is compatible with FP
        }
#endif

    }

    {   std::puts("using lambda with capture");

        const std::string capstr{"Lambda with capture"};
        auto cap_cmp_book = [capstr](const Book & b1, const Book & b2) {
            return b1.m_isbn > b2.m_isbn;
        };

        using another_map_book_price_t = std::map<Book, Price, decltype(cap_cmp_book)>;

#if __cplusplus == 201703L
        {
            another_map_book_price_t    mp_bp{cap_cmp_book};
        }
#endif

#if __cplusplus == 202002L
        {
            // lambda with capture are not default constructible so need to provie in cx
            another_map_book_price_t    mp_bp{cap_cmp_book};
        }
#endif

    }

	return 0;
}

/*****
    END OF FILE
**********/


