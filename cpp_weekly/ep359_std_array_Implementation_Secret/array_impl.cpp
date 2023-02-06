/**********

    This example demonstrates about a possible implementation of std::array

    For more info visit:
    https://www.youtube.com/watch?v=uLbv2u536G0

***************/

#include <iostream>
#include <array>

namespace nonstd {
    template<typename T, std::size_t AR_SIZE>
    struct array {
        T m_vals[AR_SIZE];

        constexpr       T& operator[](std::size_t idx)          { return m_vals[idx]; }
        constexpr const T& operator[](std::size_t idx) const    { return m_vals[idx]; }

        constexpr T* begin()    { return m_vals; }
        constexpr T* end()      { return m_vals + AR_SIZE; }

        constexpr const T* begin()  const   { return m_vals; }
        constexpr const T* end()    const   { return m_vals + AR_SIZE; }

        constexpr const T* cbegin()  const   { return m_vals; }
        constexpr const T* cend()    const   { return m_vals + AR_SIZE; }

        constexpr       T& front()          { return *m_vals; }
        constexpr const T& front()  const   { return *m_vals; }
    };

    template<std::size_t I, typename T, std::size_t AR_SIZE>
    constexpr const T & get(const nonstd::array<T, AR_SIZE> & arr) {
        static_assert(I < AR_SIZE);
        return arr[I];
    }
}

// for structure binding
template<typename T, std::size_t AR_SIZE>
struct std::tuple_size<nonstd::array<T, AR_SIZE>> : 
    std::integral_constant<std::size_t, AR_SIZE> { };

template<std::size_t I, typename T, std::size_t AR_SIZE>
struct std::tuple_element<I, nonstd::array<T, AR_SIZE>> {
    using type = T;
};



int main() {
    std::array<int, 5>      sarr{11,12,13,14,15};
    nonstd::array<int, 5>   nsarr{21,22,23,24,25};

    {
        auto val1 = sarr[1];
        auto val2 = nsarr[1];
        std::clog << "sarr[1] " << val1 << '\n';
        std::clog << "nsarr[1] " << val2 << '\n';
    }

    {
        std::clog << "sarr: ";
        for(auto elems: sarr) {
            std::clog << elems << ", ";
        }
        std::clog << '\n';
        std::clog << "nsarr: ";
        for(auto elems: nsarr) {
            std::clog << elems << ", ";
        }
        std::clog << '\n';
    }

    {
        // direct member access is undefined behavior because member identifier is implementation dependent and it may change
        std::clog << "sarr.m_vals[0] " << sarr._M_elems[0] << '\n';
        std::clog << "nsarr.m_vals[0] " << nsarr.m_vals[0] << '\n';
    }

    {
        std::clog << "sarr.front() " << sarr.front() << '\n';
        std::clog << "nsarr.front() " << nsarr.front() << '\n';
    }

    {
	std::clog << "structure binding \n";
        auto [m1, m2, m3, m4, m5] = sarr;
        const auto [n1, n2, n3, n4, n5] = nsarr;

        std::clog << m1+m2+m3+m4+m5 << '\n';
        std::clog << n1+n2+n3+n4+n5 << '\n';
    }

    return 0;
}

/****
    END OF FILE
*********/

