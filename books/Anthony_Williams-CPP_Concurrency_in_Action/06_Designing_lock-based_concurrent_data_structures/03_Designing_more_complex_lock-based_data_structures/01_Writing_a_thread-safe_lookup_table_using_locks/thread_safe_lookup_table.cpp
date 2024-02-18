/*****

References
    Anthony Williams - C++ Concurrency in Action

6. Designing lock-based concurrent data structures

    In this chapter we’ll start by taking the basic building blocks of locks and condition variables and revisit the design of basic data structures

6.3 Designing more complex lock-based data structures

Not all data structures are that simple; most data structures support a variety of operations. 
In principle, this can then lead to greater opportunities for concurrency, 
but it also makes the task of protecting the data that much harder because 
the multiple access patterns need to be taken into account.


6.3.1 Writing a thread-safe lookup table using locks

In the C++ STL, this facility is provided by the associative containers: std::map<>, std::multimap<>, std::unordered_map<>, and std::unordered_multimap<>.
The biggest problem with the std::map<> interface from a concurrency perspective is the iterators.
Correctly handling iterators requires you to deal with issues such as another thread deleting the element that the iterator is referring to.

For a thread-safe lookup table interface, skip the iterators.
A few basic operations on a lookup table:
	-> Add a new key/value pair.
	-> Change the value associated with a given key.
	-> Remove a key and its associated value.
	-> Obtain the value associated with a given key, if any.

DESIGNING A MAP DATA STRUCTURE FOR FINE-GRAINED LOCKING
Three common ways of implementing an associative container like your lookup table:
	1. A binary tree, such as a red-black tree
	2. A sorted array
	3. A hash table
	
1. Binary Tree, every lookup or modification has to start by accessing the root node, which therefore has to be locked. 
Although this lock can be released as the accessing thread moves down the tree, this isn’t much better than a single lock across the whole data structure.

2. A sorted array is even worse, because you can’t tell in advance where in the array a given data value is going to be, so you need a single lock for the whole array.

3. Assuming a fixed number of buckets, which bucket a key belongs to is purely a property of the key and its hash function. 
This means you can safely have a separate lock per bucket. If you again use a mutex that supports multiple readers or a single writer, 
you increase the opportunities for concurrency N-fold, where N is the number of buckets.
The downside is that you need a good hash function for the key. The C++ Standard Library provides the std::hash<> template, which you can use for this purpose.

**********/

#include <iostream>
#include <exception>
#include <memory>

#include <list>
#include <string>
#include <vector>

#include <thread>
#include <mutex>
#include <syncstream>
#include <shared_mutex>

#include <algorithm>

template<typename key_t, typename val_t, typename hash_t = std::hash<key_t>>
class thsafe_lookup_table {

    class bucket_t {
        using bucket_val_t  = std::pair<key_t, val_t>;
        using bucket_data_t = std::list<bucket_val_t>;
        using bucket_itr_t  = bucket_data_t::iterator;

        bucket_data_t       m_bucket_data;
        std::shared_mutex   m_bucket_data_mutex;

        bucket_itr_t find_entry_for(const key_t & key)  {
            return std::find_if(m_bucket_data.begin(), m_bucket_data.end(),
            [&](const bucket_val_t & bval){ return key == bval.first; });
        }

        public:

        void remove(const key_t & key) {
            std::lock_guard         l_lock(m_bucket_data_mutex);
            bucket_itr_t l_itr =    find_entry_for(key);
            if(m_bucket_data.end() != l_itr) {
                m_bucket_data.erase(l_itr);
            }
        }

        void add_or_update(const key_t & key, const val_t & val) {
            std::lock_guard         l_lock(m_bucket_data_mutex);
            bucket_itr_t l_itr =    find_entry_for(key);
            if(m_bucket_data.end() ==  l_itr) {
                m_bucket_data.push_back(bucket_val_t{key, val});
            } else {
                l_itr->second = val;
            }
        }

        val_t get(const key_t & key, const val_t & default_val)  {
            std::shared_lock        l_lock(m_bucket_data_mutex);
            bucket_itr_t l_itr = find_entry_for(key);
            if(m_bucket_data.end() == l_itr) {
                return default_val;
            }
            return l_itr->second;
        }
    }; // bucket_t

    std::vector<std::unique_ptr<bucket_t>>  m_buckets;
    hash_t                                  m_hasher;

    bucket_t & get_bucket(const key_t & key) const {
        const std::size_t   index = m_hasher(key)%m_buckets.size();
        return *(m_buckets[index]);
    }

    public:
    thsafe_lookup_table(const thsafe_lookup_table &)                = delete;
    thsafe_lookup_table & operator=(const thsafe_lookup_table &)    = delete;

    thsafe_lookup_table(const std::size_t num_buckets = 17, const hash_t & hasher = hash_t()) 
        : m_buckets(num_buckets), m_hasher(hasher) {
            for(std::size_t i = 0; i < num_buckets; ++i) {
                m_buckets[i] = std::make_unique<bucket_t>();
            }
    }

    val_t get(const key_t & key, const val_t & default_val = val_t{}) const {
        return get_bucket(key).get(key, default_val);
    }

    void add_or_update(const key_t & key, const val_t & val) {
        get_bucket(key).add_or_update(key, val);
    }

    void remove(const key_t & key) {
        get_bucket(key).remove(key);
    }

};

const std::size_t count = 20;

thsafe_lookup_table<std::string, std::string> gtable(count);
std::osyncstream syn_cout(std::cout);

void add_or_update(const std::size_t count) {
    for(std::size_t i = 0; i < count; ++i) {
        const std::string l_key = std::string("key-")+std::to_string(i);
        const std::string l_val = std::string("value-")+std::to_string(i);
        gtable.add_or_update(l_key, l_val);
    }
}

void remove_keys(const std::size_t count) {
    for(std::size_t i = 0; i < count; ++i) {
        gtable.remove(std::string("key-")+std::to_string(i));
    }  
}

void get(const std::size_t count) {
    for(std::size_t i = 0; i < count; ++i) {
        const std::string l_key = std::string("key-")+std::to_string(i);
        std::string l_default_val = std::string("DEFAULT_VAL"); 
        const auto val = gtable.get(l_key);
        std::cout << "Value for " << l_key << " is " << val << '\n';
    }
}

int main() {

    std::vector<std::thread> vecth;

    vecth.push_back(std::thread(add_or_update, count));
    vecth.push_back(std::thread(get, count));
    vecth.push_back(std::thread(remove_keys, count));

    for(auto & th : vecth) {
        th.join();
    }

    return 0;
}

/*****
Explanation


This implementation uses a std::vector<std::unique_ptr<bucket_type>> to hold the buckets, which allows the number of buckets to be specified in the constructor.
The default is 19, which is an arbitrary prime number; hash tables work best with a prime number of buckets.
Each bucket is protected with an instance of std::shared_mutex B to allow many concurrent reads or a single call to either of the modification functions per bucket.

what about exception safety? 
get() doesn’t modify anything, so that’s fine; if it throws an exception, it won’t affect the data structure. 

remove() modifies the list with the call to erase, but this is guaranteed not to throw, so that’s safe. 

add_or_update(), which might throw in either of the two branches of if. 
push_back is exception-safe and will leave the list in the original state if it throws, so that branch is fine. 
The only problem is with the assignment in the case where you’re replacing an existing value; 
if the assignment throws, you’re relying on it leaving the original unchanged. 
But this doesn’t affect the data structure as a whole and is entirely a property of the user-supplied type, 
so you can safely leave it up to the user to handle this.

*****/

/*****
    END OF FILE
**********/

