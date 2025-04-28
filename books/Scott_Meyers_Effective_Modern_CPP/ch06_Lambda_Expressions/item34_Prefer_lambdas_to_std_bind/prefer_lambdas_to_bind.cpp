/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/lambda

Item 34: Prefer lambdas to std::bind

lambdas are almost always a better choice than std::bind

In C++14, there are no reasonable use cases for std::bind

In C++11 std::bind may be useful for
	->	Move capture
	->	Polymorphic function objects

Drawbacks of bind
	->	arguments are copied into bind so an expression may be evaluated at the time it is called
		auto setSoundB = std::bind(setAlarm,
									steady_clock::now() + 1h,	// incorrect! see below
									_1,
									30s);

		the expression will be evaluated when std::bind is called, 
		and the time resulting from that expression will be stored inside the resulting bind object
		As a consequence, the alarm will be set to go off an hour after the call to std::bind, not an hour after the call to setAlarm
		
	->	in case of function overload we need to specify cast to the actual overload we need to call using bind
	->	call to function can be inlined in case of lambda this case is less likely for std::bind
		It’s thus possible that using lambdas generates faster code than using std::bind
	->	we need to memorize how std::bind works
		.	arguments to bind are stored by value
		.	all arguments passed to bind objects are passed by reference, 
			because the function call operator for such objects uses perfect forwarding
	->	Compared to lambdas, then, code using std::bind is less readable, less expressive, and possibly less efficient
	
Summary
•	Lambdas are more readable, more expressive, and may be more efficient than using std::bind
•	In C++11 only, std::bind may be useful for implementing move capture or for binding objects with templatized function call operators

**********/

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <iomanip>

using x_clock_t = std::chrono::steady_clock;
using steady_time_p = std::chrono::time_point<x_clock_t>;
using duration_t = std::chrono::steady_clock::duration;
enum class sound_t { BEEP, WHISTLE, SING };

void display_time(std::chrono::time_point<std::chrono::system_clock> ltp) {
	std::time_t now_time_t = std::chrono::system_clock::to_time_t(ltp);
	std::cout << "Current time: " << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d %H:%M:%S") << '\n';

}

void make_sound(sound_t snd) {
    switch (snd) {
        case sound_t::BEEP:
            std::puts("BEEP");
            break;
        case sound_t::WHISTLE:
            std::puts("WHISTLE");
            break;
        case sound_t::SING:
            std::puts("SING");
            break;
    }
}

void setAlarm(steady_time_p tp, sound_t snd, duration_t dur) {

    std::this_thread::sleep_until(tp);
    
    auto l_now = std::chrono::system_clock::now();
    display_time(l_now);

    auto l_start = x_clock_t::now();

    while ((x_clock_t::now() - l_start) < dur) {
        make_sound(snd);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    {   std::cout << "=== Set alarm using bind ===\n";
        auto set_alarm =
            std::bind(setAlarm, x_clock_t::now() + std::chrono::seconds(10),
                      sound_t::WHISTLE, std::chrono::seconds(3));

        std::this_thread::sleep_for(std::chrono::seconds(5));

	auto l_now = std::chrono::system_clock::now();
	display_time(l_now);
        set_alarm();
    }

    {   std::cout << "\n=== Set alarm using lambda ===\n";
        auto set_alarm = []() {
            setAlarm(x_clock_t::now() + std::chrono::seconds(10),
                     sound_t::WHISTLE, std::chrono::seconds(3));
        };

        std::this_thread::sleep_for(std::chrono::seconds(5));

	auto l_now = std::chrono::system_clock::now();
	display_time(l_now);
        set_alarm();
    }

    return 0;
}

/*****
    END OF FILE
**********/

