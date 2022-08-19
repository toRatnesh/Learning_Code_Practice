/********
    Reference:  C++17 - The Complete Guide | Nicolai M. Josuttis

    Structured Bindings
    Structured bindings allow you to initialize multiple entities by the elements or members of an object.

    1.2 Where Structured Bindings can be Used
    Structured bindings can be used for structures with public data members, raw C-style arrays, and .tuple-like objects..
    
    In all cases 
    The number of elements or data members has to fit the number of names in the declaration of the structured binding. 
    You can.t skip name and you can.t use a name twice. 
    However, you could use a very short name such as '_'.

    Nested or non-flat decomposition is not supported.

    1.2.1 Structures and Classes
        You can bind each public non-static data member to exactly one name.
        There is only limited usage of inheritance possible. All non-static data members must be members of the same class definition.

    1.2.2 Raw Arrays
        Structure binding is possible as long as arr has a known size.
        For an array passed as argument, this is not possible because it decays to the corresponding pointer type.
        Note that C++ allows us to return arrays with size by reference, so that this feature also applies to functions returning an array provided its size is part of the return type.

    1.2.3 std::pair, std::tuple, and std::array
        Assigning new Values to Structured Bindings for pair and tuple
        After declaring a structured binding, you usually can.t modify all bindings together because structured bindings can only be declared but not used together. However, you can use std::tie() if the value assigned can be assigned to a std::pair<> or a std::tuple<>.
        
**********/

#include <iostream>
#include <string>
#include <type_traits>
#include <array>
#include <tuple>

class WithPrivateMember {
    // struct/class with private member can not be decomposed for structure binding
    private:
        int private_val = 10;
    public:
        int m = 11;
};

class WithStaticMember {
    public:
    int m1 = 7;
    int m2 = 8;
    // static member is not consider for decompose
    inline static int static_val = 9;
};

struct Base {
    int m1 = 7;
    int m2 = 8;
};

struct privateDerived : private Base { }; // can not decompose because Base is private
struct publicDerivedWithNoMember : public Base { };
struct publicDerivedWithMember : public Base { int m3 = 9; };  // can not decompose because new member added

struct NestedStruct {
    // only m will decompose
    int m = 7;
    struct InnerStruct {
        int n = 8;
        int o = 9;
    };
};

// array parameter cannot be decomposed because it decays to pointer type
void arrayAsArray(int arr[5]) {
    //auto [v1, v2] = arr;    // CE: error: cannot decompose non-array non-class type 'int*'
    return ;
}

auto getArray() -> int (&)[5] {
    static int arr[] = {1,2,3,4,5};
    return arr;
}

int main() {
    
    // 1. Struct/class

    WithPrivateMember with_private_mem;
    //auto [pv, m] = with_private_mem;  // CE: error: cannot decompose inaccessible member 'WithPrivateMember::private_val' of 'WithPrivateMember'
    //auto [m] = with_private_mem;      // CE: error: cannot decompose inaccessible member 'WithPrivateMember::private_val' of 'WithPrivateMember'

    WithStaticMember with_static_mem;
    //auto [v1, v2, sv] = with_static_mem;     // CE: error: 3 names provided for structured binding
    //auto [v, v] = with_static_mem;    // CE: error: redeclaration of 'auto v'
    auto [v1, v2] = with_static_mem;

    privateDerived private_derived_obj;
    //auto [m11, n11] = private_derived_obj;        // CE: error: 'Base' is an inaccessible base of 'privateDerived'
    
    publicDerivedWithNoMember public_derived_obj_with_no_member;
    auto [m21, n21] = public_derived_obj_with_no_member;
    
    publicDerivedWithMember public_derived_obj_with_member;
    //auto [m31, m32, m33] = public_derived_obj_with_member;   // CE: error: cannot decompose class type 'publicDerivedWithMember': both it and its base class 'Base' have non-static data members

    NestedStruct nested_struct;
    //auto [ns1, ns2, ns3] = nested_struct;   // CE: error: 3 names provided for structured binding
    auto [ns] = nested_struct;


    // 2. Raw array

    int arr [] = {11, 12, 13, 14, 15};
    auto [a1, a2, a3, a4, a5] = arr;
    auto [a11, a12, a13, a14, a15] = getArray();

    // 3. std::pair, std::tuple, and std::array
    std::tuple<char, int, std::string> tuple1{'a', 2, "strcuture binding"};
    auto [c, i, s] = tuple1;
    std::tie(c, i, s) = tuple1;

    std::array<int, 4> arr2 = {1,2,3,4};
    auto [a21, a22, a23, a24] = arr2;
    //std::tie(a21, a22, a23, a24) = arr2;    // CE: error: no match for 'operator=' (operand types are 'std::tuple<int&, int&, int&, int&>' and 'std::array<int, 4>')

    return 0;
}

/*****
	END OF FILE
******/
