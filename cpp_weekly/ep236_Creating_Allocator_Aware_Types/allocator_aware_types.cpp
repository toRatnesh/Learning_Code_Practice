/**************
  This example demonstrates about user defined allocator aware types.

  For more infi visit:
https://www.youtube.com/watch?v=2LAsqp7UrNs&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=237
 *************/

#include <fmt/format.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory_resource>
#include <vector>

template <typename ItrBegin, typename ItrEnd>
void print_line(int offset, ItrBegin begin, const ItrEnd end) {
    fmt::print("(dec) {:02x}:  {:3}\n", offset, fmt::join(begin, end, "  "));
    fmt::print("(hex) {:02x}:   {:02x}\n", offset,
               fmt::join(begin, end, "   "));

    fmt::print("(asc) {:02x}:", offset);
    std::for_each(begin, end, [](const auto c) {
        if (std::isgraph(c)) {
            fmt::print("   {} ", static_cast<char>(c));
        } else {
            fmt::print(" \\{:03o}", c);
        }
    });

    fmt::print("\n");
}

template <typename Buffer, typename Container>
void print_buffer(const std::string_view title, const Buffer &buffer,
                  const Container &container) {
    fmt::print("==============={:^10}==============\n", title);

    auto begin = buffer.begin();
    fmt::print("Buffer Address Start: {}\n",
               static_cast<const void *>(buffer.data()));
    for (const auto &elem : container) {
        fmt::print(" Item Address: {}\n", static_cast<const void *>(&elem));
    }
    for (std::size_t offset = 0; offset < buffer.size(); offset += 16) {
        print_line(offset, std::next(begin, offset),
                   std::next(begin, offset + 16));
    }

    fmt::print("\n");
}

// short strings, non PMR
void nested_string() {
    fmt::print("Size of `std::pmr::string`: {}\n", sizeof(std::pmr::string));

    std::array<std::uint8_t, 256> buffer{};
    std::pmr::monotonic_buffer_resource mem_resource(buffer.data(),
                                                     buffer.size());
    print_buffer("initial", buffer, "");
    std::pmr::vector<std::pmr::string> vec1(
        {"Hello World", "Hello World 2", "Hello world long string"},
        &mem_resource);
    print_buffer("2 short strings + 1 long string", buffer, vec1);
}

struct S {
    std::pmr::string str = "Hello long string";
    using allocator_type = std::pmr::polymorphic_allocator<>;

    ~S() = default;

    S() : S(allocator_type{}) {}

    explicit S(allocator_type alloc) 
        : str("Hello from PMR constructor", alloc) { }

    S(const S & other, allocator_type alloc = {}) 
        : str(other.str, alloc) { }

    S(S && other, allocator_type alloc) 
        : str(std::move(other.str), alloc) { }

    S(S &&)         = default;

    S& operator=(const S & rhs) = default;
    S& operator=(S && rhs)      = default;

    allocator_type get_allocator() const {
        return str.get_allocator();
    }

};

void my_aa_t() {
    std::array<std::uint8_t, 256> buffer{};
    fmt::print("Size of object: {}\n", sizeof(S));

    std::pmr::monotonic_buffer_resource mem_resource(buffer.data(), buffer.size());
    fmt::print("mem_resource address: {}\n", static_cast<const void *>(&mem_resource));
    print_buffer("initial", buffer, "");
    std::pmr::vector<S> vec1(&mem_resource);
    vec1.push_back(S());
    print_buffer("push_back", buffer, vec1);
    vec1.emplace_back();
    print_buffer("emplace_back", buffer, vec1);

    return ;
}

int main() {
    //nested_string();
    my_aa_t();

    // * know how and if your memory is growing
    // * choose the correct allocator for your use case
    // * make sure you properly nest your allocator aware types
    // * Understand which std types are allocator aware

    /*******
      When building custom types that support allocators
      make sure to initialize all sub object correctly (know your defaults)
      notify the AA containers that we support allocators
     **************/

    return 0;
}

/****
  END OF FILE
 ***/
