/*****

References
    Effective Modern C++ | Scott Meyers


Item 1: Understand template type deduction

Consider a function template
    template<typename T>
    void f(ParamType param);

A call to f
    f(expr); // call f with some expression
    
During compilation, compilers use expr to deduce two types: one for T and one for ParamType.
These types are frequently different, because ParamType often contains adornments, 
e.g., const or reference qualifiers.

The type deduced for T is dependent not just on the type of expr, but also on the form of ParamType.
There are three cases:
1. ParamType is a pointer or reference type (not a universal reference).
2. ParamType is a universal reference.
3. ParamType is neither a pointer nor a reference.

1. ParamType is a pointer or reference type (not a universal reference).

    i. If expr’s type is a reference, ignore the reference part.
    ii. Then pattern-match expr’s type against ParamType to determine T.

    Consider template function:
    template<typename T>
    void parmIsRef(T & param) { }

    Variables:
    int val = 10;
    const int cval = 15;
    int & rval = val;
    const int & crval = 17;
    int && urval = 5;
    const int && curval = 5;

    the deduced types for param and T in various calls are as follows:
    ---------------------------------------------------------------------------
    Call                    T's type                    Parm's Type
    ---------------------------------------------------------------------------
    parmIsRef(val);           int                         int &
    parmIsRef(cval);          const int                   const int &
    parmIsRef(rval);          int                         int &
    parmIsRef(crval);         const int                   const int &
    parmIsRef(urval);         int                         int &
    parmIsRef(curval);        int                         const int &
    ---------------------------------------------------------------------------    

    If we change the type of fun’s parameter from T& to const T&, things change a little,
    because we’re now assuming that param is a reference-to-const, 
    there’s no longer a need for const to be deduced as part of T:

    template<typename T>
    void parmIsRef(const T & param) { }
    the deduced types for param and T in various calls are as follows:
    ---------------------------------------------------------------------------
    Call                    T's type                    Parm's Type
    ---------------------------------------------------------------------------
    parmIsRef(val);           int                         const int &
    parmIsRef(cval);          int                         const int &
    parmIsRef(rval);          int                         const int &
    parmIsRef(crval);         int                         const int &
    parmIsRef(urval);         int                         const int &
    parmIsRef(curval);        int                         const int &
    ---------------------------------------------------------------------------    
    
    If param were a pointer (or a pointer to const) instead of a reference, 
    things would work essentially the same way


2. ParamType is a universal reference.

    i. If expr is an lvalue, both T and ParamType are deduced to be lvalue references.
        That’s doubly unusual. 
        First, it’s the only situation in template type deduction where T is deduced to be a reference. 
        Second, although ParamType is declared using the syntax for an rvalue reference, 
        its deduced type is an lvalue reference.      
    ii. If expr is an rvalue, the “normal” (i.e., Case 1) rules apply.

    The type deduction rules for universal reference parameters are different 
    from those for parameters that are lvalue references or rvalue references.

    int getVal() { return 42; }

    template<typename T>
    void parmIsUniversalRef(T && parm) { }

    ---------------------------------------------------------------------------
    Call                            T's type            Parm's Type
    ---------------------------------------------------------------------------
    parmIsUniversalRef(val);        int &               int &
    parmIsUniversalRef(cval);       const int &         const int &
    parmIsUniversalRef(rval);       int &               int &
    parmIsUniversalRef(crval);      const int &         const int &
    parmIsUniversalRef(urval);      int &               int &
    parmIsUniversalRef(curval);     const int &         const int &
    parmIsUniversalRef(27);         int                 int &&
    parmIsUniversalRef(getVal());   int                 int &&
    ---------------------------------------------------------------------------  


3. ParamType is neither a pointer nor a reference.

    i. As before, if expr’s type is a reference, ignore the reference part.
    ii. If, after ignoring expr’s reference-ness, expr is const, ignore that, too. 
        If it’s volatile, also ignore that.

    template<typename T>
    void parmIsPassByValue(T parm) { }

    ---------------------------------------------------------------------------
    Call                            T's type            Parm's Type
    ---------------------------------------------------------------------------
    parmIsPassByValue(val);        int					int
    parmIsPassByValue(cval);       int					int
    parmIsPassByValue(rval);       int					int
    parmIsPassByValue(crval);      int					int
    parmIsPassByValue(urval);      int					int
    parmIsPassByValue(curval);     int					int
    parmIsPassByValue(27);         int					int
    parmIsPassByValue(getVal());   int					int
    
    parmIsPassByValue(ptr);         int *               int *
    ---------------------------------------------------------------------------  


Array Arguments
    in many contexts, an array decays into a pointer to its first element
    const char carr[] = "This a char array";
    const char * ptr = carr;    // array decays to pinter

    if an array is passed to a template taking a by-value parameter
    parmIsPassByValue(carr);        // const char *
    
    Because array parameter declarations are treated as if they were pointer parameters,
    the type of array is deduced to be a pointer type.


    if an array is passed to a template taking a by-ref parameter    
    parmIsRef(carr);                // const char (&)[18]

    Although functions can’t declare parameters that are truly arrays, 
    they can declare parameters that are references to arrays

    the type deduced for T is the actual type of the array, 
    That type includes the size of the array

Function Arguments
    Function types can decay into function pointers

    everything we’ve discussed regarding type deduction for arrays applies to 
    type deduction for functions and their decay into function pointers

    double getSum(int ival, double dval) {
        return ival + dval;
    }

    parmIsPassByValue(getSum);  // double (*parm)(int, double)
    parmIsRef(getSum);          // double (&parm)(int, double)

    This rarely makes any difference in practice


NOTE:
    To check deduced type you may 
    compile this code using https://cppinsights.io/ and check  deduced type

**********/

#include <iostream>

double getSum(int ival, double dval) {
    return ival + dval;
}

int getVal() { return 42; }

template<typename T>
void parmIsRef(T & param) { }

template<typename T>
void parmIsUniversalRef(T && param) { }

template<typename T>
void parmIsPassByValue(T parm) { }

int main() {

    int val = 10;
    const int cval = 15;
    int & rval = val;
    const int & crval = 17;
    int && urval = 5;
    const int && curval = 5;

    {
        std::puts("1. ParamType is a pointer or reference type (not a universal reference)");
        
        parmIsRef(val);        // int &
        parmIsRef(cval);       // const int &
        parmIsRef(rval);       // int &
        parmIsRef(crval);      // const int &
        parmIsRef(urval);      // int &
        parmIsRef(curval);     // const int &
        //parmIsRef(27);		// CE error: no matching function for call to 'parmIsRef'
        //parmIsRef(getVal());	// CE error: no matching function for call to 'parmIsRef'  
    }

    {
        std::puts("2. ParamType is a universal reference.");

        parmIsUniversalRef(val);		// int &
        parmIsUniversalRef(cval);		// const int &
        parmIsUniversalRef(rval);		// int &
        parmIsUniversalRef(crval);		// const int &
        parmIsUniversalRef(urval);		// int &
        parmIsUniversalRef(curval);		// const int &
        parmIsUniversalRef(27);			// int &&
        parmIsUniversalRef(getVal());	// int &&        
    }

    {
        std::puts("3. ParamType is neither a pointer nor a reference.");

        int * ptr = &val;

        parmIsPassByValue(val);			// int
        parmIsPassByValue(cval);        // int
        parmIsPassByValue(rval);        // int
        parmIsPassByValue(crval);		// int
        parmIsPassByValue(urval);		// int
        parmIsPassByValue(curval);		// int
        parmIsPassByValue(27);			// int
        parmIsPassByValue(getVal());	// int

        parmIsPassByValue(ptr);         // int *
    }

    {
        std::puts("Array Arguments");
        
        const char carr[] = "This a char array";
        parmIsPassByValue(carr);
        parmIsRef(carr);           
    } 

    {
        std::puts("Function Arguments");
        parmIsPassByValue(getSum);  // double (*parm)(int, double)
        parmIsRef(getSum);          // double (&parm)(int, double)
    }
    return 0;
}

/*****
    END OF FILE
**********/