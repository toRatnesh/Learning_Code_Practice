/************
References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

8.  Single-Argument static_assert
    Since C++17, the previously required message argument for static_assert() is now optional
    This means that the resulting diagnostic message is completely platform specific.

*************/

int main() {
    const int val = 5;
    static_assert(5 == val);

    return 0;
}

/***************
    END OF FILE
*****************/
