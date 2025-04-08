/*******
        This example demonstrates the use of condition variable.
 
 ****************/


#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>

bool ready = false;
std::vector<int> global_vec;
std::condition_variable conv_global_vec;
std::mutex mt_ready;

int reader() {
	{
		std::unique_lock<std::mutex> l_lock(mt_ready);
		conv_global_vec.wait(l_lock, []{return true == ready;});
	}
	for(const auto elem: global_vec) {
		std::clog << elem << ' ';
	}
	std::clog << '\n';
	return 0;
}

int writer() {
	{
		std::lock_guard<std::mutex> l_lg(mt_ready);
		for(const auto elem : {1,2,3,4,5,6,7,8,9,10}) {
			global_vec.push_back(elem);
		}
		ready = true;
	}
	conv_global_vec.notify_one();
	return 0;
}

int main() {
	std::thread lth_writer(writer);
	std::thread lth_reader(reader);

	lth_writer.join();
	lth_reader.join();

	return 0;
}

/*******
    END OF FILE
 ******/
