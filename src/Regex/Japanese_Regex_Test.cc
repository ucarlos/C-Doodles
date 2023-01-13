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
#include <vector>
#include <regex>
using namespace std;


int main(void) {
    const string japanese_pattern = R"([一-龠]+|[ぁ-ゔ]+|[ァ-ヴー]+|[々〆〤ヶ]+)";
    std::regex pattern{japanese_pattern};

    std::smatch string_match;
    const string test = "それは何も持っていませんExample1あなたが正しいExample2なんて混乱";

    bool result = regex_search(test, string_match, pattern);

    cout << "Match size: " << string_match.size() << "\n"
         << "Match: " << string_match.str() << "\n";

}
