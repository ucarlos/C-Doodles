/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 04/05/2022 at 03:01 PM
 *
 * Itoa.cc
 *
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <cstdint>
#include <string>
#include <sstream>

using namespace std;

/**
 * Convert an integer to its string representation.
 * @param value an signed integer.
 * @returns a string representation of the integer.
 */
string itoa(int32_t value) {
    const int MAX_INT_DIGIT_SIZE = 12;
    string temp_string;
    temp_string.reserve(MAX_INT_DIGIT_SIZE);

    for (int i = value; i > 0; i /= 10)
        temp_string.insert(temp_string.begin(), (i % 10) + '0');

    if (value < 0)
        temp_string.insert(temp_string.begin(), '-');

    return temp_string;
}

string simple_itoa(int32_t value) {
    ostringstream os;
    os << value;
    return os.str();
}

int main(void) {
    int32_t value;
    cout << "Please enter a value: ";
    cin >> value;

    cout << "Normal String: " << value;
    cout << "Calling itoa: " << itoa(value);
   
}









