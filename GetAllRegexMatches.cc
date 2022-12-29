/*
 * -------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 12/28/2022 at 03:08 PM
 *
 * GetAllRegexMatches.cc
 *
 * -------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <regex>
#include <unistd.h>
#include <vector>
using namespace std;

enum class mode { NORMAL = 0, DEBUG_MODE, INTERACTIVE_MODE, TEST_MODE };
const mode MODE = mode::NORMAL;

vector<string> get_all_regex_matches(string regex_pattern, string searched_string) {
    vector<string> search_vector;
    
    if (regex_pattern.empty() || searched_string.empty())
        return search_vector;
        
    std::regex regex;

    // If there's a problem with the regex, return an empty vector.
    try {
        regex = std::regex{regex_pattern};
    }
    catch (regex_error &error) {
        return search_vector;
    }

    auto first = searched_string.begin();
    auto end = searched_string.end();

    std::match_results<std::string::iterator> string_match;
        
    while (first < end) {
        // string substring = searched_string.substr((first - searched_string.begin()), searched_string.length() - 1);

        bool result = regex_search(first, end, string_match, regex);
        if (!result)
            break;

        // Insert the match into the vector, and clear the string match.
        search_vector.push_back(string_match.str());
        // auto length = string_match.length();
        // auto match = string_match.str();
        first = string_match.suffix().first;
    }

    return search_vector;
}


void interactive_mode() {
    string pattern_string, search_string;
    cout << "Please enter the regex pattern to use: ";
    cin >> pattern_string;
    cout << "Now enter the string to search for the regex pattern: ";
    cin >> search_string;
    

    vector<string> match_vector = get_all_regex_matches(pattern_string, search_string);
    if (match_vector.empty()) {
        cout << "No matches were found in " << search_string << " using the regex pattern.\n";
    }
    else {
        cout << match_vector.size() << "match(es) were found:\n";
        for (const string &sub_match: match_vector)
            cout << "\t" << sub_match << "\n";
    }
    

}

void debug_mode() {
    const string japanese_pattern = R"([一-龠]+|[ぁ-ゔ]+|[ァ-ヴー]+|[々〆〤ヶ]+)";
    std::regex pattern{japanese_pattern};

    std::smatch string_match;
    const string test = "普段は生意気ExampleだけどクリスマスにHelloWorld夜這いする妹";
    
    bool result = regex_search(test, string_match, pattern);
    
    cout << "Match size: " << string_match.size() << "\n"
         << "Match: " << string_match.str() << "\n";


    vector<string> check = get_all_regex_matches(japanese_pattern, test);
    cout << "List of checks:\n";
    for (const string &str: check)
        cout << str << "\n";
}

void help() {
    cout << "Usage: ./GetAllRegexMatches.cc -r [Regex Pattern] [String]" << endl;   
}


int main(int argc, char *argv[]) {

    
    if (MODE == mode::DEBUG_MODE)
        cout << "Argument count: " << argc << endl;

    
    if (MODE == mode::TEST_MODE) {
        debug_mode();
        exit(EXIT_SUCCESS);
    }

    
    if (argc != 4) {
        help();
        exit(EXIT_SUCCESS);
    }

    int option;
    string regex_pattern;
    string searched_string;

    while ((option = getopt(argc, argv, "r:i")) != -1) {
        switch(option) {
        case 'r':
            regex_pattern = string{optarg};
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
    
