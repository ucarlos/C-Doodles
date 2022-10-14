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

#pragma once
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <initializer_list>
#include <memory>
#include <stdexcept>

template<class T, class A = std::allocator<T>> class my_vector {
public:
    // Default constructor
    my_vector(): elem{nullptr}, sz{0}, space{0} { }
    
    explicit my_vector(int s);
    
    my_vector(const my_vector&); // Copy constructor
    my_vector& operator=(const my_vector&); // Copy assignment

    my_vector(std::initializer_list<T> lst); // Initializer list constructor
    my_vector(my_vector&&) noexcept ; // Move constructor
    my_vector& operator=(my_vector&&) noexcept; // Move assignment

    T& operator[](int n) { return elem[n]; }
    const T& operator[](int n) const { return elem[n]; }
    
    T& at(int n);
    [[nodiscard]] int size() const { return sz; }
    [[nodiscard]] int capacity() const { return space; }

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

//------------------------------------------------------------------------------
// Vector Constructors
//------------------------------------------------------------------------------

// Explicit Constructor
template<class T, class A> my_vector<T,A>::my_vector(int s) {
    // Call Resize by default
    resize(s);
}


/**
 *
 */
template<class T, class A> my_vector<T,A>::my_vector(const my_vector<T,A> &vec) {
    // Allocate the size of vec.size
    T *p = alloc.allocate(vec.size());

    // Now copy over the contents of vec:
    for (int i = 0; i < vec.size(); i++) {
        alloc.construct(&p[i], vec[i]);
    }

    sz = space = vec.size();
    elem = p;
}

template<class T, class A> my_vector<T, A>&
    my_vector<T,A>::operator=(const my_vector<T, A> &vec) {
    if (this == &vec)
        return *this;

    if (vec.sz <= this->space) {

        // If the size of vec is smaller than currently allocated space, then destroy
        // all current object and reconstruct from vec.

        for (int i = 0; i < this->sz; i++)
            this->alloc.destroy(&this->elem[i]);

        for (int i = 0; i < vec.sz; i++)
            this->alloc.construct(&this->elem[i], vec.elem[i]);

        // Set size:
        this->sz = vec.sz;
        return *this;
    }

    // Otherwise, if vec.sz is larger than space, allocate enough space and then copy all
    // data from vec to new elem.

    T *temp = alloc.allocate(vec.sz);

    for (int i = 0; i < vec.sz; i++) {
        alloc.construct(&temp[i], vec.elem[i]);
    }

    // Destroy and deallocate elem:
    for (int i = 0; i < this->sz; i++)
        alloc.destroy(&this->elem[i]);

    alloc.deallocate(this->elem, this->space);
    
    elem = temp;
    this->sz = this->space = vec.sz;
    
    return *this; // Return a self-reference.
    
}


// Move constructor
template<class T, class A> my_vector<T, A>::my_vector(my_vector<T, A> &&vec) noexcept {
    sz = vec.sz;
    space = vec.space;
    elem = vec.elem;

    // Now set sz and space to zero
    vec.sz = vec.space = 0;
    vec.elem = nullptr;

}

// Move assignment
template<class T, class A> my_vector<T, A>& my_vector<T, A>::operator=(my_vector<T, A> &&vec) noexcept {
    // Do nothing if vec is the same as this
    if (this == &vec)
        return *this;

    for (int i = 0; i < sz; i++)
        alloc.destroy(&elem[i]);

    for (int i = 0; i < space; i++)
        alloc.deallocate(&elem[i]);

    elem = vec.elem;
    sz = vec.sz;
    space = vec.space;

    vec.sz = vec.space = 0;
    vec.elem = nullptr;
    return *this;
}

// Initializer_list constructor
template<class T, class A> my_vector<T, A>::my_vector(std::initializer_list<T> lst) {
    T *p = alloc.allocate(lst.size());
    this->space = this->sz = lst.size();

    auto it  = lst.begin();

    // for (unsigned int i = 0; i < lst.size(); i++)
    //  elem[i] = *it++;
    for (unsigned int i = 0; i < lst.size(); i++)
        alloc.construct(&p[i], *it++);

    elem = p;

}

// Destructor
template<class T, class A> my_vector<T,A>::~my_vector() {
    // If elem is nullptr, do nothing
    if (elem != nullptr) {

        //First destroy all elements:
        for (int i = 0; i < sz; i++)
            alloc.destroy(&elem[i]);

        // Now deallocate memory:
        alloc.deallocate(elem, space);
    }
}

//------------------------------------------------------------------------------
// My_Vector member functions
//------------------------------------------------------------------------------
template<class T, class A> void my_vector<T, A>::resize(int new_size, T val) {
    // Let reserve handle causes where the new_size is less than space
    reserve(new_size);

    // Initialize all new elements
    // OLD:
    // for (int i = sz; i < space; i++)
    //  elem[i] = 0;
    // Construct

    for (int i = sz; i < new_size; i++)
        alloc.construct(&elem[i], val);

    sz = new_size;
}

template<class T, class A> T& my_vector<T, A>::at(int n) {
    if (!(0 <= n && n < sz))
        throw std::runtime_error("Out of Range");

    return elem[n];
}

template<class T, class A> void my_vector<T, A>::push_back(const T &val) {
    // Make sure that we have enough space
    if (!space)
        reserve(8); // Reserve eight blocks
    else if (sz == space)
        reserve(2 * space); // Double space if at capacity

    alloc.construct(&elem[sz], val);
    sz++;

}

template<class T, class A> void my_vector<T,A>::reserve(int newalloc) {
    if (newalloc <= space) return;

    // Allocate new memory
    T *p = alloc.allocate(newalloc);
    // construct
    for (int i = 0; i < sz; i++)
        alloc.construct(&p[i], elem[i]);
    // Deconstruct old memory
    for (int i = 0; i < sz; i++)
        alloc.destroy(&elem[i]);
    // Deallocate old memory
    alloc.deallocate(elem, space);

    elem = p;
    space = newalloc;

}

#endif
