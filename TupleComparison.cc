/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 02/18/2022 at 7:00PM
 *
 * TupleComparison.cc
 *
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <set>
#include <tuple>
#include <algorithm>

using namespace std;
using Item = std::tuple<int, std::string, std::string>;

void dumb_example(const std::set<Item> &item_set, const int score) {
    auto compare = [&score = score](const Item &item) { return std::get<0>(item) > score; };

    // O(n)
    // auto iterator = find_if(item_set.begin(), item_set.end(), compare);

    // O(log(n))
    auto iterator = item_set.upper_bound(make_tuple(score, "", ""));
     
    // Consider the possibility that the score is either less than first or greater than last:
    if (iterator == item_set.begin() || iterator == item_set.end()) 
        iterator = (score > std::get<0>(*(--item_set.end()))) ? --item_set.end() : item_set.begin();
    
    cout << "First: " << std::get<0>(*iterator) << "\tSecond: " << std::get<1>(*iterator) << "\tThird: " << std::get<2>(*iterator) << "\n";
}

int main(void) {
    std::set<Item> item_set = { std::make_tuple(10, "Very Weak", "#d87093"),
                                std::make_tuple(15, "Weak", "#c06"),
                                std::make_tuple(30, "Medium", "#f60"),
                                std::make_tuple(40, "Strong", "#3c0"),
                                std::make_tuple(50, "Very Strong", "#ffa500") };

    for (const auto &item : item_set)
        cout << "First: " << std::get<0>(item) << "\tSecond: " << std::get<1>(item) << "\tThird: " << std::get<2>(item) << "\n";

    // Now display score:
    int score;
    cout << "Please enter a score: ";
    cin >> score;
    dumb_example(item_set, score);    
}
