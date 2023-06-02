/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/execution

Chapter 22 Parallel STL Algorithms
    
    C++17 allow STL standard algorithms to run using multiple threads to deal with different elements in parallel.

22.5 Overview of Parallel Algorithms

Unmodified Parallel STL Algorithms lists the algorithms that are standardized to support parallel processing without any modification
-----------------------------------------------------------------------------------------------
Algorithms								Remark
-----------------------------------------------------------------------------------------------
find_end(), adjacent_find()
search(), search_n()					except with searcher
swap_ranges()
replace(), replace_if()
fill()
generate()
remove(), remove_if()
unique()
reverse()
rotate()
partition(), stable_partition()
sort(), stable_sort(), partial_sort()
is_sorted(), is_sorted_until()
nth_element()
inplace_merge()
is_heap(), is_heap_until()
min_element(), max_element(), min_max_element()
-----------------------------------------------------------------------------------------------



Modified Parallel STL Algorithms lists the algorithms that are standardized to support parallel processing with some modifications

-----------------------------------------------------------------------------------------------
Algorithms										Remark
-----------------------------------------------------------------------------------------------
for_each()										forward iterators and return type void
all_of(), any_of(), none_of()					forward iterators
for_each_n()									forward iterators
find(), find_if(), find_if_not()				forward iterators
find_first_of()									forward iterators
count(), count_if()								forward iterators
mismatch()										forward iterators
equal()											forward iterators
is_partitioned()								forward iterators
partial_sort_copy()								forward iterators
includes()										forward iterators
lexicographical_compare()						forward iterators
fill_n()										forward iterators
generate_n()									forward iterators
reverse_copy()									forward iterators
rotate_copy()									forward iterators
copy(), copy_n(), copy_if()						forward iterators
move()											forward iterators
transform()										forward iterators
replace_copy(), replace_copy_if()				forward iterators
remove_copy(), remove_copy_if()					forward iterators
unique_copy()									forward iterators
partition_copy()								forward iterators
merge()											forward iterators
set_union(), set_intersection()					forward iterators
set_difference(), set_symmetric_difference()	forward iterators
exclusive_scan(), inclusive_scan()				forward iterators
-----------------------------------------------------------------------------------------------


STL Algorithms Without Parallelization lists the algorithms that are don’t support parallel processing
-----------------------------------------------------------------------------------------------
Algorithms											Remark
-----------------------------------------------------------------------------------------------
accumulate(), inner_product(), partial_sum()		use reduce() and transform_reduce() instead
search() with searcher
copy_backward() move_backward()
sample(), shuffle()
partition_point()
lower_bound(), upper_bound(), equal_range()
binary_search()
is_permutation(), next_permutation(), prev_permutation()
push_heap(), pop_heap(), make_heap(), sort_heap()
-----------------------------------------------------------------------------------------------


for accumulate() and inner_product() 
new parallel algorithms
reduce() 
transform_reduce()
are provided with relaxed requirements

*************/

#include <iostream>
#include <vector>
#include <execution>
#include <algorithm>

int main() {


    return 0;
}

/**********
    END OF FILE
*************/


