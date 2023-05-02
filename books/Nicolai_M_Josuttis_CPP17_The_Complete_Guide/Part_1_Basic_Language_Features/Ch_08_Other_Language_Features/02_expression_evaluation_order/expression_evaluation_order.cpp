/************
References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

2.  Defined Expression Evaluation Order
    Since C++17 some evaluation guarantees were refined to guaranteed evaluation order

    i. For
        e1[e2]
        e1.e2
        e1.*e2
        e1->*e2
        e1<<e2
        e1>>e2
        e1 is guaranteed to get evaluated before e2 now, so that the evaluation order is left to right

    ii. For assignment operators
        e2 = e1
        e2 += e1
        e2 *= e1
        . . .
        the right-hand side (e1) is guaranteed to get evaluated before the left-hand side (e2) now

    iii. For new expressions like
        new Type(e)
        the allocation is now guaranteed to be performed before the evaluation e, and 
        the initialization of the new value is guaranteed to happen before any usage of the allocated and initialized value.

    iv. For statement
        std::cout << ++i << ' ' << --i << '\n';
        output is now guaranteed to be 1 0 for any type of i that supports these operands

    v. However, the undefined order for most of the other operators still exists. For example:
        i = i++ + i; // still undefined behavior

    vi. Backward Incompatibilities
        void print10elems(const std::vector<int>& v) {
            for (int i=0; i<10; ++i) {
                std::cout << "value: " << v.at(i) << '\n';
            }
        }
        Before C++17 at() was allowed to be evaluated before "value " was written, so that for the wrong index the output was skipped at all
        Since C++17, "value: " is printed as output before at() is evaluated
        
*************/

#include <iostream>
#include <vector>
#include <cassert>

void printVectorOutofRange(const std::vector<int>& v) {
    for (int i=0; i<3; ++i) {
        std::clog << "value: " << v.at(i) << '\n';
    }
}

struct S {
    int * m_ptr;
};

int & getRef() {
    static int m = 0;
    std::clog << "m: " << m << '\n';
    return m;
}

int getVal() { return 5; }

int main() {
    std::vector<int> lv{1,2,3};
    printVectorOutofRange(lv);

    int val = 0;
    std::clog << "++val: " << ++val << ", --val: " << --val << '\n';

    getRef() = getVal();
    getRef();

    int * ptr = new int(getVal());
    std::clog << "*ptr: " << *ptr << '\n';

    S s;
    s.m_ptr = new int(getVal());
    std::clog << "*s.m_ptr: " << *s.m_ptr << '\n';

    delete ptr;
    delete s.m_ptr;

    return 0;
}

/***************
    END OF FILE
*****************/
