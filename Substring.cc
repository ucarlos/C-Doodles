/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 04/26/2021 at 12:39 PM
 * 
 * Substring.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <cstdint>
#include <string>
#include <cctype>
using namespace std;

/**
 * \brief Basically a shitty version of std::string::find.
 * Determine if a substring can be found in a given string, disregarding
 * case.
 *
 * @returns a boolean value determining if the substring was found or not.
 */
bool has_substring(const string &str, const string &substr) {
	const size_t size = substr.size();
	bool check;
	for (size_t i = 0; i < str.size(); i++) {
		// Prevent the string from searching out bounds for the substring.
		if ((i + size) >= str.size()) continue;
		
		check = true; // Awful check
		for (size_t j = 0; j < size; j++) {
			if (tolower(str.at(i + j)) != tolower(substr.at(j))) {
				check = false; break;
			}
		}

		if (!check)
			continue;
		else return true;
		
	}

	return false; // Substring was not found.

}


int main(void) {
	string example = "O brave new world, that has such people in it!";

	string substring = "world";
	cout << boolalpha;
	cout << "Is the substring \"" << substring << "\" in \"" << example << "\" ? : "
		 << has_substring(example, substring) << endl;

}
