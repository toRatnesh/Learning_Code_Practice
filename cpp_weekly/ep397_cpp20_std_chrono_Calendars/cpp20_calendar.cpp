/*****

References
    episode https://www.youtube.com/watch?v=I53iT3gPXrk
    https://en.cppreference.com/w/cpp/chrono
    https://en.cppreference.com/w/cpp/header/chrono

    Clock, Duration and Time Points
    https://github.com/toRatnesh/Learning_Code_Practice/tree/main/books/Anthony_Williams-CPP_Concurrency_in_Action/04_Synchronizing_concurrent_operations/03_Waiting_with_a_time_limit

**********/

#include <iostream>
#include <chrono>
#include <format>

int main() {

    {
        std::cout << "=== Using system_clock ===\n";
        
        auto start = std::chrono::system_clock::now();
        const auto days{std::chrono::floor<std::chrono::days>(start)};
        std::cout << std::format("{} aka {}\n", start, days);
        
        const auto hr{std::chrono::hours(10)};
        std::cout << std::format("{} from now {}\n", hr, start+hr);

        auto end = std::chrono::system_clock::now();
        auto time_diff = end - start;
        std::cout << std::format("elapsed time {}/{}/{}/{}\n",
            time_diff,
            std::chrono::duration_cast<std::chrono::microseconds>(time_diff),
            std::chrono::duration_cast<std::chrono::milliseconds>(time_diff),
            std::chrono::duration_cast<std::chrono::seconds>(time_diff));

    }
    
    {
        std::cout << "=== Using utc_clock ===\n";
        auto start = std::chrono::utc_clock::now();
        const auto days{std::chrono::floor<std::chrono::days>(start)};
        std::cout << std::format("{} aka {}\n", start, days);
        
        const auto hr{std::chrono::hours(10)};
        std::cout << std::format("{} from now {}\n", hr, start+hr);

        auto end = std::chrono::utc_clock::now();
        auto time_diff = end - start;
        std::cout << std::format("elapsed time {}/{}/{}/{}\n",
            time_diff,
            std::chrono::duration_cast<std::chrono::microseconds>(time_diff),
            std::chrono::duration_cast<std::chrono::milliseconds>(time_diff),
            std::chrono::duration_cast<std::chrono::seconds>(time_diff));

    }

    return 0;
}

/*****
    END OF FILE
**********/


