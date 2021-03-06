/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/05/2021 at 10:04 PM
 * 
 * Disjoint.cc
 * Develop a Disjoint algorithm for three vectors.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// Let's give the example three groups:
// group1 = [1, 2, 3, 4, 5, 6]
// group2 = [7, 6, 8, 9, 10, 11]
// group3 = [2, 4, 6, 10, -2, -4]
// 6 is the key in all of them:

template<class T> bool disjoint(vector<T> &group1,
								vector<T> &group2,
								vector<T> &group3) {


	sort(group2.begin(), group2.end());
	sort(group3.begin(), group3.end());
	
	for (const auto &i : group1) {
		// auto find2  = find(group2.begin(), group2.end(), i);
		// auto find3 = find(group3.begin(), group3.end(), i);
		auto find2 = binary_search(group2.begin(), group2.end(), i);
		
		if (!find2) continue;
		auto find3 = binary_search(group3.begin(), group3.end(), i);
		
		// bool check = (find2 != group2.end()) and (find3 != group3.end());
		bool check = find2 && find3;
		if (check)
			return false; 
	}

	return true;
}

			  
int main(void) {
	vector<int> vec1 = {1, 2, 3, 4, 5};
	vector<int> vec2 = {7, 5, 6, -3, -9, 14, 10};
	vector<int> vec3 = {12, 9, 6, 3, 6, 10, -3, -6};

	bool result = disjoint(vec1, vec2, vec3);
	cout << "Is this set of three vectors disjoint? " << boolalpha << result << "\n";


}
