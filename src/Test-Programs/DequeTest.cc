/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 04/10/2023 at 08:02 PM
 *
 * DequeTest.cc
 *
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <deque>

using namespace std;
int main(void) {
	deque<int> int_deque;

	const int max_size = 40;
	std::cout << "Populating Deque with " << max_size << " value(s).\n";
	for (int i = 1; i <= max_size; i++) {
		if (!(i % 2))
			int_deque.push_front(i);
		else
			int_deque.push_back(i);
	}

	std::cout << "Now printing the Deque.\n";
	for (const int i : int_deque)
		cout << i << " ";
	cout << "\n";

}
