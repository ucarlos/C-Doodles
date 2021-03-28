/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/08/2021 at 01:35 AM
 * 
 * Enum.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <map>
using namespace std;

enum class Weekday {Sunday = 0, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

int main() {
	Weekday weekday = Weekday::Friday;
	const map<Weekday, string> Map = {{Weekday::Sunday, "Sunday"},
									  {Weekday::Monday, "Monday"},
									  {Weekday::Tuesday, "Tuesday"},
									  {Weekday::Wednesday, "Wednesday"},
									  {Weekday::Thursday, "Thursday"},
									  {Weekday::Friday, "Friday"},
									  {Weekday::Saturday, "Saturday"}};
		
	cout << "Before: " << Map.at(weekday) << endl;
	// Now try assigning value:

}
