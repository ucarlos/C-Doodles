/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 08/16/2020 at 08:32 PM
 *
 * My_Vector.cc
 *
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "My_Vector.h"
using namespace std;

int main(){
	// Call Default Constructor:
    my_vector<double> test;

    // Call Size Constructor
    my_vector<double> test2(10);

    my_vector<double> test3 = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};

    test.push_back(12.1);
	test.resize(30, 10.2);

	// Now assign test2 to test:
	test = test2;

	// Now print the contents of test:
	cout << "Assigning test2 to test...\n\n";
	for (int i = 0; i < test.size(); i++){
		cout << "Index[" << i << "] : " << test.at(i) << endl;
	}

	// Now assign test3 to test:
	test = test3;
	cout << "Assigning test3 to test...\n\n";
	for (int i = 0; i < test.size(); i++)
		cout << "Index[" << i << "] : " << test.at(i) << "\n";
    //test.resize(120);

}
