/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/container/unordered_map/contains.html

Chapter 10 | New STL elements

10.6 contains for all associative containers

    C++20 added contains method for all associative containers
    contains:   Checks if there is an element with key equivalent to key in the container

    For std::map and std::set
        both find and count have logarithmic complexity in size of the container

    For std::multimap and std::multiset
        this is different
        count of one of the multi containers has logarithmic complexity plus a linear one in the number of elements found    
    

**********/

#include <iostream>
#include <unordered_map>

int main() {

    const std::unordered_map<std::string, std::string> lmap{
        {"key-1", "val-1"},
        {"key-2", "val-2"},
        {"key-3", "val-3"},
        {"key-4", "val-4"},
        {"key-5", "val-5"},
        {"key-6", "val-6"},
    };
    
    const std::string l_key{"key-2"};

    if(lmap.contains(l_key)) {
        std::cout << l_key << " found in map\n";
    }

    // pre C++20

    if(lmap.find(l_key) != lmap.end()) {
        std::cout << l_key << " found in map\n";
    }

	return 0;
}

/*****
    END OF FILE
**********/

