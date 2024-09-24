/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 04/21/2021 at 01:28 PM
 * 
 * BitChecker.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include <iostream>
using namespace std;

int get_set_bits(unsigned char value) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int temp = (value & (1 << i)) >> (8 - i);
        if (temp)
            count++;
    }
    
    return 0;
}


int main(void) {
    unsigned char val = 0xFF;
    cout << "Please enter a value: ";
    cin >> val;
    
    int result = get_set_bits(val);

    cout << "Number of set bits: " << result << endl;
}
