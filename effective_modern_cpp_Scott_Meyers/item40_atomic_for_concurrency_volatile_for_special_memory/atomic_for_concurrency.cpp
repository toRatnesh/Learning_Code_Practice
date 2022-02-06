/*************
	This example demonstrate the use of std::atomic for concurrency.

	For more info visit:
	

**********/

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

std::atomic_bool global_vec_ready(false);
int global_val = 0;

int reader() {

	while(true) {
		if(global_vec_ready) {
            std::clog << "reader thread, global value " << global_val << '\n';
			global_vec_ready = false;   
		}
		else {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	return 0;
}

int writer() {

	while(true) {
		if(!global_vec_ready) {
            std::clog << "writer thread\n";
			++global_val;
            global_vec_ready = true;
		}
		else {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	return 0;
}

int main() {
	std::thread lth_writer(writer);
	std::thread lth_reader(reader);

	lth_writer.join();
	lth_reader.join();

	return 0;
}

/********
	END OF FILE
******/
