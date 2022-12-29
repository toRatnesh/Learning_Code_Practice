/*********

References
    C++17 - The Complete Guide | Nicolai M. Josuttis

11. Fold Expressions

	Since C++17, there is a feature to compute the result of using a binary operator over all the arguments of a parameter pack (with an optional initial value).
	
	Given a parameter pack args and an operator op, C++17 allows us to write
	• a unary left fold
	( ... op args ) expands to		((arg1 op arg2) op arg3) op . . .			// prefer this
	• a unary right fold
	( args op ... ) expands to		arg1 op (arg2 op . . . (argN-1 op argN))

	The parentheses around the return expression are part of the fold expression and can’t be omitted.
	The order of fold expression arguments can differ and matters (and might look a bit counter-intuitive)
	Because in almost all cases evaluation from left to right is the intention, usually, the left fold syntax with the parameter pack at the end should be preferred (unless this doesn’t work).

11.2 Using Fold Expressions
	Given a parameter pack args and an operator op, C++17 allows us to write
	• a unary left fold
	( ... op args ) expands to		((arg1 op arg2) op arg3) op . . .			// prefer this
	• a unary right fold
	( args op ... ) expands to		arg1 op (arg2 op . . . (argN-1 op argN))

	Because in almost all cases evaluation from left to right is the intention, usually, the left fold syntax with the parameter pack at the end should be preferred (unless this doesn’t work).


11.2.2 Supported Operators
	all binary operators for fold expressions except ., ->, and [].
	
Folded Function Calls
	Fold expression can also be used for the comma operator, combining multiple expressions into one statement.
	The use of left fold expressions is recommended when using them for multiple function calls.

Combining Hash Functions
	One example of using the comma operator is to combine hash values.

Folded Path Traversals
	a fold expression to traverse a path in a binary tree with operator ->*:

***************************/

#include <iostream>
#include <string>
#include <cstdint>
#include <set>

// Folded Function Calls
template<typename ... Bases>
class MultiBase : private Bases ... 
{
    public:
    void display() {
        std::clog << R"((..., Bases::display()))" << '\n';
        (..., Bases::display());
        /*
            due to the nature of the comma operator it doesn’t matter whether 
            we use the left or right fold operator. 
            The functions are always called from left to right
        */
        std::clog << R"((Bases::display(), ...))" << '\n';
        (Bases::display(), ...);
    }
};
struct A { 
    void display() { std::clog << "A::display()\n"; } 
};
struct B { 
    void display() { std::clog << "B::display()\n"; } 
};
struct C { 
    void display() { std::clog << "C::display()\n"; } 
};

// Combining Hash Functions
template<typename T>
void hashCombine (std::size_t& seed, const T& val) {
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

template<typename... Types>
std::size_t combinedHashValue (const Types&... args) {
    std::size_t seed = 0;   // initial seed
    (... , hashCombine(seed,args)); // chain of hashCombine() calls
    return seed;
}

struct Employee {
    std::string     first_name;
    std::string     last_name;
    uint8_t         age;
};

struct EmployeeHash {
    auto operator() (const Employee & emp) const {
        return combinedHashValue(emp.first_name, emp.last_name, emp.age);
    }
};

struct Node {
    int data;
    Node*  left;
    Node*  right;
    Node(int i = 0) : data{i}, left{nullptr}, right{nullptr} {}
};
auto left   = &Node::left;
auto right  = &Node::right;

// traverse tree, using fold expression:
template<typename T, typename... TP>
Node* traverse (T np, TP... paths) {
    return (np ->* ... ->* paths); // np ->* paths1 ->* paths2 ...
}

int main() {
    // Folded Function Calls
    MultiBase<A,B,C> mb;
    mb.display();

    // Combining Hash Functions
    const std::string astr = "sample string";
    auto hash_val = combinedHashValue(astr, 42, 2.5);
    std::clog << "hash_val : " << hash_val << '\n';

    std::set<Employee, EmployeeHash> emp_set;

    // Folded Path Traversals
    // fold expression to traverse a path in a binary tree with operator ->*
    Node* root = new Node{1};
    root->left = new Node{2};
    root->left->right = new Node{3};
    // traverse binary tree:
    Node* node = traverse(root, left, right);
    std::clog << "node->data " << node->data << '\n';

    delete root->left->right;
    delete root->left;
    delete root;

    return 0;
}

/******
    END OF FILE
********/


