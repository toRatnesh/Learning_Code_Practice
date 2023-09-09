/*****

References
    Anthony Williams - C++ Concurrency in Action

3.2 Protecting shared data with mutexes
    mutex (mutual exclusion)
        You could mark all the pieces of code that access the data structure as mutually exclusive, so that if any thread was running one of them, any other thread that tried to access that data structure had to wait until the first thread was finished
        Mutexes also has issue of deadlock and protecting either too much or too little data

3.2.6 Flexible locking with std::unique_lock
	std::unique_lock provides a bit more flexibility than std::lock_guard
	unique_lock instance doesn’t always own the mutex that it’s associated with
	
	Use following as second argument
	std::adopt_lock: to have the lock object manage the lock on a mutex
	std::defer_lock: to indicate that the mutex should remain unlocked on construction

	The lock can then be acquired later by calling lock() on the std::unique_lock object (not the mutex) or by passing the std:: unique_lock object to std::lock().
	
	std::unique_lock takes more space and is slightly slower to use than std::lock_guard
	
	std::unique_lock forward request to the underlying mutex to do the work and update a flag inside the std::unique_lock instance to indicate whether the mutex is currently owned by that instance.
	
	This flag is necessary in order to ensure that unlock() is called correctly in the destructor.
	This flag can be queried by calling the owns_lock() member function.

	Uses
	used for deferred locking
	to transfer ownership of the lock

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
        std::unique_lock lock_a(m_img_mutex,        std::defer_lock);
        std::unique_lock lock_b(imgc.m_img_mutex,   std::defer_lock);
        std::lock(lock_a, lock_b);
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


