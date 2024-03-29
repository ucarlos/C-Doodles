/*
 * -------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 12/28/2022 at 03:08 PM
 *
 * GetAllRegexMatches.cc
 * An interactive program to retrieve all matches of a regex pattern in a given
 * source file.
 *
 * NOTE: If using g++, compile with -lfmt to get spdlog to work.
 * -------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <regex>
#include <unistd.h>
#include "../Logger.hpp"
#include <vector>

using namespace std;

enum class mode { NORMAL = 0, DEBUG_MODE };
const mode MODE = mode::DEBUG_MODE;
Logger logger{};

/**
 * Given a regex pattern and a string to apply the pattern to, return a vector
 * containing all regex matches found.
 *
 * @param regex_pattern String containing the regex pattern to use.
 * @param searched_string String that the regex pattern is applied on.
 *
 * @returns A vector containing all regex matches found. If either the regex pattern or
 *          string is empty, or if the regex pattern is invalid, an empty vector is returned.
 */
vector<string> get_all_regex_matches(const string &regex_pattern, const string &searched_string) {
    vector<string> search_vector;
    
    if (regex_pattern.empty() || searched_string.empty()) {
        logger.debug("get_all_regex_matches(): Regex Pattern or Search String is empty.");
        return search_vector;
    }
        
    std::regex regex{};

    // if there's a problem with the regex, return an empty vector.
    try {
        regex = std::regex{regex_pattern};
    }
    catch (regex_error &error) {
        logger.error("get_all_regex_matches(): " + regex_pattern + " is an invalid regex pattern.");
        return search_vector;
    }
    
    auto first = searched_string.begin();
    auto last = searched_string.end();

    std::match_results<std::string::const_iterator> string_match;
    
    while (first < last) {
        bool result = regex_search(first, last, string_match, regex);
        if (!result)
            break;
        
        // insert the match into the vector, and clear the string match.
        logger.debug("get_all_regex_matches(): appending " + string_match.str());
        search_vector.push_back(string_match.str());
        first = string_match.suffix().first;
    }

    return search_vector;
}

void interactive_mode() {
    // Note to self: If you ever mix cin and getline, you'll end up with some whitespace
    // characters that have to be consumed. You can do that by doing cin.get().

    string pattern_string, search_string;
    cout << "Please enter the regex pattern to use: ";
    getline(cin, pattern_string);
    cout << "Now enter the string to search for the regex pattern: ";
    getline(cin, search_string);
    

    vector<string> match_vector = get_all_regex_matches(pattern_string, search_string);
    if (match_vector.empty()) {
        cout << "No matches were found in " << search_string << " using the regex pattern.\n";
    }
    else {
        size_t matches = match_vector.size();
        if (matches == 1)
            cout << matches << " match was found:\n";
        else
            cout << matches << " matches were found:\n";

        for (const string &sub_match: match_vector)
            cout << "\t" << sub_match << "\n";
    }

}

void help() {
    cout << "Usage: ./GetAllRegexMatches.cc -r [Regex Pattern] [String]" << endl;
    cout << "                               -i\n";
}

int main(int argc, char *argv[]) {
    if (MODE == mode::DEBUG_MODE)
        logger.logger().set_level(spdlog::level::debug);
    else
        logger.logger().set_level(spdlog::level::off);


    if (!(argc == 2 || argc == 4)) {
        help();
        exit(EXIT_SUCCESS);
    }

    int option;
    string regex_pattern;
    string searched_string;

    while ((option = getopt(argc, argv, "r:i")) != -1) {
        switch (option) {
        case 'r':
            regex_pattern = std::string{optarg};
            break;
        case 'i':
            interactive_mode();
            exit(EXIT_SUCCESS);
        default:
            help();
            exit(EXIT_SUCCESS);
        }
    }

    if (optind > argc) {
        cerr << "Error: Expected a string argument after options.\n";
        exit(EXIT_FAILURE);
    }

    // Now attempt to grab the string:
    searched_string = argv[optind];
	vector<string> result = get_all_regex_matches(regex_pattern, searched_string);

    if (result.empty()) {
        cout << "No matches were found for " << searched_string << "using that regex pattern.\n";
    }
    else {
        size_t count = result.size();
        if (count < 2)
            cout << "1 match was found: \n";
        else
            cout << count << " matches were found: \n";
        for (const auto &string : result)
            cout << string << "\n";
    }
}
