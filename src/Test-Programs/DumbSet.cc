/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 02/18/2022 at 08:21 PM
 *
 * DumbSet.cc
 *
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <set>
#include <string>

using std::endl;
int main(void) {
    std::set<int> set;

    for (int i = 0; i < 10; i++)
        set.insert(i);
    
    // Now search for 12?
    int search = 4;
    auto iterator = set.upper_bound(search);

    if (iterator == set.end())
        std::cout << "There are no items in the set that are greater than " << search << endl;
    else
        std::cout << *iterator << " is the first item greater than " << search << endl;
}
