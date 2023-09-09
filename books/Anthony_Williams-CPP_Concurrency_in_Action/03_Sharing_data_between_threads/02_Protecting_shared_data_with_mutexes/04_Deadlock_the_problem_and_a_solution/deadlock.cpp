/*****

References
    Anthony Williams - C++ Concurrency in Action

3.2 Protecting shared data with mutexes
    mutex (mutual exclusion)
        You could mark all the pieces of code that access the data structure as mutually exclusive, so that if any thread was running one of them, any other thread that tried to access that data structure had to wait until the first thread was finished
        Mutexes also has issue of deadlock and protecting either too much or too little data

3.2.4 Deadlock: the problem and a solution
	Deadlock
	Consider two mutex are used to protect a shared data, and threads arguing over locks on mutexes: each of a pair of threads needs to lock both of a pair of mutexes to perform some operation, and each thread has one mutex and is waiting for the other. Neither thread can proceed, because each is waiting for the other to release its mutex. This scenario is called deadlock.
	
	advice for avoiding deadlock is to always lock the two mutexes in the same order
	
	C++ Standard Library has a cure for this
	std::lock a function that can lock two or more mutexes at once without risk of deadlock
	
	In the example code
	call to std::lock() locks the two mutexes
	two std::lock_guard instances are constructed, one for each mutex
	std::adopt_lock parameter is supplied in addition to the mutex to indicate to the std::lock_guard objects that the mutexes are already locked, and they should adopt the ownership of the existing lock on the mutex rather than attempt to lock the mutex in the constructor
	This ensures that the mutexes are correctly unlocked on function exit in the general case where the protected operation might throw an exception; it also allows for a simple return.
	
	std::lock provides all-or-nothing semantics with regard to locking the supplied mutexes
	
	std::scoped_lock<>
	Since C++17, additional support for above scenario, in the form of a new RAII
	This is exactly equivalent to std::lock_guard<>, except that it is a variadic template, accepting a list of mutex types as template parameters, and a list of mutexes as constructor arguments.
	
	NOTE: std::lock (and std::scoped_lock<>) doesn’t help to avoid deadlock if locks are acquired separately

**********/

#include <iostream>
#include <mutex>
#include <thread>
#include <string>

class Image {
    std::string     m_img_id;
    public:
    Image(std::string id) : m_img_id(id) { 
        std::cout << "Constructing image id " << m_img_id << '\n';
    }
    Image(const Image & img) : m_img_id(img.m_img_id) { }
    Image(Image && img) : m_img_id(std::move(img.m_img_id)) { }

    void displayImg() const { 
        std::cout << "Image id " << m_img_id << '\n';
    }

    void swap(Image & img) {
        if(this == &img) return ;
        std::string temp = img.m_img_id;;
        img.m_img_id = m_img_id;
        m_img_id = temp;
    }
};

class ImageController {
    Image       m_img;
    std::mutex  m_img_mutex;

    public:
    ImageController(const Image & img) : m_img(img) {}
    ImageController(const ImageController & imgc) : m_img(imgc.m_img) { }
    ImageController(ImageController && img) :  m_img(std::move(img.m_img)){}
    
    void swap(ImageController & imgc) {
        if(this == &imgc) {
            return ;
        }
        std::lock(m_img_mutex, imgc.m_img_mutex);
        std::lock_guard lock_a(m_img_mutex, std::adopt_lock);
        std::lock_guard lock_b(imgc.m_img_mutex, std::adopt_lock);
        m_img.swap(imgc.m_img);
    }

    Image getImage() { return m_img; }
};

int main() {

    Image img_01("image-01");
    Image img_02("image-02");
    std::cout << '\n';

    ImageController imgc_01(img_01);
    ImageController imgc_02(img_02);

    imgc_01.getImage().displayImg();
    imgc_02.getImage().displayImg();
    std::cout << '\n';

    std::thread thr(&ImageController::swap, std::ref(imgc_01), std::ref(imgc_02));
    thr.join();

    imgc_01.getImage().displayImg();
    imgc_02.getImage().displayImg();

    return 0;
}

/*****
    END OF FILE
**********/


