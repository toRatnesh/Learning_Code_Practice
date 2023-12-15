/*****

Reference
    CppCon 2022 - Lightning Talk: Cute Approach for Polymorphism in C++ - Liad Aben Sour Asayag
    https://www.youtube.com/watch?v=Y0B5AkvBL2w

Task
    Different handlers to handle elements of different type collections
    which handler to use is known at runtime

1. Inheritance

    Many virtual calls to small virtual methods could lead to poor performance
    Each handler could be written in its own source file, main only needs to know about Handler base
        -> Good Encapsulation
        -> Faster compilation

2. Concept and Varient
    Have some concept handler
    
    only one variant visit per vector of many elements
    main source code needs to know all the handlers at compile tim
        -> No encapsulation
        -> slower compilation

3. Virtual on aggregate
    only one virtual call per vector of many elements
    main source code only needs to know about handler base class 
        -> Good encapsulation
        -> Fast compilation

    Code not elegant

    Improved version
        separate the non virtual methods for handling single element in different class
        
        Derived handler base class with template parameter
        instantiate above template class with class handling single element

**********/

#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <variant>
#include <algorithm>
#include <span>

// 1. inheritance

#ifdef USE_INHERITANCE

class Handler {
    public:
    virtual ~Handler() = default;
    virtual void handle(int data) = 0;
};

class ListHandler : public Handler {
    public:
    virtual ~ListHandler() = default;
    virtual void handle(int data) override {
        std::cout << "ListHandler::handle " << data << '\n';
    };
};

class VectorHandler : public Handler {
    public:
    virtual ~VectorHandler() = default;
    virtual void handle(int data) override {
        std::cout << "VectorHandler::handle " << data << '\n';
    };
};

std::unique_ptr<Handler> choose_handler(bool vec_handle) {
    if(vec_handle) {
        return std::make_unique<VectorHandler>();
    } else {
        return std::make_unique<ListHandler>();
    }
}

void use_inheritance() {
    std::cout << "=== using inheritance ===\n";
    {
        std::vector container{1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::unique_ptr<Handler> handler = choose_handler(true);
        for(auto elem : container) {
            handler->handle(elem);
        }
    }
    std::cout << '\n';
    {
        std::list   container{1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::unique_ptr<Handler> handler = choose_handler(false);
        for(auto elem : container) {
            handler->handle(elem);
        }        
    }    
}
#endif

// 2. using concept and variant

#ifdef USE_CONCEPT

template<typename T, typename U>
concept has_handle = requires(T t, U val) { t.handle(val); };

class ListHandler {
    public:
    void handle(int data) const {
        std::cout << "ListHandler::handle " << data << '\n';
    };
};

class VectorHandler {
    public:
    void handle(int data) const {
        std::cout << "VectorHandler::handle " << data << '\n';
    };
};

using handler_t = std::variant<ListHandler, VectorHandler>;

handler_t choose_handler(bool vec_handle) {
    if(vec_handle) {
        return VectorHandler{};
    } else {
        return ListHandler{};
    }
}

void use_concept() {
    std::cout << "=== using concept ===\n";
    {
        std::vector container{1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto handler = choose_handler(true);
        std::visit([&container](const auto & h){
            for(auto elem : container) {
                h.handle(elem);
            }
        }, handler);
    }
    std::cout << '\n';
    {
        std::list   container{1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto handler = choose_handler(false);
        std::visit([&container](const auto & h){
            for(auto elem : container) {
                h.handle(elem);
            }
        }, handler);       
    }    
}
    
#endif

#ifdef VIRTUAL_ON_AGGREGATE

class Handler {
    public:
    virtual ~Handler() = default;
    virtual void handle(std::span<int> coll) = 0;
};

class ListHandler : public Handler {
    public:
    virtual ~ListHandler() = default;
    virtual void handle(std::span<int> coll) override {
        for(auto elem: coll) {
            handle(elem);
        }
    }
    void handle(int data) {
        std::cout << "ListHandler::handle " << data << '\n';
    };
};

class VectorHandler : public Handler {
    public:
    virtual ~VectorHandler() = default;
    virtual void handle(std::span<int> coll) override {
        for(auto elem: coll) {
            handle(elem);
        }
    }    
    void handle(int data) {
        std::cout << "VectorHandler::handle " << data << '\n';
    };
};

std::unique_ptr<Handler> choose_handler(bool vec_handle) {
    if(vec_handle) {
        return std::make_unique<VectorHandler>();
    } else {
        return std::make_unique<ListHandler>();
    }
}

void use_virtual_on_aggregate() {
    std::cout << "=== using virtual on aggregate ===\n";
    {
        std::vector container{1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto handler = choose_handler(true);
        handler->handle(container);
    }
    std::cout << '\n';
    /*
    {
        std::list   container{1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto handler = choose_handler(false);
        handler->handle(container);      
    }    
    */
}
#endif


#ifdef IMPROVED_VIRTUAL_ON_AGGREGATE

class HandlerBase {
    public:
    virtual ~HandlerBase() = default;
    virtual void handle(std::span<int> coll) = 0;
};

template<typename Derived>
class Handler: public HandlerBase {
    Derived d;
    public:
    virtual ~Handler() = default;
    virtual void handle(std::span<int> coll) override {
        for(auto elem: coll) {
            d.handle(elem);
        }
    }
};

class ListHandler {
    public:
    void handle(int data) {
        std::cout << "ListHandler::handle " << data << '\n';
    };
};

class VectorHandler {
    public:
    void handle(int data) {
        std::cout << "VectorHandler::handle " << data << '\n';
    };
};

std::unique_ptr<HandlerBase> choose_handler(bool vec_handle) {
    if(vec_handle) {
        return std::make_unique<Handler<VectorHandler>>();
    } else {
        return std::make_unique<Handler<ListHandler>>();
    }
}

void use_improved_virtual_on_aggregate() {
    std::cout << "=== using improved virtual on aggregate ===\n";
    {
        std::vector container{1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto handler = choose_handler(true);
        handler->handle(container);
    }
    std::cout << '\n';
    /*
    {
        std::list   container{1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto handler = choose_handler(false);
        handler->handle(container);      
    }    
    */
}
#endif


int main() {

#ifdef USE_INHERITANCE
    use_inheritance();
#endif

#ifdef USE_CONCEPT
    use_concept();
#endif

#ifdef VIRTUAL_ON_AGGREGATE
    use_virtual_on_aggregate();
#endif

#ifdef IMPROVED_VIRTUAL_ON_AGGREGATE
    use_improved_virtual_on_aggregate();
#endif

    return 0;
}

/*****
    END OF FILE
**********/



