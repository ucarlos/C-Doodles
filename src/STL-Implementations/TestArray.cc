/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 02/10/2024 at 12:39 PM
 *
 * Array.cc
 *
 * -----------------------------------------------------------------------------
 */

#include "Array.hpp"

int main() {
	// Array<int, 10> array1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	Array<int, 10> array1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	std::cout << "Listing values:\n";
	for (int &i: array1)
		std::cout << i << " ";
	std::cout << "\n";

}
