/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/24/2021 at 10:25 PM
 * 
 * Split.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * @param str
 * @param delimiter
 */
vector<string> split(const string str, const string delimiter = " ") {
    vector<string> vec;

    // Any empty string will return an empty vector
    if (str.empty())
        return vec;

    if (delimiter.empty())
        throw runtime_error("Error: Cannot have an empty delimiter.");
    
    
    // Initially reserve 8 items:
    vec.reserve(8);
    
    std::size_t length = str.length();
    std::size_t delimiter_length = delimiter.length();
    for (std::size_t index = 0; index < length;) {
        auto result = str.find(delimiter, index);

        // Add the string to the vector if the delimiter is not found
        if (result == string::npos) {
            vec.push_back(str.substr(index, length));
            break;
        }
        
        vec.push_back(str.substr(index, (result - index)));
        index = (result + delimiter_length);
    }

    // Reclaim any extra allocated memory:
    vec.shrink_to_fit();
    return vec; 
}


void test(void) {
    // string example = "The quick brown fox jumps over the lazy dog";
    string example;
    string delimiter;

    cout << "String: ";
    getline(cin, example);
    cout << "Delimiter: ";
    getline(cin, delimiter);


    // cout << "String: " << example;
    // cout << "Delimiter: " << delimiter;
    
    vector<string> temp = split(example, delimiter);

    cout << "Contents of String:\n";
    cout << "[ ";
    for (const string &i : temp)
        cout << "\'" << i << "\' ";
    cout << "]\n";

}

int main (int argc, char *argv[]) { 
    if (argc < 2) {
        test();
    }
    else if (argc == 3) {
        string source_string = argv[1];
        string delimiter = argv[2];


        vector<string> split_list = split(source_string, delimiter);
        cout << "Contents of String:\n";
        cout << "[ ";
        for (const string &i : split_list)
            cout << "\'" << i << "\' ";
        cout << "]\n";
        
    }
    else {      
        cout << "Usage: \t./Split [Source String] [Delimiter]\n";
        cout << "You can also call the program with ./Split\n";
        exit(EXIT_FAILURE);
    }   
}
