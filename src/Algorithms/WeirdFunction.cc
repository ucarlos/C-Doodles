/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 05/26/2021 at 08:49 PM
 *
 * WeirdFunction.cc
 * Make a function that takes a list of objects and return a new list
 * containing one of the attributes (ID) from each.
 * -----------------------------------------------------------------------------
 */


#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// Make a base class that can be inherited from or whatever:

struct Base {
    string first_name{"Ulysses"};
    string last_name{"Carlos"};

    Base() =default;
    Base(string fn, string ln) : first_name{fn}, last_name{fn} { }

};

template<class T> class Derived : public Base {
public:
    Derived()=default;

    Derived(T val) : special{val} { }
    T get_special() { return special; }
    void set_special(T val) { special = val; }

private:
    T special{};
    

};


const vector<string> generate_list(vector<Base> &vec) {
    vector<string> string_vec;

    for (const Base i : vec)
        string_vec.push_back(i.first_name);

    return string_vec;
}


int main(void) {
    vector<Base> base_vec;

    // Set up Random generator:
    srand(time(nullptr));
    

    // Now add some base classes into base_vec;
    for (int i = 0; i < 10; i++) {
        Derived<double> d = (1.02) * (rand() % 1000) + 1;
        base_vec.push_back(d);
    }

    string temp = "Example";
    for (int i = 0; i < 10; i++) {
        Derived<string> s = temp + "1";
        s.first_name += s.get_special();
        base_vec.push_back(s);
    }

    for (int i = 0; i < 10; i++) {
        Derived<int *> ip = nullptr;
        base_vec.push_back(ip);
    }

    // Now regardless of the Derived class, get the resultant:
    vector<string> vec = generate_list(base_vec);
    cout << "Size of Resultant vector: " << vec.size() << "\n";
    cout << "Output:\n";
    
    for (string i : vec)
        cout << i << endl;
    
}
