/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/19/2021 at 10:33 PM
 * 
 * Bubble_Sort.cc
 * 
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
using namespace std;

void bubble_sort(vector<int> &vec) {
	int max_size = vec.size() - 1;
	int temp;
	
	for (int i = 1; i <= vec.size(); i++) {
		for (int j = max_size; j >= i; j--) {
			temp = vec.at(j);
			if (temp < vec.at(j - 1)) {
				int temp2 = vec.at(j - 1);
				vec.at(j - 1) = temp;
				vec.at(j) = temp2;
			}
			else {
				temp = vec.at(j - 1);
			}
				
		}

	}
	
}

void print_list(vector<int> &vec) {
	for (const auto &i : vec)
		cout << i << " ";
	cout << endl;

}

int main(void) {
	vector<int> list = {10, 9, 2, 1, 8, 7, 6, 5, 3, 5, 2};
	cout << "Before sorting: " << endl;
	print_list(list);
	bubble_sort(list);	
	cout << "After sorting: " << endl;
	print_list(list);
	


}

