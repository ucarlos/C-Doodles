/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/11/2023 at 08:31 PM
 *
 * SelfReproduced.cc
 *
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>

using std::cout, std::cerr, std::ifstream, std::string;


int main(void) {

	ifstream input_file{"./SelfReproduced.cc", std::ios_base::in};
	if (!input_file) {
		cerr << "Error: Could not open \"SelfReproduced.cc\". Aborting.\n";
		exit(EXIT_FAILURE);
	}
	

	string line;
	while (std::getline(input_file, line)) {
		cout << line << "\n";
	}
}

	


