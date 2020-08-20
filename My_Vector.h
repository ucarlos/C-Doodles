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

template<class T, class A> struct my_vector_base{
    A alloc; // Allocator
    T* elem{nullptr}; // Start of allocation

    int sz{0};
    int space{0};
    
    // Default constructor
    my_vector_base()= default;
    
    my_vector_base(const A &a, int n): alloc{a}, elem{alloc.allocate(n)},
				    sz{n}, space{n} { }

    ~my_vector_base(){ alloc.deallocate(elem, space); }

};

template<class T, class A = std::allocator<T>>
class my_vector : private my_vector_base<T, A>{
public:
    // Default constructor
    my_vector(){
	    this->elem = nullptr;
	    this->sz = 0;
	    this->space = 0;
    }
    
    explicit my_vector(int size);
    
    my_vector(const my_vector&); // Copy constructor
    my_vector& operator=(const my_vector&); // Copy assignment

    my_vector(std::initializer_list<T> lst); // Initializer list constructor
    my_vector(my_vector&&) noexcept ; // Move constructor
    my_vector& operator=(my_vector&&) noexcept ; // Move assignment

    T& operator[](int n) { return this->elem[n]; }
    const T& operator[](int n) const { return this->elem[n]; }
    
    T& at(int n);
    int size() const { return this->sz; }
    int capacity() const { return this->space; }

    void resize(int new_size, T val = T());
    void push_back(const T& val);
    void reserve(int newalloc);
    
    // Destructor
    ~my_vector();
// private:
//     A alloc;
//     T *elem{nullptr};
//     int sz{0};
//     int space{0};

};

#endif
