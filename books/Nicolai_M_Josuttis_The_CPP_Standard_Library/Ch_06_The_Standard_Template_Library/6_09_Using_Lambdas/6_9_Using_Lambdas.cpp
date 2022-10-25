/***************

References
    The C++ Standard Library Second Edition | Nicolai M. Josuttis

6.9 Using Lambdas
    Lambdas, introduced with C++11, define a way to specify functional behavior 
    inside an expression or statement inline argument to algorithms to be used as predicates

The Benefit of Lambdas
    C++ compilers optimize lambdas better than they do ordinary functions.
    To summarize, lambdas provide the first convenient, readable, fast, 
    and maintainable approach to use STL algorithms. 
    You can use lambdas to specify a hash function and/or equivalence criterion of unordered containers.

Using Lambdas as Sorting Criterion

Limits of Lambdas
    When using Lambda as sorting criterion for associative containers,
    Type of Lambda is needed for declaration of container
    You have to pass the lambda object to constructor of container otherwise,
    container would call the default constructor for the sorting criterion passed, 
    and by rule lambdas have no default constructor and no assignment operator

    Lambda can’t have an internal state held over multiple calls of a lambda.
    If you need such a state, you have declare an object or variable in the
    outer scope and pass it by-reference with a capture into the lambda.
    In contrast, function objects allow you to encapsulate an internal state

************/

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

class Person {
    std::string name;
    uint32_t age;

   public:
    Person(const std::string name, uint32_t age) : name(name), age(age) {}
    auto get_name() const { return name; }
    auto get_age() const { return age; }
};

int main() {
    // lambda as predicate
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    const auto res = std::count_if(vec.begin(), vec.end(),
                                   [](const int elem) { return elem > 5; });
    std::clog << "Count of elements in vector greater than 5 is " << res << '\n';

    // Using Lambdas as Sorting Criterion
    std::vector<Person> vec_person;
    vec_person.emplace_back("person-1", 30);
    vec_person.emplace_back("person-2", 20);
    vec_person.emplace_back("person-3", 22);
    vec_person.emplace_back("person-4", 32);
    vec_person.emplace_back("person-5", 20);

    std::clog << "Vector before sorting\n";
    for(const auto & elem : vec_person) {
        std::clog << elem.get_name() << ' ' << elem.get_age() << '\n';
    }

    std::sort(vec_person.begin(), vec_person.end(),
         [](const Person& p1, const Person& p2) {
             return p1.get_age() < p2.get_age();});

    std::clog << "Vector after sorting\n";
    for(const auto & elem : vec_person) {
        std::clog << elem.get_name() << ' ' << elem.get_age() << '\n';
    }

    auto cmp_criteria = [](const Person& p1, const Person& p2) {
        return p1.get_name() < p2.get_name() ||
        (p1.get_name() == p2.get_name() && p1.get_age() < p2.get_age());
        };

    // Limits of Lambdas
    std::set<Person, decltype(cmp_criteria)> set_person(cmp_criteria);
    set_person.emplace(R"(person-13)", 22);
    set_person.emplace(R"(person-11)", 30);
    set_person.emplace(R"(person-14)", 32);
    set_person.emplace(R"(person-12)", 20);
    std::clog << "Person set\n";
    for(const auto & elem : set_person) {
        std::clog << elem.get_name() << ' ' << elem.get_age() << '\n';
    }

    int count = 0;
    auto maintain_lambda_state = [&count](){return ++count; };
    std::clog << maintain_lambda_state() << ' ' << maintain_lambda_state() << ' ' << maintain_lambda_state() << '\n';
    
    return 0;
}

/*********
    END OF FILE
********/

