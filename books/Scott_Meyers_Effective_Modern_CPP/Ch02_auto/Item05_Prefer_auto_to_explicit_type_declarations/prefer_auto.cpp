/*****

References
    Effective Modern C++ | Scott Meyers

Item 5: Prefer auto to explicit type declarations

auto variables have their type deduced from their initializer, so they must be initialized.

auto uses type deduction (see Item 2), it can represent types known only to compilers

auto has advantage over type shortcuts, for example
std::vector<int>    ivec;
auto sz = ivec.size();  // sz's type is std::vector<int>::size_type

Summary:
    -> auto variables must be initialized, are generally immune to type mismatches that can lead to portability or efficiency problems, can ease the process of refactoring, and typically require less typing than variables with explicitly specified types.
    -> auto-typed variables are subject to the pitfalls described in Items 2 and 6.

**********/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

template<typename It>
void displayRange(It begin, It end) {
    while(begin != end) {
        typename std::iterator_traits<It>::value_type curr_val = *begin;
        std::cout << curr_val << ", ";
        ++begin;
    }
    std::cout << '\n';
}

template<typename It>
void displayRangeUsingAuto(It begin, It end) {
    while(begin != end) {
        auto curr_val = *begin;
        std::cout << curr_val << ", ";
        ++begin;
    }
    std::cout << '\n';
}

int main() {

    std::cout << "auto variables must be initialized\n";

    int x1;         // uninitialized or garbage initialized
    //auto x2;      // CE  error: declaration of 'auto x2' has no initializer
    auto x3 = 0;    // well - initialized


    std::vector ivec{1,2,3,4,5,6,7,8,9};
    displayRange(ivec.begin(), ivec.end());
    displayRangeUsingAuto(ivec.begin(), ivec.end());


    std::cout << "auto can represent types known only to compilers\n";
    auto sval1 = std::make_unique<std::string>("This is a string large string value 1");
    auto sval2 = std::make_unique<std::string>("This is a string large string value 2");    
    {
        // C++11
        auto getLessUp = [](const std::unique_ptr<std::string> & val1,
                        const std::unique_ptr<std::string> & val2) {
                            return *val1 < *val2;
                        };
        auto val = getLessUp(sval1, sval2);
        std::cout << val << '\n';
    }
    {
        // C++14
        auto getLessUp = [](const auto & val1, const auto & val2) {
                            return *val1 < *val2;
                        }; 
        auto val = getLessUp(sval1, sval2);
        std::cout << val << '\n';
    }

    
    {
        std::cout << "Advantage over type shortcuts\n";

        std::vector ivec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        unsigned sz1    = ivec.size();
        auto sz2        = ivec.size();  // sz2's type is std::vector<int>::size_type
    }

    {
        std::cout << "auto to avoid unintentional type mismatches\n";
        std::unordered_map<std::string, std::string> umap{
            {"key-1", "val-1"},
            {"key-2", "val-2"},
            {"key-3", "val-3"}
        };

        // compilers convert std::pair<const std::string, std::string> objects to std::pair<std::string, std::string>
        for(const std::pair<std::string, std::string> & elem : umap) { 
            std::cout << elem.first << '-' << elem.second << '\n';
        }
        std::cout << '\n';

        for(const auto & elem : umap) {
            std::cout << elem.first << '-' << elem.second << '\n';
        }
    }

    return 0; 
}

/*****
    END OF FILE
**********/


