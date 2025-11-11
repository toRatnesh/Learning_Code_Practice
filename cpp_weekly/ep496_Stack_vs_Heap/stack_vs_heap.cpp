/*****

References
    episode https://www.youtube.com/watch?v=VAzfOxLNLl4
    https://github.com/toRatnesh/Learning/blob/main/CPP/18_Memory_Layout.rst

    This example demonstrates stack vs heap memory region of program

    start of heap address
    -
    -
    |   Heap (Limited by virtual memory)
    V

        Unused

    ^
    |   Stack (Limited)
    -
    -
    start of stack address

**********/

#include <iostream>

void printAddr(const int *ptr)
{
    std::cout << "Pointer to   " << ptr << '\n';
}

void printAddr(const int &val)
{
    std::cout << "Reference to " << &val << '\n';
}

int main()
{
    {
        std::cout << "=== using stack ===\n";

        int i = 1;
        int j = 2;
        int k = 3;
        printAddr(i);
        printAddr(j);
        printAddr(k);
    }

    {
        std::cout << "\n=== using heap ===\n";

        int *i = new int{1};
        int *j = new int{2};
        int *k = new int{3};
        printAddr(i);
        printAddr(j);
        printAddr(k);

        delete i;
        i = nullptr;
        delete j;
        j = nullptr;
        delete k;
        k = nullptr;
    }

    return 0;
}

/*****
    END OF FILE
**********/
