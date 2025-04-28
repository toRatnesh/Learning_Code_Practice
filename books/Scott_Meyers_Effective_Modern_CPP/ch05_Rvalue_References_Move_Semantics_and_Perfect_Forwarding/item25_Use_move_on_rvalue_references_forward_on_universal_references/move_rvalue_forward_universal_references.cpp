/*****

References

    Effective Modern C++ | Scott Meyers
	https://en.cppreference.com/w/cpp/language/reference
	https://en.cppreference.com/w/cpp/language/reference#Rvalue_references

	https://en.cppreference.com/w/cpp/utility/move
	https://en.cppreference.com/w/cpp/utility/forward


Item 25: Use std::move on rvalue references, std::forward on universal references

	Rvalue references bind only to objects that are candidates for moving
	To pass such objects to other functions in a way that permits those functions to take advantage of the object’s rvalueness
	The way to do that is to cast parameters bound to such objects to rvalues, std::move does this

	Universal references should be cast to rvalues only if they were initialized with rvalues, std::forward does this

	In short, 
	rvalue references should be unconditionally cast to rvalues (via std::move)
	universal references should be conditionally cast to rvalues (via std::forward)

	std::forward can also be used on rvalue references, but the source code is wordy, error-prone, and unidiomatic, 
	so you should avoid using std::forward with rvalue references

	worse is the idea of using std::move with universal references, because that can have the effect of unexpectedly modifying lvalues

Overloading on universal reference
	replacing a template taking a universal reference with a pair of functions overloaded on 
	lvalue references and rvalue references is likely to incur a runtime cost in some cases.
	
	The most serious problem with overloading on lvalues and rvalues, however, 
	isn’t the volume or idiomaticity of the source code, nor is it the code’s runtime performance. 
	It’s the poor scalability of the design.
	
	for functions taking more parameters, each of which could be an lvalue or an rvalue, 
	the number of overloads grows geometrically: n parameters necessitates (2^n) overloads
	
	For functions taking unlimited number of parameters, overloading on lvalues and rvalues is not an option: 
	universal references are the only way to go, For exmaple std::make_shared and std::make_unique

move and forward for return value	
	If you’re in a function that returns by value, and you’re returning an object bound to an rvalue reference or a universal reference, 
	you’ll want to apply std::move or std::forward when you return the reference.
	
return value optimization (RVO)
	“copying” version of a function can avoid the need to copy the local variable 
	by constructing it in the memory alloted for the function’s return value

	do not unnecessarily use move on such variable

named return value optimization (NRVO)	
	Some people draw a distinction between application of the RVO to named and unnamed (i.e., temporary) local objects, 
	limiting the term RVO to unnamed objects and calling its application to named objects the named return value optimization (NRVO).
	
	
	Widget makeWidget() {
		Widget w;
		…
		return w;
	}
	compilers must either elide the copying of w or they must treat the function as if it were written like this:
	Widget makeWidget() {
		Widget w;
		…
		return std::move(w);
	}

	
	Widget makeWidget(Widget w) {		// by-value parameter of same type as function's return 
		…
		return w;
	}
	compilers must treat it as if it had been written this way:
	Widget makeWidget(Widget w) {
		…
		return std::move(w); // treat w as rvalue
	}
	
	
Summary
	•	Apply std::move to rvalue references and std::forward to universal references the last time each is used.
	•	Do the same thing for rvalue references and universal references being returned from functions that return by value.
	•	Never apply std::move or std::forward to local objects if they would otherwise be eligible for the return value optimization.

**********/

#include <iostream>
#include <memory>
#include <utility>

class St {
    int     val;
    public:
    ~St()   { std::puts("~St()"); }
    St()   { std::puts("St()"); }
    
    St(const St & other) : val(other.val) { 
        std::puts("St(const St & other)"); 
    }
    St & operator=(const St & other) { 
        std::puts("operator=(const St & other)"); 

        if(this != &other) {
            val = other.val;
        }
        return *this;
    }

    St(St && other) : val(std::move(other.val)) { 
        std::puts("St(St && other)"); 
    }
    St & operator=(St && other) { 
        std::puts("operator=(St && other)"); 

        if(this != &other) {
            val = std::move(other.val);
        }
        return *this;
    }    

};

class CorrectUseOfMove {
    St                      m_st;
    std::shared_ptr<St>     mp_st;

    public:
    ~CorrectUseOfMove() {
        std::puts("~CorrectUseOfMove()");
    }

    CorrectUseOfMove() 
    : m_st{St{}}, mp_st{std::make_shared<St>()}
    {   
        std::puts("CorrectUseOfMove()");
    }

    CorrectUseOfMove(const CorrectUseOfMove & other) 
    :   m_st(other.m_st), 
        mp_st(other.mp_st)
    {
        std::puts("CorrectUseOfMove(const CorrectUseOfMove & other)");
    }

    CorrectUseOfMove& operator=(const CorrectUseOfMove & other)
    {
        if(this != &other) {
            m_st    = other.m_st; 
            mp_st   = other.mp_st;
        }
        std::puts("operator=(const CorrectUseOfMove & other)");

        return *this;
    }

    CorrectUseOfMove(CorrectUseOfMove && other) 
    :   m_st(std::move(other.m_st)), 
        mp_st(std::move(other.mp_st)) 
    {
        std::puts("CorrectUseOfMove(CorrectUseOfMove && other)");
    }

    CorrectUseOfMove& operator=(CorrectUseOfMove && other)
    {
        if(this != &other) {
            m_st    = std::move(other.m_st); 
            mp_st   = std::move(other.mp_st);            
        }
        std::puts("operator=(CorrectUseOfMove && other)");

        return *this;
    }

    CorrectUseOfMove & doSomeOperation() {
        std::puts("doSomeOperation()");
        return *this;
    }
    
};

class IncorrectUseOfMove {
    St                      m_st;
    std::shared_ptr<St>     mp_st;

    public:
    ~IncorrectUseOfMove() {
        std::puts("~IncorrectUseOfMove()");
    }

    IncorrectUseOfMove() 
    : m_st{St{}}, mp_st{std::make_shared<St>()}
    {   
        std::puts("IncorrectUseOfMove()");
    }

    template<typename T>
    void setStUsingUniversalRef(T&& st) {
        std::puts("setUsingUniversalRef(T&& other)");

        // THIS IS BAD CODE BCOZ EVEN LVALUE REF WILL BE MOVED
        m_st    = std::move(st);
    }
};

class UsingUniversalRef {
    St                      m_st;
    std::shared_ptr<St>     mp_st;

    public:
    ~UsingUniversalRef() {
        std::puts("~UsingUniversalRef()");
    }

    UsingUniversalRef() 
    : m_st{St{}}, mp_st{std::make_shared<St>()}
    {   
        std::puts("UsingUniversalRef()");
    }

    template<typename T>
    void setSt(T&& st) {
        std::puts("setUsingUniversalRef(T&& other)");
        m_st    = std::forward<T>(st);
    }
};

class OverloadingOnLvalueAndRvalue {
    St                      m_st;
    std::shared_ptr<St>     mp_st;

    public:
    ~OverloadingOnLvalueAndRvalue() {
        std::puts("~OverloadingOnLvalueAndRvalue()");
    }

    OverloadingOnLvalueAndRvalue() 
    : m_st{St{}}, mp_st{std::make_shared<St>()}
    {   
        std::puts("OverloadingOnLvalueAndRvalue()");
    }

    void setSt(const St & st) {
        std::puts("setSt(const St & st)");
        m_st    = st;
    }

    void setSt(St && st) {
        std::puts("setSt(St && st)");
        m_st    = std::move(st);
    }
};

CorrectUseOfMove returnRvalueParmUsingMove(CorrectUseOfMove && cmv) {
    std::puts("returnRvalueParmUsingMove(CorrectUseOfMove && cmv)");
    cmv = cmv.doSomeOperation();
    return std::move(cmv);
}

CorrectUseOfMove returnRvalueParm(CorrectUseOfMove && cmv) {
    std::puts("returnRvalueParm(CorrectUseOfMove && cmv)");
    cmv = cmv.doSomeOperation();
    return cmv;
}

template<typename T>
T returnUinversalRefParmUsingForward(T && val) {
    std::puts("returnRvalueParmUsingMove(CorrectUseOfMove && cmv)");
    val = val.doSomeOperation();
    return std::forward<T>(val);
}

CorrectUseOfMove getValue() {
    CorrectUseOfMove cmv;

    // warning: moving a local object in a return statement prevents copy elision
    // return std::move(cmv);
    return cmv;
}

CorrectUseOfMove getValueUsingMove() {
    CorrectUseOfMove cmv;

    // warning: moving a local object in a return statement prevents copy elision
    return std::move(cmv);
}

int main() {

    {   std::puts("=== Correct use of move ===");
        {   std::puts("--- Using move for rvalue ---");
            CorrectUseOfMove cmf1;
            CorrectUseOfMove cmf2{std::move(cmf1)};
        } 
        {   std::puts("--- Using rvalue ---");
            CorrectUseOfMove cmf2(CorrectUseOfMove{});
        }
                        
    }       


    {   std::puts("\n=== Incorrect use of move ===");
        {   std::puts("--- Using move with lvalue ---");
            IncorrectUseOfMove icmf1;
            St st;
            icmf1.setStUsingUniversalRef(st);
        }

        {   std::puts("--- Using move with rvalue ---");
            IncorrectUseOfMove icmf1;
            icmf1.setStUsingUniversalRef(St{});
        }     
    }

    {   std::puts("\n=== Compare overloading on lvalue and rvalue with using universal ref ===");
        {   std::puts("--- Using lvalue with overload ---");
            St st;

            OverloadingOnLvalueAndRvalue olr;
            olr.setSt(st);
        }
        {   std::puts("--- Using lvalue with universal ref ---");
            St st;

            UsingUniversalRef ur;
            ur.setSt(st);
        }
        
        {   std::puts("--- Using rvalue with overload ---");
            St st;

            OverloadingOnLvalueAndRvalue olr;
            olr.setSt(std::move(st));
        }
        {   std::puts("--- Using rvalue with with universal ref ---");
            St st;

            UsingUniversalRef ur;
            ur.setSt(std::move(st));
        } 

        {   std::puts("--- Using rvalue with overload ---");

            OverloadingOnLvalueAndRvalue olr;
            olr.setSt(St{});
        }
        {   std::puts("--- Using rvalue with universal ref ---");

            UsingUniversalRef ur;
            ur.setSt(St{});
        }            
    }

    {   std::puts("\n=== Returning rvalue parm using move ===");
        CorrectUseOfMove ret = returnRvalueParmUsingMove(CorrectUseOfMove{});        
    }

    {   std::puts("\n=== Returning rvalue parm ===");
        CorrectUseOfMove ret = returnRvalueParm(CorrectUseOfMove{});        
    }

    {   std::puts("\n=== Return uinversal ref parm using forward ===");

        {   std::puts("--- Using lvalue ---");
            CorrectUseOfMove cmv;
            CorrectUseOfMove retval = returnUinversalRefParmUsingForward(cmv);
        }

        {   std::puts("--- Using rvalue ---");
            CorrectUseOfMove cmv;
            CorrectUseOfMove retval = returnUinversalRefParmUsingForward(std::move(cmv));
        }

        {   std::puts("--- Using rvalue ---");
            CorrectUseOfMove retval = returnUinversalRefParmUsingForward(CorrectUseOfMove{});
        }
    }

    {   std::puts("\n=== Using lvalue return ===");
        { CorrectUseOfMove retval = getValue(); }
    }


    {   std::puts("\n=== Using move for lvalue return ===");
        { CorrectUseOfMove retval = getValueUsingMove(); }
    }

    return 0;
}

/*****
    END OF FILE
**********/


