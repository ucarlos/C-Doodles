/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 04/19/2021 at 12:09 AM
 * 
 * Map.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;


int main(void) {
    map<int, string> mapper;
    ostringstream os;
    os << showbase << hex;

    for (int i = 0; i < 100; i++) {
        string temp;
        os.str(temp);
        os << "{ Hexadecimal: " << i << " }";
        mapper.insert({i, os.str()});
    }

    cout << "Printing contents of Mapper: " << endl;
    for (map<int, string>::iterator it = mapper.begin(); it != mapper.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }




}
