/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 07/29/2023 at 06:25 PM
 *
 * HashMap.cc
 *
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main(void) {
    unordered_map<string, int> hashmap = {
        {"key1", 1},
        {"key2", 2},
        {"key3", 3},
        {"key4", 4}
    };

    for (std::pair<string, int> item : hashmap) {
        cout << item.first << "\t" << item.second << "\n";
    }
}
