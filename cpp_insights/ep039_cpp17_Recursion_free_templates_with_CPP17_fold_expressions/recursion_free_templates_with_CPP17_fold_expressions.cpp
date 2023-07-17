/********
    This example demonstrates about how C++17 fold expression
    eliminates the need to write recursive template code.

    For more info visit
    episode https://www.youtube.com/watch?v=C3Kiv_FTv-g
    https://github.com/toRatnesh/Learning_Code_Practice/tree/main/books/Nicolai_M_Josuttis_CPP17_The_Complete_Guide/Part_2_Template_Features/Ch_11_Fold_Expressions

************/

#include <iostream>

template <typename T>
auto foldSumRec(T arg) {
    return arg;
}

template <typename T1, typename... Ts>
auto foldSumRec(T1 arg1, Ts... otherArgs) {
    return arg1 + foldSumRec(otherArgs...);
}

// post C++17
template <typename... T>
auto foldSum(T... args) {
    return (... + args);  // arg1 + arg2 + arg3 ...
}

int main() {
    std::cout << "=== Pre C++17 ===\n";
    std::cout << "foldSumRec(2): " << foldSumRec(2) << '\n';
    std::cout << "foldSumRec(2, 3, 5): " << foldSumRec(2, 3, 5) << '\n';

    std::cout << "\n=== Post C++17 ===\n";
    std::cout << "foldSum(2): " << foldSum(2) << '\n';
    std::cout << "foldSum(2, 3, 5): " << foldSum(2, 3, 5) << '\n';
        
}

/********
    END OF FILE
************/

