/*****

References
    Juan Antonio Rufes - Asynchronous Programming with C++
    https://en.cppreference.com/cpp/thread/async
    
**********/

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <future>

using matrix_t = std::vector<std::vector<int>>;

auto display_matrix(const matrix_t &mt)
{
    const size_t l_rows = mt.size();
    if (l_rows)
    {
        const size_t l_cols = mt[0].size();
        std::cout << "Matrix rows: " << mt.size() << ", columns: " << mt[0].size() << ":\n";

        for (size_t i = 0; i < l_rows; ++i)
        {

            for (size_t j = 0; j < l_cols; ++j)
            {
                std::cout << mt[i][j] << ' ';
            }
            std::cout << '\n';
        }
    } else {
        std::cout << "Empty matrix\n";
    }
}

auto display_vec(const std::vector<int> &vec)
{
    for (const auto &elem : vec)
    {
        std::cout << elem << ' ';
    }
}

auto dot_product(const std::vector<int> &row,
                 const std::vector<int> &col)
{
    //std::cout << "Row: ";
    //display_vec(row);
    // std::cout << '\n';

    //std::cout << " Col: ";
    //display_vec(col);
    //std::cout << '\n';

    int res{0};
    for(size_t i = 0; i < row.size(); ++i) {
        res += (row[i] * col[i]);
    }

    return res;
}

auto matrix_mutiplication(const matrix_t &m1,
                          const matrix_t &m2,
                          matrix_t &outm)
{
    const size_t l_m1_r = m1.size();
    //const size_t l_m1_c = m1[0].size();
    //std::cout << "M1 Rows: " << l_m1_r << ", column: " << l_m1_c << '\n';

    const size_t l_m2_r = m2.size();
    const size_t l_m2_c = m2[0].size();
    //std::cout << "M2 Rows: " << l_m2_r << ", column: " << l_m2_c << '\n';

    outm.resize(l_m1_r);

    for (size_t i = 0; i < l_m1_r; ++i)
    {
        outm[i].resize(l_m2_c);

        const auto l_row = m1[i];

        for (size_t j = 0; j < l_m2_c; ++j)
        {
            std::vector<int> l_col(l_m2_r);
            for (size_t k = 0; k < l_m2_r; ++k)
            {
                l_col[k] = m2[k][j];
            }

            outm[i][j] = dot_product(l_row, l_col);
        }
    }
}

auto async_matrix_mutiplication(const matrix_t &m1,
                          const matrix_t &m2,
                          matrix_t &outm)
{
    const size_t l_m1_r = m1.size();
    //const size_t l_m1_c = m1[0].size();
    //std::cout << "M1 Rows: " << l_m1_r << ", column: " << l_m1_c << '\n';

    const size_t l_m2_r = m2.size();
    const size_t l_m2_c = m2[0].size();
    //std::cout << "M2 Rows: " << l_m2_r << ", column: " << l_m2_c << '\n';

    std::vector<std::future<int>>   l_futs;
    outm.resize(l_m1_r);
    for (size_t i = 0; i < l_m1_r; ++i)
    {
        outm[i].resize(l_m2_c);

        const auto l_row = m1[i];

        for (size_t j = 0; j < l_m2_c; ++j)
        {
            std::vector<int> l_col(l_m2_r);
            for (size_t k = 0; k < l_m2_r; ++k)
            {
                l_col[k] = m2[k][j];
            }

            //outm[i][j] = dot_product(l_row, l_col);
            l_futs.push_back(
                std::async(std::launch::async, dot_product, l_row, l_col)
            );
        }
    }

    for(size_t i = 0; i < l_m1_r; ++i) {
        for(size_t j = 0; j < l_m2_c; ++j) {
            outm[i][j] = l_futs[(i * l_m2_c) + j].get();
        }
    }
}

int main()
{
    matrix_t l_m1{
        {11, 12, 13},
        {14, 15, 16},
        {17, 18, 19},
        {21, 22, 23}};
    std::cout << "Rows: " << l_m1.size() << ", column: " << l_m1[0].size() << '\n';

    matrix_t l_m2{
        {21, 22, 23},
        {24, 25, 26},
        {27, 28, 29}};
    std::cout << "Rows: " << l_m2.size() << ", column: " << l_m2[0].size() << '\n';

    display_matrix(l_m1);
    std::cout << '\n';
    
    display_matrix(l_m2);
    std::cout << '\n';

    {
        matrix_t l_m;
        //const auto l_start_time = std::chrono::high_resolution_clock::now();
        matrix_mutiplication(l_m1, l_m2, l_m);
        //const auto l_end_time = std::chrono::high_resolution_clock::now();

        //const auto l_dur = std::chrono::duration_cast<std::chrono::nanoseconds>(l_end_time - l_start_time);
        //std::cout << "Time taken " << l_dur.count() << " nanoseconds\n";

        display_matrix(l_m);
        std::cout << '\n';
    }

    {
        matrix_t l_m;
        //const auto l_start_time = std::chrono::high_resolution_clock::now();
        async_matrix_mutiplication(l_m1, l_m2, l_m);
        //const auto l_end_time = std::chrono::high_resolution_clock::now();

        //const auto l_dur = std::chrono::duration_cast<std::chrono::nanoseconds>(l_end_time - l_start_time);
        //std::cout << "Time taken " << l_dur.count() << " nanoseconds\n";

        
        display_matrix(l_m);
        std::cout << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/
