/*
 * -------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 12/19/2022 at 09:18 PM
 *
 * Japanese_Regex_Test.cc
 *
 * -------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <regex>
#include <vector>
using namespace std;

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



int main(void) {
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
