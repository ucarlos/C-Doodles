/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 04/20/2021 at 02:30 PM
 * 
 * URLify_String.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
using namespace std;

void urlify_string(std::string &str) {
    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == ' ') {
            // Insert "20" into string:
            str.insert(i + 1, "20");
            str.at(i) = '%';
            i+= 2;         
        }
    }
}


int main(void) {
    std::string example = "Hello World! My Name is Ulysses!";
    cout << "Before: " << example << endl;
    urlify_string(example);
    cout << "After: " << example << endl;



}
