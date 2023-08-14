/*********

    This example is demonstrates use of lambda and this is for learing purpose only

    For more info visit
    episode https://www.youtube.com/watch?v=z5ndvveb2qM

**************/

#include <iostream>
#include <vector>

int main() {

    {
        std::cout << "=== non-variadic ===\n";

        auto flat_map = [data = std::vector<std::pair<int, int>>()]
            (const int in_key) mutable -> auto & {

            for( auto &[key, value] : data) {
                if(in_key == key) {
                    return value;
                }
            }

            return data.emplace_back(in_key, 0).second;
        };

        flat_map(1) = 11;
        flat_map(2) = 12;
        std::cout << "flat_map(1) " << flat_map(1) << " flat_map(2) " << flat_map(2) << '\n';
    }
    
    {
        std::cout << "=== variadic ===\n";

        auto flat_map = [data = std::vector<std::pair<int, int>>()]
            (auto && ... in_key) mutable -> auto & {

            if constexpr(1 == sizeof...(in_key)) {
                for( auto &[key, value] : data) {
                    if((... , in_key) == key) {
                        return value;
                    }
                }
                
                return data.emplace_back((... , in_key), 0).second;

            } else {
                return data;
            }
        };

        flat_map(1) = 31;
        flat_map(2) = 32;
        std::cout << "flat_map(1) " << flat_map(1) << " flat_map(2) " << flat_map(2) << '\n';

        for(const auto & [key, value] : flat_map()) {
            std::cout << key << ' ' << value << '\n';
        }
    }

}

/*********
	END OF FILE
**************/


