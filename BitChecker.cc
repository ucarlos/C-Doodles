/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 04/21/2021 at 01:28 PM
 * 
 * BitChecker.cc
 * :facepalm:
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <cstdint>
using namespace std;

int get_set_bits(unsigned char value) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		int temp = (value & (1 << i));
		if (temp)
			count++;
	}
	
	return count;
}

int get_set_bits(uint64_t val) {
	int count = 0;

	// Only set bit is the most significant bit
	uint64_t shift = 0x8000000000000000;
	size_t end = sizeof(uint64_t) * 8;

	// Check each bit starting from most significant to least significant
	for (size_t i = 0; i < end; i++, shift >>= 1) {
		uint64_t temp = (val & shift);
		if (temp)
			count++;
	}
	
	return count;

}

int main() {
	//unsigned char val = 0x71;
	uint64_t val;
	cout << "Please enter a value: ";
	cin >> val;
	// int result = get_set_bits(static_cast<uint64_t>(val));
	int result = get_set_bits(val);
	
	cout << "Number of set bits: " << result << endl;
}
