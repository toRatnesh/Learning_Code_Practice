#ifndef ADDITION_HPP
#define ADDITION_HPP

template<typename T>
T myadd(T m, T n) {
    return (m+n);
}

/****
    extern template saves on build time in each cpp file of our large project
    (assuming 'myadd' function is expensive to compile)
***/
extern template
int myadd<int>(int m, int n);

#endif
