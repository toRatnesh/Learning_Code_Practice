/*****

References:
    episode     https://www.youtube.com/watch?v=WROn9H5FLoY
    https://clang.llvm.org/extra/clang-tidy/checks/modernize/use-designated-initializers.html

    This episode explains about clang-tidy check for C++20 designated initializer

**********/

#include <iostream>
#include <cassert>

struct Point3d {
    int x;
    int y;
    int z;
};


void usePoint(const Point3d & point) {

}

int main()
{
    usePoint(Point3d{.x=4, .y=5, .z=6});

    return 0;
}

/*****
    END OF FILE
**********/

