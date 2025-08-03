/*****

References

    episode https://www.youtube.com/watch?v=DU1SmsjUxWg
    User-defined literals:  https://en.cppreference.com/w/cpp/language/user_literal.html

**********/

#include <iostream>
#include <string>
#include <ratio>

using bytes = std::ratio<1, 1>;
using kb = std::ratio<1024, 1>;
using mb = std::ratio<1024 * 1024, 1>;
using gb = std::ratio<1024 * 1024 * 1024, 1>;

template<typename Ratio>
std::string ext{};

template<>
std::string ext<bytes> =  "_bytes";

template<>
std::string ext<kb> =  "_KB";

template<>
std::string ext<mb> =  "_MB";

template<>
std::string ext<gb> =  "_GB";

template<typename Ratio = bytes>
class my_file_size {

    std::size_t     m_value;
    std::size_t     m_file_size;

    public:
    my_file_size(const std::size_t fsize) : m_value{fsize}, m_file_size{(fsize * Ratio::num) / Ratio::den} {

    }

    std::size_t size() const noexcept {
        return m_file_size;
    }

    std::size_t value() const noexcept {
        return m_value;
    }

    std::string str() const {
        return std::to_string(m_value) + ext<Ratio>;
    }

};

using file_size_kb = my_file_size<kb>;
using file_size_mb = my_file_size<mb>;
using file_size_gb = my_file_size<gb>;

template<typename Ratio = bytes>
std::ostream & operator<<(std::ostream & os, const my_file_size<Ratio> & fsize) {
    os << fsize.value() << ext<Ratio>;
    return os;
}

file_size_kb operator""_KB(unsigned long long int val) {
    return file_size_kb{val};
}


file_size_mb operator""_MB(unsigned long long int val) {
    return file_size_mb{val};
}

file_size_gb operator""_GB(unsigned long long int val) {
    return file_size_gb{val};
}

int main() {

    {
        std::cout << "=== using custom file size ===\n";
        my_file_size fs(2);
        std::cout << fs << '\n';
        std::cout << fs.str() << '\n';
        std::cout << "File size: " << fs.size() << " bytes\n";
        std::cout << "File size: " << fs.value() << " bytes\n";
    } 

    {
        std::cout << "=== using custom file size literal for KB ===\n";

        std::cout << 2_KB << '\n';
        my_file_size fs = 2_KB;
        std::cout << fs.str() << '\n';
        std::cout << "File size: " << fs.size() << " bytes\n";
        std::cout << "File size: " << fs.value() << " KB\n";
    }    

    {
        std::cout << "=== using alias file size for KB ===\n";

        file_size_kb fs(2);
        std::cout << fs << '\n';
        std::cout << fs.str() << '\n';
        std::cout << "File size: " << fs.size() << " bytes\n";
        std::cout << "File size: " << fs.value() << " KB\n";
    }

    {
        std::cout << "=== using alias file size for MB ===\n";

        file_size_mb fs(2);
        std::cout << fs << '\n';
        std::cout << fs.str() << '\n';
        std::cout << "File size: " << fs.size() << " bytes\n";
        std::cout << "File size: " << fs.value() << " MB\n";
    }

    {
        std::cout << "=== using alias file size for GB ===\n";

        file_size_gb fs(2);
        std::cout << fs << '\n';
        std::cout << fs.str() << '\n';
        std::cout << "File size: " << fs.size() << " bytes\n";
        std::cout << "File size: " << fs.value() << " GB\n";
    }

    return 0;
}

/*****
    END OF FILE
**********/
