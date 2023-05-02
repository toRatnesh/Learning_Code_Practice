/*****

    This example demonstrates about use of
    capture less lambda in unevaluated contexts since C++20

    For more info visit:
    C++ Insights - Episode 34: https://www.youtube.com/watch?v=vcBqlkWvmFw
    C++ Weekly - Ep 149:
https://github.com/socialratnesh/Learning_Code_Practice/tree/main/cpp_weekly/ep149_cpp20_Lambda_Usability_Changes

***********/

#include <iostream>
#include <set>
#include <string>

class Person {
    std::string name;
    uint32_t age;

   public:
    Person(const std::string name, uint32_t age) : name(name), age(age) {}
    auto get_name() const { return name; }
    auto get_age() const { return age; }
};

auto cmp_criteria = [](const Person& p1, const Person& p2) {
    return p1.get_name() < p2.get_name() ||
           ((p1.get_name() == p2.get_name()) && (p1.get_age() < p2.get_age()));
};

void display(const auto& set_person) {
    for (const auto& elem : set_person) {
        std::cout << elem.get_name() << ' ' << elem.get_age() << '\n';
    }
}

int main() {
    std::cout << "=== pre C++20 ===\n";
    std::set<Person, decltype(cmp_criteria)> set_person1(cmp_criteria);  // pre C++20 need to pass comparison function in constructor
    set_person1.emplace(R"(person-13)", 22);
    set_person1.emplace(R"(person-11)", 30);
    set_person1.emplace(R"(person-11)", 25);
    set_person1.emplace(R"(person-14)", 32);
    set_person1.emplace(R"(person-12)", 20);
    set_person1.emplace(R"(person-12)", 25);
    display(set_person1);

    std::cout << "=== since C++20 default constructable lamda ===\n";
    std::set<Person, decltype(cmp_criteria)> set_person2{};  // no need to pass comparison function to constructor
    set_person2.emplace(R"(person-13)", 22);
    set_person2.emplace(R"(person-11)", 30);
    set_person2.emplace(R"(person-11)", 25);
    set_person2.emplace(R"(person-14)", 32);
    set_person2.emplace(R"(person-12)", 20);
    set_person2.emplace(R"(person-12)", 25);
    display(set_person2);

    std::cout << "=== since C++20 lambda in unevaluated context ===\n";
    std::set<Person, decltype([](const Person& p1, const Person& p2) {
                 return p1.get_name() < p2.get_name() ||
                        ((p1.get_name() == p2.get_name()) &&
                         (p1.get_age() < p2.get_age()));
             })> set_person3{};  // lamda can be used directly as comaparator
    set_person3.emplace(R"(person-13)", 22);
    set_person3.emplace(R"(person-11)", 30);
    set_person3.emplace(R"(person-11)", 25);
    set_person3.emplace(R"(person-14)", 32);
    set_person3.emplace(R"(person-12)", 20);
    set_person3.emplace(R"(person-12)", 25);
    display(set_person3);

    return 0;
}

/****
    END OF FILE
*******/


