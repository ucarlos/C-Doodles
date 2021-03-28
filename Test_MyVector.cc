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
    my_vector<double> test;
    test.push_back(12.1);
	test.resize(30, 10.2);

	for (int i = 0; i < test.size(); i++) {
		cout << "Index " << i << " " << test.at(i) << endl;
	}
    //test.resize(120);

}
