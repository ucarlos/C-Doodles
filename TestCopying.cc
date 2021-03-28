/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/17/2021 at 10:18 PM
 * 
 * TestCopying.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include <iostream>
using namespace std;

class Example {
public:
	Example() =default;
	Example(int v) : val{v} { }
	Example(int v, int *p) : val{v}, ptr{p} { }
	// Copy constructor:
	Example(Example &ex) { ptr = ex.ptr; val = ex.val; }
	
	
	// Copy assignment:
	Example& operator=(Example &ex);
	// ostream& operator<<(ostream &os);
private:
	int *ptr{nullptr};
	int val{};
	friend ostream& operator<<(ostream &os, Example &ex);
};

ostream& operator<<(ostream &os, Example &ex) {
	return os << "Value: " << ex.val << "\tPtr: " << ex.ptr;
}


// Implementation of Copy Assignment operator:
Example& Example::operator=(Example &ex) {
	val = ex.val;
	ptr = ex.ptr;	
	return *this;
}


int main(void) {
	int *ptr = new int;
	
	Example ex1{10, ptr};
	Example ex2;
	ex2 = ex1;
	cout << ex1 << endl;
	cout << ex2 << endl;

	
	delete ptr; // Make sure to delete it 
   
}
