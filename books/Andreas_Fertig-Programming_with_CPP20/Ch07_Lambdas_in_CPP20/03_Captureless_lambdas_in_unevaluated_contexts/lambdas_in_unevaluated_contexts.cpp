/*****

References

    Programming with C++20 | Andreas Fertig


Chapter 7 | Lambdas in C++20: New features

    There are several changes therein to make lambdas even more powerful.

7.3 Captureless lambdas in unevaluated contexts

	Since C++20, we could define lambdas in unevaluated contexts.
	
	lambdas in a decltype expression, or in an unevaluated context in general, only work with captureless lambdas.
	Lambdas with captures need arguments during construction, the captures of which are not available in an unevaluated context.

**********/

#include <iostream>
#include <map>
#include <string>

struct Book {
    std::string m_title;
    std::string m_isbn;
};

struct Price {
    double m_price;
};


int main() {
    const Book book{"Book-1", "2025-01"};
    const Price price{256.39};

#if __cplusplus == 201703L
    {
        std::puts("using lambda to compare");

        {
            auto cmp_book = [](const Book& b1, const Book& b2) {
                return b1.m_isbn > b2.m_isbn;
            };
            using map_book_price_t = std::map<Book, Price, decltype(cmp_book)>;

            map_book_price_t mp_bp{cmp_book};
        }

        {
            /* CE error: lambda-expression in unevaluated context only available
            with '-std=c++20' or '-std=gnu++20' using map_book_price_t =
            std::map<Book, Price, decltype([](const Book & b1, const Book & b2)
            { return b1.m_isbn > b2.m_isbn;
                    })
            >;

            map_book_price_t    mp_bp;
            mp_bp.emplace(book, price);
            */
        }
    }
#endif

#if __cplusplus == 202002L
    {
        std::puts("using lambda to compare");
        {
            using map_book_price_t =
                std::map<Book, Price,
                         decltype([](const Book& b1, const Book& b2) {
                             return b1.m_isbn > b2.m_isbn;
                         })>;

            map_book_price_t mp_bp;
            mp_bp.emplace(book, price);
        }

        {
            using cmp_book_t = decltype([](const Book& b1, const Book& b2) {
                return b1.m_isbn > b2.m_isbn;
            });

            using map_book_price_t = std::map<Book, Price, cmp_book_t>;

            map_book_price_t mp_bp;
            mp_bp.emplace(book, price);
        }

        std::puts("using lambda with capture to compare");

        {
            const std::string capstr{"Lambda with capture"};
            /*
            // CE error: no matching constructor for initialization of '(lambda at <source>:103:35)'
            using map_book_price_t =
                std::map<Book, Price,
                         decltype([capstr](const Book& b1, const Book& b2) {
                             return b1.m_isbn > b2.m_isbn;
                         })>;

            map_book_price_t mp_bp;
            mp_bp.emplace(book, price);
            */

        }

        {
            const std::string capstr{"Lambda with capture"};
            /*  CE error: no matching constructor for initialization of '(lambda at <source>:116:41)'
            using cmp_book_t = decltype([capstr](const Book& b1, const Book& b2) {
                return b1.m_isbn > b2.m_isbn;
            });

            using map_book_price_t = std::map<Book, Price, cmp_book_t>;

            map_book_price_t mp_bp;
            mp_bp.emplace(book, price);
            */
        }

    }
#endif

    return 0;
}

/*****
    END OF FILE
**********/

