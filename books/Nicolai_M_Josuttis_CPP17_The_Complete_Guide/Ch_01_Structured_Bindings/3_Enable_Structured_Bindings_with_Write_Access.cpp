/********
Reference:  C++17 - The Complete Guide | Nicolai M. Josuttis

Structured Bindings
Structured bindings allow you to initialize multiple entities by the elements or members of an object.

Enable Structured Bindings with Write Access
-> The tuple-like API can use functions that yield references
-> Extend tuple_size for count of members
-> Extend tuple_element for type of members
-> For read-write access, we have to overload the getters for constant and non-constant references

 **********/

#include <iostream>
#include <string>
#include <utility>

namespace nonstd {
    class Student {
        private:
            std::string m_name;
            std::string m_department;
            uint32_t m_rollno;

        public:
            Student(std::string name, std::string department, uint32_t rollno)
                : m_name(name), m_department(department), m_rollno(rollno) {}


            const std::string & name() const        { return m_name; }
            const std::string & department() const  { return m_department; }
            uint32_t rollno() const                 { return m_rollno; }

            std::string & name()        { return m_name; }
            std::string & department()  { return m_department; }
            uint32_t & rollno()         { return m_rollno; }
    };

    // you should have all three overloads, to be able to deal with constant, non-constant, and movable objects
    // decltype(auto)
    // By using this as a return type, roughly speaking, references are returned by reference, but temporaries are returned by value.
    template<std::size_t Idx>
        decltype(auto) get(Student & st) {
            static_assert(Idx < 3);
            if constexpr(0 == Idx) { return st.name(); }
            else if constexpr(1 == Idx) { return st.department(); }
            else { return st.rollno(); }
        }

    template<std::size_t Idx>
        decltype(auto) get(const Student & st) {
            static_assert(Idx < 3);
            if constexpr(0 == Idx) { return st.name(); }
            else if constexpr(1 == Idx) { return st.department(); }
            else { return st.rollno(); }
        }

    template<std::size_t Idx>
        decltype(auto) get(Student && st) {
            static_assert(Idx < 3);
            if constexpr(0 == Idx) { return st.name(); }
            else if constexpr(1 == Idx) { return st.department(); }
            else { return st.rollno(); }
        }
}  // namespace nonstd

// provide a tuple-like API for class for structured bindings
template<> struct std::tuple_size<nonstd::Student> { static constexpr int value = 3; };
template<> struct std::tuple_element<2, nonstd::Student> { using type = uint32_t; };
template<std::size_t Idx> struct std::tuple_element<Idx, nonstd::Student> { using type = std::string; };

int main() {
    {
        std::clog << "=== non-const object ===\n";
        {
            nonstd::Student st("student-1", "ECE", 123);
            auto [n, d, r] = st;
            std::clog << n << ' ' << d << ' ' << r << '\n';
            std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
            std::string str = std::move(n);
            n = "student-2";
            d = "CSE";
            r = 456;
            std::clog << n << ' ' << d << ' ' << r << '\n';
            // changing structure bind values has no effect on original object
            std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
            std::clog << str << '\n';
        }
        {
            nonstd::Student st("student-1", "ECE", 123);
            auto & [n, d, r] = st;
            std::clog << n << ' ' << d << ' ' << r << '\n';
            std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
            std::string str = std::move(n);
            n = "student-2";
            d = "CSE";
            r = 456;
            std::clog << n << ' ' << d << ' ' << r << '\n';
            // changing structure bind values has no effect on original object
            std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
            std::clog << str << '\n';
        }
        {
            nonstd::Student st("student-1", "ECE", 123);
            auto && [n, d, r] = st;
            std::clog << n << ' ' << d << ' ' << r << '\n';
            std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
            std::string str = std::move(n);
            n = "student-2";
            d = "CSE";
            r = 456;
            std::clog << n << ' ' << d << ' ' << r << '\n';
            // changing structure bind values has no effect on original object
            std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
            std::clog << str << '\n';
        }

    }

    {
        std::clog << "=== non-const object ===\n";
        {
            const nonstd::Student st("student-1", "ECE", 123);
            auto [n, d, r] = st;
            std::clog << n << ' ' << d << ' ' << r << '\n';
            std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
            std::string str = std::move(n);
            n = "student-2";
            d = "CSE";
            r = 456;
            std::clog << n << ' ' << d << ' ' << r << '\n';
            // changing structure bind values has no effect on original object
            std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
            std::clog << str << '\n';
        }
        {
            const nonstd::Student st("student-1", "ECE", 123);
            auto & [n, d, r] = st;
            std::clog << n << ' ' << d << ' ' << r << '\n';
            std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
            std::string str = std::move(n);
            //n = "student-2";
            //d = "CSE";
            //r = 456;
            std::clog << n << ' ' << d << ' ' << r << '\n';
            // changing structure bind values has no effect on original object
            std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
            std::clog << str << '\n';
        }
        {
            const nonstd::Student st("student-1", "ECE", 123);
            auto && [n, d, r] = st;
            std::clog << n << ' ' << d << ' ' << r << '\n';
            std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
            std::string str = std::move(n);
            //n = "student-2";
            //d = "CSE";
            //r = 456;
            std::clog << n << ' ' << d << ' ' << r << '\n';
            // changing structure bind values has no effect on original object
            std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
            std::clog << str << '\n';
        }

    }

    return 0; 
}

/*****
  END OF FILE
 ******/

