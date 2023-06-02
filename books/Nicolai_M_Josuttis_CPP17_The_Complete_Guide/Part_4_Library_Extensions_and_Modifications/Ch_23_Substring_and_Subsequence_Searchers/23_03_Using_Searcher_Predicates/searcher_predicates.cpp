/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/algorithm/search
    https://en.cppreference.com/w/cpp/header/functional#Searchers

Chapter 23 Substring and Subsequence Searchers

	C++17 therefore introduced the Boyer-Moore and Boyer-Moore-Horspool search algorithms

23.3 Using Searcher Predicates
	predicates might be necessary for two reasons:
	-> to compare two elements
	-> to provide a hash function
	
	using a predicate might create a significant overhead to using searchers
	
*************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

class Student {
    std::string     id;
    std::string     name;
    public:
    Student(std::string id, std::string name) : 
            id(std::move(id)), name(std::move(name)) { }
    std::string getId() const { return id; }
};

int main() {
    std::cout << "=== Using Searcher Predicates ===\n";

    std::vector<Student>    ivec_coll;
    for(int i = 0; i < 100000; ++i) {
        std::string id      = std::string("st_id") + std::to_string(i*3);
        std::string name    = std::string("student-") + std::to_string(i);
        ivec_coll.push_back({id, name});
    }
    std::vector<Student>    search_this{{"st_id30", "student-10"}, {"st_id33", "student-11"}};
    {   
        std::boyer_moore_searcher   bms{search_this.begin(), search_this.end(),
                                [](const Student & st){ return std::hash<std::string>{}(st.getId()); },
                                [](const Student & st1, const Student & st2){ return st1.getId() == st2.getId();}
                                };
        
        for(auto [pos_b, pos_e] = bms(ivec_coll.begin(), ivec_coll.end());
                    ivec_coll.end() != pos_b;
                    std::tie(pos_b, pos_e) = bms(pos_e, ivec_coll.end())) 
        {
            std::cout << "Found subset at index " << (pos_b-ivec_coll.begin()) << '-' << (pos_e-ivec_coll.begin()) << '\n';
        }
    }

    return 0;
}

/**********
    END OF FILE
*************/


