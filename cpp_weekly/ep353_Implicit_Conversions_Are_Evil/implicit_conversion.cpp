/***************

    This example demonstrates about disadvantages of implicit conversion
    and why it should be removed from the language.

    For all warning errors check episode in which it is compiled using customized compiler
    episode: https://www.youtube.com/watch?v=T97QJ0KBaBU&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=355

**************/

#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <string_view>

/*

    warning: loop variable 'item' of type 
    'const std::pair<std::string, std::string> &' 
    (aka 'const pair<basic_string<char>, basic_string<char>> &') 
    binds to a temporary constructed from type 
    'std::_Rb_tree_const_iterator<std::pair<const std::basic_string<char>, std::basic_string<char>>>::reference' 
    (aka 'const std::pair<const std::basic_string<char>, std::basic_string<char>> &') [-Wrange-loop-construct]

    note: use non-reference type 'std::pair<std::string, std::string>' 
    (aka 'pair<basic_string<char>, basic_string<char>>') 
    to make construction explicit or type
    'const std::pair<const std::basic_string<char>, std::basic_string<char>> &' 
    to prevent copying

    Unnecessary copy from const char to char

*/

void use_data(const std::map<std::string, std::string> &map) {
    for (const std::pair<std::string, std::string> & item : map) {
        std::clog << item.first << ' ' <<  item.second << '\n';
    }
}

const char *load_file(const std::filesystem::path &);

std::string_view process_file(std::string_view sv) {
    /* implicit conversion from string_view to filesystem path */
    std::string results(load_file(sv));

    return results.substr(10, 100);
}

void process_file() {
    /* implicit conversion from string to string_view */
    std::string some_path("/path/to/a/file"); 
    
    process_file(some_path);
}

std::size_t get_data_size();

void allocate_data() {
    /* implicit conversion from size_t to int */
    int size = get_data_size();
    
    /* implicit conversion from int to size_t (this is narrowing conversion and may result in loss of integer precision) */
    void *data = malloc(size);
}

void do_things(const std::shared_ptr<const int> &);
std::vector<std::shared_ptr<int>> get_data();

void use_data() {
    for (const auto &item : get_data()) {
        /* implicit conversio from shared_ptr<int> to shared_ptr<const int> creates new non-trivial object */
        do_things(item);
    }
}

struct Base {};
struct Derived : Base {};

void use(const Base);

void use_derived() {
  Derived d;

  /* implicit conversion from Derived to Base results in slicing */
  use(d);
}

int main() {

    return 0;
}

/*********
    END OF FILE
**********/



