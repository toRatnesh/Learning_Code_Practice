/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis

Chapter 25 Container Extensions

25.2 Node Handles
	introducing the ability to splice node out of an associative or unordered container
	this allow us to:
	• Modify keys or (unordered) maps or values or (unordered) sets,
	• Use move semantics in (unordered) sets and maps, and
	• Move elements between (unordered) sets and maps.
	
	Note that no memory (de)allocation is used and that pointers and references to the element remain valid. 
	However, using the pointers and references while the element is held in the node handle results in undefined behavior.
	
	You can also use node handles to move elements from a container to another.
	The containers can even differ:
	• one supports duplicates while another doesn’t
	• comparison functions and hash functions might differ
	
*************/

#include <iostream>
#include <string>
#include <map>

auto  displayMap = [](const auto & coll,
                    const std::string msg = "map elements === \n") {
    std::cout << msg;
    for(const auto & [key, val] : coll) {
        std::cout << key << ' ' << val << '\n';
    }
};

int main() {
    std::cout << "=== Node Handles ===\n";
    
    std::map<std::string, std::string>  l_map{
        {"key-1", "value-1"},
        {"key-2", "value-2"},
        {"key-3", "value-3"},
        {"key-4", "value-4"},
        {"key-5", "value-5"}
    };
    displayMap(l_map);

    auto node_h = l_map.extract(++l_map.begin());

    displayMap(l_map, "map elements after extraction ===\n");

    node_h.key() = "updated key";
    node_h.mapped() = "updated value";
    l_map.insert(std::move(node_h));
    
    displayMap(l_map, "map elements after insertion with updated key ===\n");

    std::map<std::string, std::string>  l_dmap{{"k-1", "v-1"}};
    displayMap(l_dmap);
    l_dmap.insert(l_map.extract(l_map.begin()));
    auto [pos, done, node] = l_dmap.insert(l_map.extract("key-4"));
    if (!done) {
        std::cout << "Node insertion failed:"
        << "Node key " << node.key()
        << "Node value " << node.mapped()
        << ", but key exists with value " << pos->second << "\n";
    }    
    displayMap(l_dmap, "map elements after insertion ===\n");
    displayMap(l_map, "map elements after extraction ===\n");

    return 0;
}

/**********
    END OF FILE
*************/


