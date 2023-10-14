/*****

References
    episode     https://www.youtube.com/watch?v=hW4NJF4RLnE
    Benchmark   https://quick-bench.com/q/I9Wmi2dnRwmCeNo-2aLvP6aUTUw

In case where available for a container
    emplace         insert a new object and construct it in place at the automatically chosen correct location
                    (for other types, construct an object in place)
                    
    emplace_back    insert a new object at the end of a container, and construct it in place
    emplace_front   insert a new object at at the front of a container, and construct it in place
             
    try_emplace     try to insert a new object in place
    emplace_hint    Tell the container where the element in the container should be inesrted
    try_emplace with hint

**********/

#include <iostream>
#include <list>
#include <map>

template<typename T>
void display_container(const T & cont) {
    for(const auto & elem : cont) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

int main() {
    
    std::cout << "=== Using list for emplace, emplace_front and emplace_back ====\n";
    
    std::list alist{1,2,3};
    std::cout << "List: ";
    display_container(alist);
    
    auto ret = alist.emplace(alist.begin(), 0);
    std::cout << "List after, ret = alist.emplace(alist.begin(), 0)\n";
    std::cout << "*ret " << *ret << '\n';
    display_container(alist);   

    ret = alist.emplace(alist.end(), 4);
    std::cout << "List after, ret = alist.emplace(alist.end(), 4)\n";
    std::cout << "*ret " << *ret << '\n';
    display_container(alist);

    ret = alist.emplace(++alist.begin(), 7);
    std::cout << "List after, ret = alist.emplace(++alist.begin(), 7)\n";
    std::cout << "*ret " << *ret << '\n';
    display_container(alist); 

    auto ret_ref = alist.emplace_front(1);
    std::cout << "List after, ret_ref = alist.emplace_front(1)\n";
    std::cout << "ret_ref: " << ret_ref << '\n';
    display_container(alist); 

    ret_ref = alist.emplace_back(9);
    std::cout << "List after, ret_ref = alist.emplace_back(9)\n";
    std::cout << "ret_ref: " << ret_ref << '\n';
    display_container(alist); 


    std::cout << "\n=== Using map for emplace, emplace_hint and try_emplace ====\n";
    std::map<std::string, std::string>  amap{
        {"key-1", "value-1"},
        {"key-2", "value-2"},
        {"key-3", "value-3"}
    };

    {
        auto [pos, done] = amap.emplace("key-4", "value-4");
        if(done) {
            std::cout << "key: " << pos->first << ", value: " << pos->second << '\n';
        } else {
            std::cout << R"(amap.emplace("key-4", "value-4") failed)" << '\n';
        }
    }

    {
        auto [pos, done] = amap.emplace("key-4", "value-4");
        if(done) {
            std::cout << "key: " << pos->first << ", value: " << pos->second << '\n';
        } else {
            std::cout << R"(amap.emplace("key-4", "value-4") failed)" << '\n';
        }
    }

    {
        auto it = amap.emplace_hint(++amap.begin(), "key-5", "value-5");
        std::cout << "key: " << it->first << ", value: " << it->second << '\n';
    }

    {
        auto it = amap.emplace_hint(++amap.begin(), "key-5", "value-5");
        std::cout << "key: " << it->first << ", value: " << it->second << '\n';
    }

    {
        auto [pos, done] = amap.try_emplace("key-6", "value-6");
        if(done) {
            std::cout << "key: " << pos->first << ", value: " << pos->second << '\n';
        } else {
            std::cout << R"(amap.try_emplace("key-6", "value-6") failed)" << '\n';
        }
    }

    {
        auto [pos, done] = amap.try_emplace("key-6", "value-6");
        if(done) {
            std::cout << "key: " << pos->first << ", value: " << pos->second << '\n';
        } else {
            std::cout << R"(amap.try_emplace("key-6", "value-6") failed)" << '\n';
        }
    }

    {
        auto it = amap.try_emplace(++amap.begin(), "key-7", "value-7");
        std::cout << "key: " << it->first << ", value: " << it->second << '\n';
    }

    {
        auto it = amap.try_emplace(++amap.begin(), "key-7", "value-7");
        std::cout << "key: " << it->first << ", value: " << it->second << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/


