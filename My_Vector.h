/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 08/16/2020 at 08:05 PM
 * 
 * My_Vector.h
 * Implmenetation of vector, following the implementation from Bjarne
 * Stroustrup's "Programming: Principles and Practice Using C++"
 * 
 * -----------------------------------------------------------------------------
 */

#ifndef MY_VECTOR
#define MY_VECTOR
#include <initializer_list>
#include <memory>
#include <stdexcept>
template<class T, class A = std::allocator<T>> class my_vector{
public:
    // Default constructor
    my_vector(): elem{nullptr}, sz{0}, space{0} { }
    
    explicit my_vector(int s): elem{new T[s]}, sz{s}, space{s} {
	for (int i = 0; i < sz; i++) elem[i] = 0;
    }
    
    my_vector(const my_vector&); // Copy constructor
    my_vector& operator=(const my_vector&); // Copy assignment

    my_vector(std::initializer_list<T> lst); // Initializer list constructor
    my_vector(my_vector&&); // Move constructor
    my_vector& operator=(my_vector&&); // Move assignment

    T& operator[](int n) { return elem[n]; }
    const T& operator[](int n) const { return elem[n]; }
    
    T& at(int n);
    int size() const { return sz; }
    int capacity() const { return space; }

    void resize(int new_size, T val = T());
    void push_back(const T& val);
    void reserve(int newalloc);
    
    // Destructor
    ~my_vector();
private:
    A alloc;
    T *elem{nullptr};
    int sz{0};
    int space{0};

};

#endif
