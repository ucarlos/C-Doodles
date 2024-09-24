/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 05/16/2022 at 10:05 PM
 *
 * Remember.cc
 * I remember I was going to do some test because I forgot something in C++?
 * I dunno.
 * Oh wait, it was operator== i think
 * ------------------------------------------------------------------------------
 */

#include <iostream>
using namespace std;

struct A {
    int a_val;
    A() { }
};

class B : public A {
public:
    B() { }

    int get_b() { return b_val; }
    void set_b(int new_value) { b_val = new_value; }
    bool operator==(B b_object) { return this->b_val == b_object.get_b(); }
    
    B& operator=(B b_object) { this->b_val = b_object.get_b();  return *this; }
    
private:
    int b_val;
};

int main(void) {}
