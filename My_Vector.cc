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

// Normal constructor:
template<class T, class A> my_vector<T,A>::my_vector(int size){
    // Just call resize
    resize(size);
}

// Copy constructor
template<class T, class A> my_vector<T, A>::my_vector(const my_vector<T, A> &vec){
    // get the size;
    this->my_vector_base<T,A>::my_vector_base(this->alloc, vec.sz);
    
    // Now copy all the data:
    for (int i = 0; i < vec.sz; i++)
	this->alloc.construct(&this->elem[i], vec.elem[i]);
    
    // Now delete old elem:

    this->space = this->sz = vec.sz;
}

// Copy assignment
template<class T, class A> my_vector<T, A>& my_vector<T, A>::operator=(const my_vector<T, A> &vec){
    if (this == &vec)
	return *this;

    // If size of vec is smaller than space, destroy the current space and then
    if (vec.sz <= this->space){ // 
	// First, destroy elem:
	for (int i = 0; i < this->sz; i++)
	    this->alloc.destroy(&this->elem[i]);
		
	for (int i = 0; i < vec.sz; i++)
	    this->alloc.construct(&this->elem[i], vec.elem[i]);

	this->sz = vec.sz;
	return *this;
	
    }

    // Otherwise, if the sz is larger than the space,
    // allocate enough space, and then copy all data from vec
    // to the new elem.

    my_vector_base<T,A> b(this->alloc, vec.sz);
    std::uninitialized_copy(vec.elem, &vec.elem[vec.sz], b.elem);

    for (int i = 0; i < this->sz; i++)
	this->alloc.destroy(&this->elem[i]);

    // Now swap representations:
    std::swap<my_vector_base<T,A>>(*this, b);
    // T *p = new T[vec.sz];
    // for (int i = 0; i < vec.sz; i++)
    // 	p[i] = vec.elem[i];

    // delete[] elem; // Deallocate old space
    // elem = p; // assign new pointer
    
    
    this->sz = this->space = vec.sz; // Set new size
    
    return *this; // Return a self-reference.
}

// Move constructor
template<class T, class A> my_vector<T, A>::my_vector(my_vector<T, A> &&vec) noexcept{
    this->sz = vec.sz;
    this->space = vec.space;
    this->elem = vec.elem;

    // Now set sz and space to zero
    vec.sz = vec.space = 0;
    vec.elem = nullptr;
    
}

// Move assignment
template<class T, class A> my_vector<T, A>& my_vector<T, A>::operator=(my_vector<T, A> &&vec) noexcept{
    // Do nothing if vec is the same as this
    if (this == &vec)
	return *this;
    
    for (int i = 0; i < this->sz; i++)
	this->alloc.destroy(&this->elem[i]);

    for (int i = 0; i < this->space; i++)
	this->alloc.deallocate(&this->elem[i]);
    
    this->elem = vec.elem;
    this->sz = vec.sz;
    this->space = vec.space;

    vec.sz = vec.space = 0;
    vec.elem = nullptr;
    return *this;
}

// Initializer_list constructor
template<class T, class A> my_vector<T, A>::my_vector(std::initializer_list<T> lst){
    T *p = this->alloc.allocate(lst.size());
    this->space = this->sz = lst.size();
    
    auto it  = lst.begin();
    
    // for (unsigned int i = 0; i < lst.size(); i++)
    // 	elem[i] = *it++;
    for (unsigned int i = 0; i < lst.size(); i++)
	this->alloc.construct(&p[i], *it++);

    this->elem = p;
    
}

// Destructor
template<class T, class A> my_vector<T,A>::~my_vector(){
    //First destroy all elements:
    for (int i = 0; i < this->sz; i++)
	this->alloc.destroy(this->elem[i]);

    // Now call vector_base's deconstructor:
    // this->my_vector_base<T,A>::~my_vector_base();
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
    for (int i = this->sz; i < new_size; i++)
	this->alloc.construct(&this->elem[i], val);

    this->sz = new_size;
}

template<class T, class A> T& my_vector<T, A>::at(int n){
    if (!(0 <= n && n < this->sz))
	throw std::runtime_error("Out of Range");
    
    return this->elem[n];
}

template<class T, class A> void my_vector<T, A>::push_back(const T &val){
    // Make sure that we have enough space
    if (!this->space)
	reserve(8); // Reserve eight blocks
    else if (this->sz == this->space)
	reserve(2 * this->space); // Double space if at capacity

    this->alloc.construct(&this->elem[this->sz], val);
    this->sz++;
    
}

template<class T, class A> void my_vector<T,A>::reserve(int newalloc){
    if (newalloc <= this->space) return; // Never decrease allocation

    // Allocate new memory

    my_vector_base<T, A> b(this->alloc, newalloc); // Allocate new space

    // This might be wrong.
    // std::uninitialized_copy(b.elem, &b.elem[this->sz], this->elem);
    
    std::uninitialized_copy(this->elem, this->elem[this->sz], b.elem);
    
    for (int i = 0; i < this->sz; i++)
	this->alloc.destroy(&this->elem[i]); // Destroy old

    std::swap<my_vector_base<T,A>>(*this, b); // Swap representations
    

    
    // T *p = alloc.allocate(newalloc);
    // // construct
    // for (int i = 0; i < sz; i++)
    // 	alloc.construct(&p[i], elem[i]);
    // // Deconstruct old memory
    // for (int i = 0; i < sz; i++)
    // 	alloc.destroy(&elem[i]);
    // // Deallocate old memory
    // alloc.deallocate(elem, space);
    
    // elem = p;
    // space = newalloc;

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
