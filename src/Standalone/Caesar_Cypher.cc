/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/21/2020 at 02:33 PM
 * 
 * Cesear_Cypher.cc
 * An example of an Caesar cypher to work with.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <cstdint>
#include <cctype>
#include <cmath>
using namespace std;

std::string shift_string(const string &s, const int16_t shift){
    // If shift is zero, return immediately.
    if (!shift) return s;
    
    std::string result = s;
    int16_t adjusted_shift;
    char temp;
    
    for (char &i : result){
        if (!isalpha(i)) continue;
    
        temp = tolower(i);

        // Optimized (I think) version of code below:
        // If the shifted character is outside the range ['a' : 'z'],
        // Then loop around it and decrease/increase the shift
        // depending on the circumstance
        adjusted_shift = ((temp + shift) < 'a') ? ('a' - (temp + shift + 1))
                                            : ((temp + shift) > 'z') ? (temp + shift - 'z' - 1)
                                                                     : shift;

        temp = (adjusted_shift == shift) ? temp + shift
                                         : ((shift < 0) ? ('z' - adjusted_shift)
                                                        : ('a' + adjusted_shift));

        // Same logic, but easier to understand:
        // if (shift < 0){
        //     adjusted_shift = ((temp + shift) < 'a') ? ('a' - (temp + shift + 1))
        //  : shift;
        
        //     temp = (adjusted_shift == shift) ? temp + shift
        //  : 'z' - adjusted_shift;
                           
        // }
        // else{
        //     adjusted_shift = ((temp+ shift) > 'z') ? (temp + shift - 'z' - 1)
        //  : shift;
        
        //     temp = (adjusted_shift == shift) ? temp + shift
        //  : 'a' + adjusted_shift;
        // }
    
        // Now readjust according to case
        i = (isupper(i)) ? toupper(temp) : temp;
    
    }
    
    return result;
}

int main(void){
    string input;
    int16_t max_shift = 26;
    int16_t shift;
    
    cout << "Please enter a phrase to encrypt using a Caesar Cypher:\n";
    getline(cin, input);
    cout << "Shift by how many characters?" << endl;
    cin >> shift;
    
    // If shift is outside [-26 : 26], then absolute it and do modulus:
    int32_t absolute = abs(shift);
    
    if (absolute > max_shift){
        shift = (shift < 0) ? -1 * (absolute % max_shift)
                            : (absolute % max_shift);
    
        cerr << "Warning: Shift is outside range [-26: 26]. Readjusting to "
             << shift << endl << endl;
    }
    
    cout << "Original Phrase: " << input << "\n";
    cout << "Shifted Phrase: " << shift_string(input, shift) << endl;
    
}
