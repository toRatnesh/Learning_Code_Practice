/*****

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/ranges

Chapter 3 | Ranges: The next generation STL

	Ranges are a new element of the STL that make using algorithms more concise and add the ability to write code in a functional style.
	
3.4 A range algorithm

	A range algorithm is an algorithm specialized to operate on a range.
	Range algorithms are not drop-in replacements. They come with different complexity or execution parameters.
	Range algorithms are executed immediately. This is of significance because views aren’t.
	
3.4.1 Projections for range algorithms

	Projection parameter is like a transform built into the algorithm.

**********/

#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

struct Book{
    std::string     m_title;
    std::string     m_pub_year;
};

void displayBookVec(const std::vector<Book> & cont) {
    for(const auto & elem : cont) {
        std::cout << elem.m_title << " -> " << elem.m_pub_year << '\n';
    }
    std::cout << '\n';
}

int main() {
    {
        std::cout << "=== using std::sort ===\n";
        std::vector<Book>   vec{
            {"Book-1", "1998"},
            {"Book-2", "2002"},
            {"Book-5", "1999"},
            {"Book-3", "2004"},
            {"Book-4", "2003"}
        };

        std::sort(vec.begin(), vec.end(), 
                    [](const Book & b1, const Book & b2){ return b1.m_title < b2.m_title;});

        displayBookVec(vec);          
    }

    {
        std::cout << "=== using std::ranges::sort with Book::m_title as projection ===\n";
        std::vector<Book>   vec{
            {"Book-1", "1998"},
            {"Book-2", "2002"},
            {"Book-5", "1999"},
            {"Book-3", "2004"},
            {"Book-4", "2003"}
        };

        std::ranges::sort(vec, {}, &Book::m_title);

        displayBookVec(vec);          
    }

    {
        std::cout << "=== using std::ranges::sort with Book::m_pub_year as projection ===\n";
        std::vector<Book>   vec{
            {"Book-1", "1998"},
            {"Book-2", "2002"},
            {"Book-5", "1999"},
            {"Book-3", "2004"},
            {"Book-4", "2003"}
        };

        std::ranges::sort(vec, {}, &Book::m_pub_year);

        displayBookVec(vec);          
    }

    {
        std::cout << "=== using std::ranges::sort with default projection and provided comparison ===\n";
        std::vector<Book>   vec{
            {"Book-1", "1998"},
            {"Book-2", "2002"},
            {"Book-5", "1999"},
            {"Book-3", "2004"},
            {"Book-4", "2003"}
        };

        std::ranges::sort(vec, 
        [](const Book & b1, const Book & b2){ return b1.m_title < b2.m_title;});

        displayBookVec(vec);          
    }

	return 0;
}

/*****
    END OF FILE
**********/

