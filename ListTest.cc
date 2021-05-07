/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 05/04/2021 at 11:35 PM
 * 
 * ListTest.cc
 * 
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <list>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int MAX_SIZE = 100;

void populate_list(list<int> &lst) {
	// populate random generator:
	srand(time(NULL));

	for (int i = 0; i < MAX_SIZE; i++)
		lst.push_back((rand() % MAX_SIZE) + 1);
}

// T must be an input iterator:
template<class T> void print_range(T begin, T end) {
	long count{0};

	cout << setw(3);
	while (begin != end) {
		count++;
		cout << *begin;
		
		if (!(count % 10))
			cout << endl;
		else cout << " ";

		begin++;
	}

}

int main(void) {
	list<int> lst;
	populate_list(lst);


	cout << "Before Sorting: \n";
	print_range(lst.begin(), lst.end());

	
	cout << "After Sorting: " << endl;
	lst.sort();
	print_range(lst.begin(), lst.end());

}
