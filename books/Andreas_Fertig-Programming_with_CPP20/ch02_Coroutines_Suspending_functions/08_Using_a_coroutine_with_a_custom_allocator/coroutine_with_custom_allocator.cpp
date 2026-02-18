/*******

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/language/coroutines
    https://github.com/andreasfertig/programming-with-cpp20/blob/main/02.25-coroutineParsingDataStreamCustomAllocator1/main.cpp

Chapter 2 | Coroutines: Suspending functions

A coroutine is a function that can suspend itself.

2.8 Using a coroutine with a custom allocator

    We can provide an operator new template, which then picks the right allocator.

*******/


#include <coroutine>
#include <exception>
#include <format>
#include <iostream>
#include <utility>


struct arena {
  void* Allocate(size_t size) noexcept;
  void  Deallocate(void* p, size_t size) noexcept;

  static arena* GetFromPtr(void* ptr, size_t size);
};

void* arena::Allocate(size_t sz) noexcept
{
  auto osz = sz;
  sz += sizeof(arena*);

  char* ptr = new char[sz];

  [[maybe_unused]] arena* a =
    reinterpret_cast<arena*>(ptr + osz);

  a = this;

  arena* b = reinterpret_cast<arena*>(ptr + osz);

  printf("custom alloc %zu  %p  %p  %p\n", osz, ptr, this, b);

  return ptr;
}

arena* arena::GetFromPtr(void* ptr, size_t sz)
{
  return reinterpret_cast<arena*>(static_cast<char*>(ptr) + sz);
}

void arena::Deallocate(void* ptr, size_t sz) noexcept
{
  printf("custom dealloc %zu  %p  %p\n", sz, ptr, this);
  delete[] static_cast<char*>(ptr);
}

namespace coro_iterator {

template <typename PT>
struct iterator {
    std::coroutine_handle<PT> m_coro_hdl{nullptr};

    void resume() {
        if (not m_coro_hdl.done()) {
            m_coro_hdl.resume();
        }
    }

    iterator() = default;
    iterator(std::coroutine_handle<PT> hco) : m_coro_hdl{hco} { resume(); }

    void operator++() { resume(); }
    bool operator==(const iterator&) const { return m_coro_hdl.done(); }

    const auto& operator*() const { return m_coro_hdl.promise().m_value; }
};

}  // namespace coro_iterator

void* myAllocate(size_t msize) noexcept {
    std::cout << "Inside " << __func__ << '\n';
    return calloc(1, msize);
}

void myDeallocate(void* ptr, size_t) noexcept {
    std::cout << "Inside " << __func__ << '\n';
    return free(ptr);
}

template <typename T, typename G>
struct promise_type_base {
    T m_value;  // A - The value yielded or returned from a coroutine

    auto yield_value(T value)  // B - Invoked by co_yield or co_return
    {
        m_value = std::move(value);    // C - Store the yielded value for access
                                       // outside the coroutine
        return std::suspend_always{};  // D - Suspend the coroutine here
    }

    G get_return_object() { return G{this}; };  // E - Return generator
    static auto get_return_object_on_allocation_failure() { return G{nullptr}; }

    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }

    void return_void() {}
    void unhandled_exception() { std::terminate(); }

    template<typename ...Args>
    void* operator new(size_t msize, arena & memalloc, Args&&...) noexcept { 
        return memalloc.Allocate(msize); 
    }

    void operator delete(void* ptr, size_t msize) noexcept {
        arena::GetFromPtr(ptr, msize)->Deallocate(ptr, msize);
    }
};

template <typename T>
class generator {
   public:
    using promise_type =
        promise_type_base<T, generator>;  // A - The PromiseType
    using PromiseTypeHandle = std::coroutine_handle<promise_type>;

    // D - As the default ctor is private promise_type needs to be a friend
    friend promise_type;

   private:
    explicit generator(promise_type* p)
        : m_coro_hdl{PromiseTypeHandle::from_promise(*p)} {}

    PromiseTypeHandle m_coro_hdl;  // E - The coroutine handle

   public:
    // B- Make the generator iterable
    using iterator = coro_iterator::iterator<promise_type>;
    iterator begin() { return {m_coro_hdl}; }
    iterator end() { return {}; }

    generator(generator const&) = delete;
    generator(generator&& rhs)
        : m_coro_hdl(std::exchange(rhs.m_coro_hdl, nullptr)) {}

    ~generator() {
        // C - We have to maintain the life - time of the coroutine
        if (m_coro_hdl) {
            m_coro_hdl.destroy();
        }
    }
};

using int_generator = generator<int>;

int_generator counter(arena &, const int start, const int end) {
    int val{start};

    while (val < end) {
        co_yield val;
        ++val;
    }
}

int main() {

    arena memarena{};
    auto cg = counter(memarena, 0, 10);

    for (auto c : cg) {
        std::cout << std::format("counter value: {}\n", c);
    }

    return 0;
}

/*****
    END OF FILE
**********/

