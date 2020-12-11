/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 08/16/2020 at 08:32 PM
 * 
 * My_Vector.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include "./My_Vector.h"


//------------------------------------------------------------------------------
// Vector Constructors
//------------------------------------------------------------------------------

// Copy constructor
template<class T, class A> my_vector<T, A>::my_vector(const my_vector<T, A> &vec){
    // get the size;
    T *p = new T[vec.sz];
    for (int i = 0; i < vec.sz; i++)
	p[i] = vec.elem[i];
    
    // Now delete old elem:
    delete[] elem;
    elem = p;
    this->space = this->sz = vec.sz;
}

// Copy assignment
template<class T, class A> my_vector<T, A>& my_vector<T, A>::operator=(const my_vector<T, A> &vec){
    if (this == &vec)
	return *this;

    if (vec.sz <= space){
	for (int i = 0; i < vec.sz; i++)
	    elem[i] = vec.elem[i];
	this->sz = vec.sz;
	return *this;
    }

    // Otherwise, if the sz is larger than the space,
    // allocate enough space, and then copy all data from vec
    // to the new elem.

    T *p = new T[vec.sz];
    for (int i = 0; i < vec.sz; i++)
	p[i] = vec.elem[i];

    delete[] elem; // Deallocate old space
    elem = p; // assign new pointer
    this->sz = this->space = vec.sz; // Set new size
    
    return *this; // Return a self-reference.
}

// Move constructor
template<class T, class A> my_vector<T, A>::my_vector(my_vector<T, A> &&vec){
    sz = vec.sz;
    space = vec.space;
    elem = vec.elem;

    // Now set sz and space to zero
    vec.sz = vec.space = 0;
    vec.elem = nullptr;
    
}

// Move assignment
template<class T, class A> my_vector<T, A>& my_vector<T, A>::operator=(my_vector<T, A> &&vec){
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
template<class T, class A> my_vector<T, A>::my_vector(std::initializer_list<T> lst){
    T *p = alloc.allocate(lst.size());
    this->space = this->sz = lst.size();
    
    auto it  = lst.begin();
    
    // for (unsigned int i = 0; i < lst.size(); i++)
    // 	elem[i] = *it++;
    for (unsigned int i = 0; i < lst.size(); i++)
	alloc.construct(&p[i], *it++);

    elem = p;
    
}

// Destructor
template<class T, class A> my_vector<T,A>::~my_vector(){
    //First destroy all elements:
    for (int i = 0; i <sz; i++)
	alloc.destroy(&elem[i]);

    // Now deallocate memory:
    for (int i = 0; i < space; i++)
	alloc.deallocate(&elem[i]);

}
//------------------------------------------------------------------------------
// My_Vector member functions
//------------------------------------------------------------------------------
template<class T, class A> void my_vector<T, A>::resize(int new_size, T val){
    // Let reserve handle causes where the new_size is less than space
    reserve(new_size);
    
    // Initialize all new elements
    // OLD:
    // for (int i = sz; i < space; i++)
    // 	elem[i] = 0;
    // Construct 
    for (int i = sz; i < new_size; i++)
	alloc.construct(&elem[i], val);

    sz = new_size;
}

template<class T, class A> T& my_vector<T, A>::at(int n){
    if (!(0 <= n && n < sz))
	throw std::runtime_error("Out of Range");
    
    return elem[n];
}

template<class T, class A> void my_vector<T, A>::push_back(const T &val){
    // Make sure that we have enough space
    if (!space)
	reserve(8); // Reserve eight blocks
    else if (sz == space)
	reserve(2 * space); // Double space if at capacity

    alloc.construct(&elem[sz], val);
    sz++;
    
}

template<class T, class A> void my_vector<T,A>::reserve(int newalloc){
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

// template<class T> void my_vector<T>::reserve(int newalloc){
//     if (newalloc <= space) return;

//     // Otherwise,
//     T *p = new T[newalloc];

//     // Copy all elements from elem
//     for (int i = 0; i < sz; i++)
// 	p[i] = elem[i];

//     // deallocate pointer
//     delete[] elem;
//     elem = p;
//     space = newalloc;
// }
