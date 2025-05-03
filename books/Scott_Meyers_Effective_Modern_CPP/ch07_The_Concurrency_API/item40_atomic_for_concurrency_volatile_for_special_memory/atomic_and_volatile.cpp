/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/atomic/atomic
	https://en.cppreference.com/w/c/language/volatile

Item 40: Use std::atomic for concurrency, volatile for special memory

std::atomic

	Once a std::atomic object has been constructed, operations on it behave as if 
	they were inside a mutex-protected critical section, but the operations are generally implemented 
	using special machine instructions that are more efficient than would be the case if a mutex were employed.

		std::atomic<int> ai(0);		// initialize ai to 0
		ai = 10;					// atomically set ai to 10
		std::cout << ai;			// atomically read ai's value
		++ai;						// atomically increment ai to 11
		--ai;						// atomically decrement ai to 10
		
	.	in the “std::cout << ai;” statement, the fact that ai is a std::atomic guarantees only that the read of ai is atomic. 
		There is no guarantee that the entire statement proceeds atomically.
		
	.	"++ai" and "--ai" are each read-modify-write (RMW) operations, yet they execute atomically.
		once a std::atomic object has been constructed, all member functions on it, 
		including those comprising RMW operations, are guaranteed to be seen by other threads as atomic.

volatile
	volatile guarantees virtually nothing in a multithreaded context
	
	Consider a simple counter of each type that’s incremented by multiple threads.
	
	std::atomic<int> ac(0);	// "atomic counter"
	volatile int vc(0);		// "volatile counter"
	
	----- Thread 1 -----	------- Thread 2 ------- 
			++ac;					++ac;
			++vc;					++vc;
	
	When both threads have finished, ac’s value must be 2,
	
	vc’s final value is, in general, not predictable, because vc is involved in a data race, and 
	the Standard’s decree that data races cause undefined behavior
	
Code reordering with atomic and volatile
	atomic might be used for inter thread communication
	
	Consider code in the task computing the value would look something like this:

	std::atomic<bool> valAvailable(false);
	auto imptValue = computeImportantValue();	// compute value
	valAvailable = true;	// tell other task it's available

	As a general rule, compilers are permitted to reorder unrelated assignments.
	Even if compilers don’t reorder them, the underlying hardware might do it
	
	However, the use of std::atomics imposes restrictions on how code can be reordered, 
	and one such restriction is that no code that, in the source code, 
	precedes a write of a std::atomic variable may take place (or appear to other cores to take place) afterwards.
	
	Declaring valAvailable as volatile doesn’t impose the same code reordering restrictions
	
	volatile bool valAvailable(false);
	auto imptValue = computeImportantValue();
	valAvailable = true;	// other threads might see this assignment before the one to imptValue!
	
	Here, compilers or machine code might flip the order of the assignments to imptValue and valAvailable

	Two issues with volatile
		1.	no guarantee of operation atomicity 
		2.	insufficient restrictions on code reordering
	
Use of volatile
	it’s for telling compilers that they’re dealing with memory that doesn’t behave normally
	
	Consider following code
	auto y = x;		// read x
	y = x;			// read x again, it’s redundant with y’s initialization
	
	x = 10;			// write x, first write can be eliminated, because it was never used
	x = 20;			// write x again
	
	compilers can treat it as if it had been written like this:
	auto y = x;		// read x
	x = 20;			// write x
	
	compilers can get rid of such redundant loads and dead stores
	
	Such optimizations are valid only if memory behaves normally. “Special” memory doesn’t. 
	Probably the most common kind of special memory is memory used for memory-mapped I/O.
	
	volatile is the way we tell compilers that we’re dealing with special memory.
	Its meaning to compilers is “Don’t perform any optimizations on operations on this memory.”
	
	So if x corresponds to special memory
	
	volatile int x;
	
	auto y = x;			// read x
	y = x;				// read x again (can't be optimized away)

	x = 10;				// write x (can't be optimized away)
	x = 20;				// write x again
	
redundant loads and dead stores in atomic	
	Compilers are permitted to eliminate such redundant operations on std::atomics.

	std::atomic<int> x;
	auto y = x;	// conceptually read x (ERROR COPY CONSTRUCTOR NOT PRESENT FOR ATOMIC)
	y = x;		// conceptually read x again (ERROR COPY ASSIGNMENT NOT PRESENT FOR ATOMIC)
	
	x = 10;		// write x
	x = 20;		// write x again
	
	compiler can optimize it to this:
	auto y = x;	// conceptually read x (ERROR COPY CONSTRUCTOR NOT PRESENT FOR ATOMIC)
	x = 20;		// write x

	to get the value of x into y,
	
	std::atomic<int> y(x.load());	// read x
	y.store(x.load());				// read x again
	
	compilers could “optimize” it by storing x’s value in a register instead of reading it twice:
	
	register = x.load();			// read x into register
	std::atomic<int> y(register);	// init y with register value
	y.store(register);				// store register value into y
	
	
	
• std::atomic is useful for concurrent programming, but not for accessing special memory.
• volatile is useful for accessing special memory, but not for concurrent programming.

std::atomic and volatile serve different purposes, they can even be used together:

	volatile std::atomic<int> vai;	// operations on vai are atomic and can't be optimized away

This could be useful if vai corresponded to a memory-mapped I/O location that was concurrently accessed by multiple threads.	


Summary
	• std::atomic is for data accessed from multiple threads without using mutexes. It’s a tool for writing concurrent software.
	• volatile is for memory where reads and writes should not be optimized away. It’s a tool for working with special memory.

**********/

#include <iostream>
#include <thread>
#include <atomic>

namespace nonstd {
    class jthread {
        bool            m_join_flag;
        std::thread     m_thrd;

        public:
        ~jthread() {
            if(m_thrd.joinable()) {
                if(m_join_flag) {
                    m_thrd.join();
                } else {
                    m_thrd.detach();
                }
            }
        }

        jthread(std::thread && thr, const bool join_flag = true) 
        : m_join_flag{join_flag}, m_thrd{std::move(thr)} {  }

        jthread(jthread&&   )               = default;
        jthread& operator=(jthread&&   )    = default;

        std::thread & get() { return m_thrd; }
    };
}

std::atomic_bool            atomic_flag;

void consumer_using_atomic_flag() {
    while(not atomic_flag) { };
    std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
}

void producer_using_atomic_flag() {
    std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
    atomic_flag = true;
}

auto use_atomic() {

    // compliler may optimize redundant loads and dead stores

    std::atomic<int>    atom_val{1};

    //auto y = atom_val;
    //y = atom_val;

    atom_val = 2;
    atom_val = 5;

    std::atomic<int> y{atom_val.load()};
    y.store(atom_val.load());

    return y.load();
}

auto use_volatile() {

    // compliler may optimize redundant loads and dead stores

    volatile int    volt_val{1};

    volt_val = 2;
    volt_val = 5;

    auto y = volt_val;
    y = volt_val;

    return y;
}

auto use_volatile_atomic() {

    // compliler will not optimize redundant loads and dead stores

    volatile std::atomic<int>    atom_val{1};

    atom_val = 2;
    atom_val = 5;

    std::atomic<int> y{atom_val.load()};
    y.store(atom_val.load());

    return y.load();
}

std::atomic<int>    atom_val{0};
volatile int        volt_val{0};

void increment(const bool flag) {
    if(flag) {
        ++atom_val;
    } else {
        ++volt_val;
    }
}

int main() {

    {   std::cout << "=== producer consumer using atomic flag ===\n";
        nonstd::jthread thr1(std::thread{producer_using_atomic_flag});
        nonstd::jthread thr2(std::thread{consumer_using_atomic_flag});
    }

    {   std::cout << "\n=== using atomic and volatile in concurrent code ===\n";
        nonstd::jthread thr1(std::thread{increment, true});
        nonstd::jthread thr2(std::thread{increment, true}); 

        nonstd::jthread thr3(std::thread{increment, false});
        nonstd::jthread thr4(std::thread{increment, false}); 
    }

    {   
        std::cout << atom_val << ", atomic value is guaranteed to be 2\n";
        std::cout << volt_val << ", volatile value is not guaranteed to be 2\n";
    }

    {   std::cout << "\n=== using atomic, volatile and volatile atomic ===\n";
        std::cout << "Getting atomic value " << use_atomic() << '\n';
        std::cout << "Getting volatile value " << use_volatile() << '\n';
        std::cout << "Getting volatile atomic value " << use_volatile_atomic() << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/

