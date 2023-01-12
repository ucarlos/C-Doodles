/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 11/15/2022 at 08:01 PM
 *
 * Encoding.cc
 * Basically, it's a small program that tries to accurately get the length of
 * a japanese string. 
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <locale>
#include <iomanip>
#include <codecvt>

using std::string;

int main(void) {
    std::string example = "しのづかあつと";

    std::string m_example = "123";

    std::cout << "--------------------------------------------------------------------------------" << "\n";
    std::cout << "Normal String: " << example << "\n";
    std::cout << "Example length: " << example.length() << "\n";

    // Now convert to a wstring:
    auto w_string = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>{}.from_bytes(example);
    
    std::cout << "--------------------------------------------------------------------------------" << "\n";
    std::cout << "Wide String length: " << w_string.size() << "\n";
    
}
