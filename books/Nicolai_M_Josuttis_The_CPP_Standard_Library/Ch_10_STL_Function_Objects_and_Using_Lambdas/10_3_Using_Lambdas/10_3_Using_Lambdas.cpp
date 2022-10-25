/***************

References
    The C++ Standard Library Second Edition | Nicolai M. Josuttis

10.3 Using Lambdas
    Lambdas provide significant improvements for C++ when using the STL because now you have an intuitive, readable way to pass individual behavior to algorithms and container member functions.

10.3.1 Lambdas versus Binders
    Lambda gives clean, efficient code over bind, prefer lambda over bind

10.3.2 Lambdas versus Stateful Function Objects
    When dealing with state, you should also be careful when using mutable.

10.3.3 Lambdas Calling Global and Member Functions

10.3.4 Lambdas as Hash Function, Sorting, or Equivalence Criterion
    use decltype to pass the type of the lambda to the container because it creates its own instance of them. 
    In addition, you have to pass a hash function and equivalence criterion to the constructor because otherwise, 
    the constructor calls the default constructor for the hash function and equivalence criterion, which is not defined for lambdas.

************/

#include <functional>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

class MeanValue {
	long num, sum;
    public:
	MeanValue () : num(0), sum(0) { }
	void operator() (int elem) {
		++num;
		sum += elem;
	}
	double value () {
		return static_cast<double>(sum) / static_cast<double>(num);
	}
};

void display(const std::string msg) {
        std::clog << msg << '\n';
}

class St {
    std::string msg;
    public:
    St(const std::string msg) : msg(msg) { }
    void display() const {
        std::clog << msg << '\n';
    }
};

class Person {
    std::string name;
    uint32_t age;

   public:
    Person(const std::string name, const uint32_t age) : name(name), age(age) {}
    std::string get_name() const { return name; }
    uint32_t get_age() const { return age; }
};

int main() {

    // 10.3.1 Lambdas versus Binders | bind
    {
        auto plus10 = std::bind(std::plus<int>(), std::placeholders::_1, 10);
        std::clog << "plus10(7): " << plus10(7) << '\n';
        auto plus10times2 = std::bind(std::multiplies<int>(),
            std::bind(std::plus<int>(), std::placeholders::_1, 10), 
            2);
        std::clog << "plus10times2(7): " << plus10times2(7) << '\n';
    }

    // 10.3.1 Lambdas versus Binders | Lambda
    {
        auto plus10 = [](int val){ return val + 10;};
        std::clog << "plus10(7): " << plus10(7) << '\n';
        auto plus10times2 = [](int val){ return (val + 10) * 2;};
        std::clog << "plus10times2(7): " << plus10times2(7) << '\n';
    }
    
    // 10.3.2 Stateful Function Objects | calculating mean value
    {
        std::vector<int> vec{11, 12, 13, 14, 15, 16, 17, 18, 19};
        MeanValue mv_obj;
        MeanValue mv = std::for_each (vec.begin(), vec.end(), mv_obj);
        std::clog << "mean value: " << mv.value() << '\n';
    }

    // 10.3.2 Lambda | calculating mean value
    {
        std::vector<int> vec{11, 12, 13, 14, 15, 16, 17, 18, 19};
        long sum = 0;
        std::for_each (vec.begin(), vec.end(), [&sum](const int elem){ sum += elem;});
        std::clog << "mean value: " << static_cast<double>(sum) / static_cast<double>(vec.size()) << '\n';
    }

    // 10.3.3 Lambdas Calling Global Functions
    {
        std::vector<std::string> vec{"Good morning", "Good evening", "Good night"};
        std::for_each(vec.begin(), vec.end(), [](const std::string msg){ display(msg);});
    }

    // 10.3.3 Lambdas Calling Member Functions
    {
        std::vector<St> vec{St("Good morning"), St("Good evening"), St("Good night")};
        std::for_each(vec.begin(), vec.end(), [](const St & stobj){ stobj.display();});
    }

	// 10.3.4 Lambdas as Hash Function, Sorting, or Equivalence Criterion
    auto cmp_criteria = [](const Person& p1, const Person& p2) {
        return p1.get_name() < p2.get_name() ||
        (p1.get_name() == p2.get_name() && p1.get_age() < p2.get_age());
        };

    
    std::set<Person, decltype(cmp_criteria)> set_person(cmp_criteria);
    set_person.emplace(R"(person-13)", 22);
    set_person.emplace(R"(person-11)", 30);
    set_person.emplace(R"(person-14)", 32);
    set_person.emplace(R"(person-12)", 20);
    std::clog << "Person set\n";
    for(const auto & elem : set_person) {
        std::clog << elem.get_name() << ' ' << elem.get_age() << '\n';
    }

    return 0;
}

/*********
    END OF FILE
********/

