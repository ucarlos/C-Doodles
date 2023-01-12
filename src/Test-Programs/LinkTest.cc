/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 10/21/2021 at 10:09 PM
 *
 * LinkTest.cc
 *
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <cstdint>
#include <vector>
#include <list>
#include <random>
#include <chrono>


const std::int32_t MAX_SIZE = (1 << 24);
using distribution = std::uniform_int_distribution<std::int32_t>;

void populate_list(std::list<std::int32_t> &list, distribution &dist,
                   std::mt19937 &merse) {
    
    for (int32_t i = 0; i < MAX_SIZE; i++)
        list.push_back(dist(merse));
    
}

void populate_vector(std::vector<std::int32_t> &vec, distribution &dist,
                     std::mt19937 &merse) {

    // vec.reserve(MAX_SIZE);

    // for (int32_t &i : vec)
    //  i = dist(merse);

    for (int32_t i = 0; i < MAX_SIZE; i++)
        vec.push_back(dist(merse));
            
}

template<class T> uint64_t sum_container(T begin, T end) {
    uint64_t sum{0};

    while (begin != end) {
        sum += *begin++;
    }

    return sum;
}


int main() {
    std::random_device device;
    std::mt19937 merse_generator{device()};
    distribution dist{0, MAX_SIZE >> 8};

    std::list<std::int32_t> list;
    std::vector<std::int32_t> vector;

    auto start = std::chrono::system_clock::now();  
    populate_list(list, dist, merse_generator);
    auto end = std::chrono::system_clock::now();
    
    std::cout << "Populating a list with " << MAX_SIZE << " values took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    start = std::chrono::system_clock::now();
    populate_vector(vector, dist, merse_generator);
    end = std::chrono::system_clock::now();
    
    std::cout << "Populating a vector with " << MAX_SIZE << " values took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    start = std::chrono::system_clock::now();
    uint64_t list_sum = sum_container(list.begin(), list.end());
    end = std::chrono::system_clock::now();
    
    std::cout << "Summing a list with " << MAX_SIZE << " values took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" <<  std::endl;

    start = std::chrono::system_clock::now();   
    uint64_t vector_sum = sum_container(vector.begin(), vector.end());
    end = std::chrono::system_clock::now();

    
    std::cout << "Summing a vector with " << MAX_SIZE << " values took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;


    std::cout << "List total: " << list_sum << "\n"
              << "Vector total: " << vector_sum << "\n";
}
// 10:07:20?
