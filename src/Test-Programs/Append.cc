/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 04/10/2021 at 09:28 PM
 * 
 * Append.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(void) {
	string filename = "./Input.txt";
	
	fstream fs {filename, ios_base::in | ios_base::app};
	if (!fs) {
		cerr << "The file \"" << filename << "\" does not exist. Exiting.\n";
		exit(EXIT_FAILURE);
	}
	
	fs << endl << "Your father smells of elderberries!" << endl;
	fs.seekp(0, ios_base::beg);
	
	// Now output the entire file to stdout:
	for (string temp; fs.good(); ) {
		getline(fs, temp);
		cout << temp << endl;
	}

	cout << "Complete!" << endl;

}

