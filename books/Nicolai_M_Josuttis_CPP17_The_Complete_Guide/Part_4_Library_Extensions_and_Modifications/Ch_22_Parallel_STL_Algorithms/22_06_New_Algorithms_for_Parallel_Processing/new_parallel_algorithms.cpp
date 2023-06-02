/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/execution

Chapter 22 Parallel STL Algorithms
    
    C++17 allow STL standard algorithms to run 
    using multiple threads to deal with different elements in parallel.
    
22.6 New Algorithms for Parallel Processing

22.6.1 reduce()

	reduce() was introduced as a parallel form of accumulate()
	
	Parallelization for Commutative Operations
		Example: addition (+) operation, which is commutative so that 
        the order of adding the integral elements doesn’t matter
	
	Parallelization for Non-Commutative Operations
		for floating-point values the order matters,
		
        While the results look the same they sometimes differ
		This is a possible consequence of adding floating-point values in different order.
		
        Because it is undefined if, when, and how parallel algorithms are implemented, 
        the result might look the same on some platforms (up to a certain number of elements).

    Parallelization for Non-Associative Operations

        with reduce() parallel algorithm the result sometimes might be wrong
        the problem is that the operation is not associative
        
        use test cases with enough elements to detect problems like this
        
        solution to this problem is to use another new algorithm, transform_reduce()
        It separates the modification we want to perform with each element (which is one thing we can parallelize)
        and the accumulation of the results provided it is commutative (which is the other thing we can parallelize
        
        transform_reduce() will probably be by far the most important parallel algorithm, 
        because often we modify values before we combine them (also called the map reduce principle)

*************/

#include <iostream>
#include <vector>
#include <execution>
#include <algorithm>
#include <iomanip>
#include <filesystem>

#include <string>
#include <chrono>

class Timer {
    std::chrono::steady_clock::time_point m_start;
    std::chrono::steady_clock::time_point m_stop;
    
    public:
    void start()    { m_start = std::chrono::steady_clock::now();   }
    void stop()     { m_stop = std::chrono::steady_clock::now();    }
    
    void display(const std::string& msg = "Timer diff: ") {
        std::chrono::duration<double, std::micro> diff{m_stop - m_start};
        std::cout << msg << diff.count() << "μs\n";
    }
};

void printCommutativeOperation(size_t num_elems) {
    Timer bt_time;

    std::cout << "Number of elements " << num_elems << '\n';
    std::vector<int> coll;
    coll.reserve(num_elems);

    for(size_t i = 0; i < num_elems; ++i) {
        coll.push_back(i);
    }

    {
    bt_time.start();
    auto res_acc = std::accumulate(coll.begin(), coll.end(), 0);
    bt_time.stop();
    std::cout << "Result of accumulate() is " << res_acc << '\n';
    bt_time.display("Time taken by accumulate() is ");
    }

    {
    bt_time.start();
    auto res_red = std::reduce(std::execution::par, coll.begin(), coll.end(), 0);
    bt_time.stop();
    std::cout << "Result of reduce() is " << res_red << '\n';
    bt_time.display("Time taken by reduce() using parallel execution is ");
    }
}

void printNonCommutativeOperation(size_t num_elems) {
    Timer bt_time;

    std::cout << "Number of elements " << num_elems << '\n';
    std::vector<double> coll;
    coll.reserve(num_elems);

    for(size_t i = 0; i < num_elems; ++i) {
        coll.push_back(i * 0.000000093);
    }

    std::cout.precision(20);
    
    bt_time.start();
    auto res_acc = std::accumulate(coll.begin(), coll.end(), 0.0);
    bt_time.stop();
    std::cout << "Result of accumulate() is " << std::setw(25) << res_acc << '\n';
    bt_time.display("Time taken by accumulate() is ");
    
    bt_time.start();
    auto res_red = std::reduce(std::execution::par, coll.begin(), coll.end(), 0.0);
    bt_time.stop();
    std::cout << "Result of reduce() is " << std::setw(25) << res_red << '\n';
    bt_time.display("Time taken by reduce() using parallel execution is ");

    // While the results look the same they sometimes differ. 
    // This is a possible consequence of addingfloating-point values in different order
    std::cout << "Result of accumulate() and reduce() is " << ((res_acc == res_red) ? "same" : "different") << '\n';
    
}

void printNonAssociativeOperation(size_t num_elems) {
    Timer bt_time;

    std::cout << "Number of elements " << num_elems << '\n';
    std::vector<int> coll;
    coll.reserve(num_elems);

    for(size_t i = 0; i < num_elems; ++i) {
        coll.push_back(i);
    }

    auto square_sum = [](auto sum, auto val){ return sum + (val * val);};

    {
    bt_time.start();
    auto res_acc = std::accumulate(coll.begin(), coll.end(), 0, square_sum);
    bt_time.stop();
    std::cout << "Result of accumulate() is " << res_acc << '\n';
    bt_time.display("Time taken by accumulate() is ");
    }

    {
    bt_time.start();
    auto res_red = std::reduce(std::execution::par, coll.begin(), coll.end(), 0, square_sum);
    bt_time.stop();
    // the result sometimes might be wrong. The problem is that the operation is not associative
    std::cout << "Result of reduce() is " << res_red << '\n';
    bt_time.display("Time taken by reduce() using parallel execution is ");
    }

    {
    bt_time.start();
    auto res_trans_red = std::transform_reduce(std::execution::par, coll.begin(), coll.end(), 0, 
                            std::plus<int>{}, [](auto val){ return val * val;});
    bt_time.stop();
    std::cout << "Result of transform_reduce() is " << res_trans_red << '\n';
    bt_time.display("Time taken by transform_reduce() using parallel execution is ");
    }
}

void transformReduceForFilesystem(const std::string path) {
    // this example is also available
    // https://github.com/socialratnesh/Learning_Code_Practice/blob/main/books/Nicolai_M_Josuttis_CPP17_The_Complete_Guide/Part_3_New_Library_Components/Ch_20_The_Filesystem_Library/20_01_Basic_Examples/20_01_04_Dealing_with_Filesystems_Using_Parallel_Algorithms/dealing_with_filesystems_using_parallel_algorithms.cpp
 
    namespace fs = std::filesystem;

    fs::path root_dir{path};
    std::vector<fs::path> path_coll;
    try {
        fs::recursive_directory_iterator dir_itr{root_dir};
        std::copy(fs::begin(dir_itr), fs::end(dir_itr), std::back_inserter(path_coll));

    } catch(const fs::filesystem_error & fexp) {
        std::clog << "File operation exception " << fexp.what() << '\n';
        std::clog << "  path1 " << fexp.path1() << '\n';
        std::clog << "  path2 " << fexp.path2() << '\n';
        std::clog << "  Code value " << fexp.code().value() << '\n';
        std::clog << "  Code message " << fexp.code().message() << '\n';
        std::clog << "  Code category " << fexp.code().category().name() << '\n';
    }

    /*
    you can’t pass the paths the directory iterator iterates over directly to the parallel algorithm, 
    because directory iterators are input iterators while the parallel algorithms require forward iterators
    */
    auto res_fsize = std::transform_reduce(std::execution::par,
                        path_coll.begin(), path_coll.end(),
                        std::uintmax_t{0},
                        std::plus{},
                        [](const fs::path & file_path){ 
                            return is_regular_file(file_path) ? file_size(file_path) : std::uintmax_t{0};
                        }
                    );
    std::cout << "size of all " << path_coll.size() << " regular files " << res_fsize << '\n';
}

int main(int argc, char * argv[]) {

    if(2 != argc) { std::cout << "Usage: " << argv[0] << " <path>\n"; }
    
    std::cout << "=== Commutative Operations ===\n";
    printCommutativeOperation(10);       std::cout << '\n';
    //printCommutativeOperation(100);      std::cout << '\n';
    //printCommutativeOperation(1000);     std::cout << '\n';
    //printCommutativeOperation(10000);    std::cout << '\n';

    std::cout << "\n=== Non-Commutative Operations ===\n";
    printNonCommutativeOperation(10);       std::cout << '\n';
    //printNonCommutativeOperation(100);      std::cout << '\n';
    //printNonCommutativeOperation(1000);     std::cout << '\n';
    printNonCommutativeOperation(10000);    std::cout << '\n';

    std::cout << "\n=== Non-Associative Operations ===\n";
    printNonAssociativeOperation(10);       std::cout << '\n';
    //printNonAssociativeOperation(100);      std::cout << '\n';
    //printNonAssociativeOperation(1000);     std::cout << '\n';
    printNonAssociativeOperation(10000);    std::cout << '\n';

    std::cout << "\n=== transform_reduce() for Filesystem Operations ===\n";
    transformReduceForFilesystem("/home/");
    return 0;
}

/**********
    END OF FILE
*************/


