/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/25/2021 at 06:33 PM
 * 
 * Mark_Example.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;


class Base {
public:
	Base() =default;
	Base(void *pp) : ptr{pp} { }
	virtual void* get_ptr() { return ptr; }
	virtual void set_ptr(void *new_ptr) { ptr = new_ptr; }
private:
	void *ptr{nullptr};

};

template<class T> class Derived : public Base {
public:
	Derived() = default;
	Derived(T *new_ptr) : type_ptr(new_ptr) { }
	void convert_to_void();
	const T& get_void_reference();
	const T* get_void_pointer();
private:
	T *type_ptr{nullptr};


};

template<class T> const T* Derived<T>::get_void_pointer() {
	return static_cast<T*>(get_ptr());
}

template<class T> const T& Derived<T>::get_void_reference() {
	// Should throw an exception if ptr is nullptr.
	auto ptr = get_ptr();
	if (ptr == nullptr) {
		throw runtime_error("Error: get_ptr() returned a null pointer.");
	}
	
	return *static_cast<T*>(ptr);
}

template<class T> void Derived<T>::convert_to_void() {
	set_ptr(static_cast<void*>(type_ptr));
}


int main(void) {
	vector<Base *> vec;
	
	int *iptr = new int{0x69420};
	double *dptr = new double {3.14};
	string *strptr = new string{"Hello World!"};
	
	// Now create instances of each class:
	Derived<int> d1{iptr};

	d1.convert_to_void();
	
	Derived<double> d2 = dptr;
	d2.convert_to_void();
	
	Derived<string> d3 = strptr;
	d3.convert_to_void();

	vec.push_back(&d1);	
	vec.push_back(&d2);
	vec.push_back(&d3);

	// Now do some operations:

	auto var1 = dynamic_cast<Derived<int>*>(vec[0]);
	auto result = var1->get_void_reference();
	cout << "Result: " << hex << showbase << result << endl;
	
	delete iptr;
	delete dptr;
	delete strptr;
}
