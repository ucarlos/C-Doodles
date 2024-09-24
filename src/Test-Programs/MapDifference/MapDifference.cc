/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 09/21/2024 at 11:18 PM
 *
 * TestHashMap.cc
 *
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include "Item.hpp"

using namespace std;

const int MAX_SIZE = 100000;

int main() {
    std::map<std::string, Item> initial_map = {};

    // NOTE: If you ever want to append to an ostringstream object after setting
    //       the string via ostringstream::str(), you need to set its mode to
    //       `ios_base::app` in its constructor.
    std::ostringstream output_stream{std::ios_base::app};

    std::chrono::time_point population_start = std::chrono::system_clock::now();


    for (int i = 0; i < MAX_SIZE; i++) {
        output_stream.clear();
        output_stream.str("example.item.");
        output_stream << std::setfill('0') << std::setw(8);
        output_stream << i;

        std::string key_name = output_stream.str();
        
        initial_map.insert({key_name, Item{key_name, "0", "Example Enterprise"}});
        initial_map.insert({key_name, Item{key_name, "1", "Example Enterprise"}});
    }
    

    std::map<std::string, Item> secondary_map = {};
    for (int i = 0; i < (MAX_SIZE >> 1); i++) {
        output_stream.str("example.item.");
        output_stream << i;

        std::string key_name = output_stream.str();
        
        secondary_map.insert({key_name, Item{key_name, "0", "Example Enterprise"}});
    }

    std::chrono::time_point population_end = std::chrono::system_clock::now();
    std::chrono::duration population_difference = population_end - population_start;

    std::map<std::string, Item> output_map = {};

    Item item1;
    Item item2;

    auto compare_item_function = [](const std::pair<const std::string, Item> &pair1,
        const std::pair<const std::string, Item> &pair2) {
        return pair1.first == pair2.first;
    };

    // Why the fuck does this work?
    // I still don't understand the std::inserter wrapper


    // Actually, according to ChatGPT:
    // In summary, std::inserter is essential when working with containers like std::set in algorithms like
    // std::set_difference, where elements need to be inserted, not overwritten, and the insertion must respect
    // the container's rules (such as order in a set).

    std::chrono::time_point algorithm_start = std::chrono::system_clock::now();
    std::set_difference(initial_map.begin(), initial_map.end(),
                        secondary_map.begin(), secondary_map.end(),
                        std::inserter(output_map, output_map.begin()), compare_item_function
    );

    std::chrono::time_point algorithm_end = std::chrono::system_clock::now();
    std::chrono::duration algorithm_difference = algorithm_end - algorithm_start;

    cout << "Populating both maps with " << MAX_SIZE << " items took "
         << population_difference.count() << "ns"
         << " (" << (std::chrono::duration_cast<std::chrono::milliseconds>(population_difference).count()) << "ms)\n";
        
    cout << "std::set_difference call took "
         << algorithm_difference.count() << "ns"
         << " (" << (std::chrono::duration_cast<std::chrono::milliseconds>(algorithm_difference).count()) << "ms)\n";
}
