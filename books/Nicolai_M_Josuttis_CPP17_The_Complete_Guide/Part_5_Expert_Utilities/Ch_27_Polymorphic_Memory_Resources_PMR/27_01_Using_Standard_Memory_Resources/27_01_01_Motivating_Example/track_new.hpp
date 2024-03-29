//********************************************************
// The following code example is taken from the book
//  C++17 - The Complete Guide
//  by Nicolai M. Josuttis (www.josuttis.com)
//  http://www.cppstd17.com
//
// The code is licensed under a
//  Creative Commons Attribution 4.0 International License
//  http://creativecommons.org/licenses/by/4.0/
//********************************************************


#ifndef TRACKNEW_HPP
#define TRACKNEW_HPP

#include <new>       // for std::align_val_t
#include <cstdio>    // for printf()
#include <cstdlib>   // for malloc() and aligned_alloc()

class TrackNew {
  static inline int		numMalloc	= 0;    // num malloc calls
  static inline size_t	sumSize		= 0;   // bytes allocated so far
  static inline bool	doTrace		= false; // tracing enabled
  static inline bool	inNew		= false;   // don't track output inside new overloads
 public:
  static void reset() {               // reset new/memory counters
    numMalloc = 0;
    sumSize = 0;
  }

  static void trace(bool b) {         // enable/disable tracing
    doTrace = b;
  }

  // implementation of tracked allocation:
  static void* allocate(std::size_t size, std::size_t align,
                        const char* call) {
    // track and trace the allocation:
    ++numMalloc;
    sumSize += size;
    void* p;
    if (align == 0) {
      p = std::malloc(size);
    }
    else {
        p = std::aligned_alloc(align, size);  // C++17 API
    }
    if (doTrace) {
      // DON'T use std::cout here because it might allocate memory
      // while we are allocating memory (core dump at best)
      printf("#%d %s ", numMalloc, call);
      printf("(%zu bytes, ", size);
      if (align > 0) {
        printf("%zu-byte aligned) ", align);
      }
      else {
        printf("def-aligned) ");
      }
      printf("=> %p (total: %zu bytes)\n", (void*)p, sumSize);
    }
    return p;
  }

  static void status() {              // print current state
    printf("%d allocations for %zu bytes\n", numMalloc, sumSize);
  }
};

[[nodiscard]]
void* operator new (std::size_t size) {
  return TrackNew::allocate(size, 0, "::new");
}

[[nodiscard]]
void* operator new (std::size_t size, std::align_val_t align) {
  return TrackNew::allocate(size, static_cast<size_t>(align),
                            "::new aligned");
}

[[nodiscard]]
void* operator new[] (std::size_t size) {
  return TrackNew::allocate(size, 0, "::new[]");
}

[[nodiscard]]
void* operator new[] (std::size_t size, std::align_val_t align) {
  return TrackNew::allocate(size, static_cast<size_t>(align),
                            "::new[] aligned");
}

// ensure deallocations match:
void operator delete (void* p) noexcept {
  std::free(p);
}
void operator delete (void* p, std::size_t) noexcept {
  ::operator delete(p);
}
void operator delete (void* p, std::align_val_t) noexcept {
    std::free(p);      // C++17 API
}
void operator delete (void* p, std::size_t,
                               std::align_val_t align) noexcept {
  ::operator delete(p, align);
}

#endif // TRACKNEW_HPP


