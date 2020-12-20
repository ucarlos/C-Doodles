/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 12/10/2020 at 03:34 PM
 * 
 * Integer_to_English.cc
 * Convert an integer into its English equivalent.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdint>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

/**
 * number_group_to_english
 *
 * @param str 
 */
std::string number_group_to_english(const std::string &str){
	if (str.empty())
		throw runtime_error("Error: Cannot have an empty string as parameter.");

	stringstream ss;
	uint32_t val;
	std::string new_str;
	// convert to integer:	
	ss.str(str);
	ss >> val;
	// Return empty string if val is zero
	if (!val)
		return new_str;
	
	const static std::map<uint32_t, string> ones = {{1, "one"},
													{2, "two"},
													{3, "three"},
													{4, "four"},
													{5, "five"},
													{6, "six"},
													{7, "seven"},
													{8, "eight"},
													{9, "nine"},
													{10, "ten"},
													{11, "eleven"},
													{12, "twelve"},
													{13, "thirteen"},
													{14, "fourteen"},
													{15, "fifteen"},
													{16, "sixteen"},
													{17, "seventeen"},
													{18, "eighteen"},
													{19, "nineteen"}};

	const static std::map<uint32_t, string> tens = {{2, "twenty"},
													{3, "thirty"},
													{4, "forty"},
													{5, "fifty"},
													{6, "sixty"},
													{7, "seventy"},
													{8, "eighty"},
													{9, "ninety"}};
	
	// Now try to determine value:
	uint32_t hundred_val = val / 100;
	uint32_t ten_remainder = val % 100;
	uint32_t ten_val = ten_remainder / 10;
	uint32_t one_val = val % 10;


	if (hundred_val)
		new_str += ones.at(hundred_val) + " hundred ";
	if (1 <= ten_remainder && ten_remainder < 20)
		return new_str + ones.at(ten_remainder);
	else if (ten_val) // If ten_val is not zero, append the tens place
		new_str += tens.at(ten_val) + " ";

	if (one_val) // Also append the ones place if it is not zero
		new_str += ones.at(one_val) + " ";
	
	return new_str;		
}


/**
 * integer_to_english: A program that converts a integer into its english word
 * representation. This is done by breaking the number into groups of three and
 * passing each group to number_group_to_english, applying the appropriate
 * group name (such as thousand, million, billion, etc).
 *
 * @param val contains an int64_t number to be parsed.
 */
std::string integer_to_english(const int64_t val){
	// The program breaks the number into groups of three, and then parses its
	// value and then adds the appropriate modifier. In order to consider the maximum
	// value of 2^63 - 1, the modifiers contain Quintilian, quadrillion, trillion,
	// billion, million, and thousand.
	// number_group_to_english handles parsing the number from 1 to 999, using maps.
	if (!val) return "zero";

	std::string str;
	// Now convert the entire value into a string and separate into groups of three,
	// Each representing a value.
	stringstream ss;
	ss << val;

	if (val < 0) {
		str += "negative ";
		// Remove the sign character.
		auto ss_str = ss.str();
		ss_str.erase(ss_str.begin());
		ss.str(ss_str);
	}

	int32_t digits = ss.str().length();
	int32_t max_groups = digits / 3;
	int32_t group_count = max_groups;
	int32_t remainder_digits = digits % 3;
	
	// static std::string number_name_list[] = {"thousand", "million", "billion", "trillion",
	// 	"quadrillion", "quintillion"};
	const static vector<string> number_name_list = { "thousand", "million", "billion",
		"trillion", "quadrillion", "quintillion"};
		
	// If the number of digits doesn't fit evenly into groups, parse the remainder digits.
	std::string group_str;
	if (remainder_digits) {
		group_str = ss.str().substr(0, remainder_digits);
		str += number_group_to_english(group_str);
		if (group_count > 0)
			str += " " + number_name_list[--group_count] + " ";
	}
	else // Otherwise make sure that the right name is outputted for the groups.
		group_count--;

	// Now apply for each group:
	for (int i = 0; i < max_groups; i++){
		group_str = ss.str().substr(remainder_digits + i * 3, 3);
		auto temp_str = number_group_to_english(group_str);
		if (!temp_str.empty()) {
			if (group_count > 0)
				str += temp_str + number_name_list[--group_count] + " ";
			else
				str += temp_str;
		}
	}

	return str;
}


int main(){
	int64_t val;
	cout << "Please enter a integer: ";
	cin >> val;
	cout << "English representation of " << val << ":\n"
		 << integer_to_english(val) << endl;

}
