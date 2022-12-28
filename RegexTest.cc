/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/17/2022 at 10:01 PM
 *
 * RegexTest.cc
 *
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <cstdint>

using std::cout;

void help() {
    cout << "Usage: ./RegexTest.cc [Regex Pattern] [Input File]\n";
    exit(EXIT_FAILURE);        
}


bool verify_regex_pattern(const std::string regex_string) {
    // std::regex regex_pattern;
    try {
        std::regex{regex_string};
    }
    catch (std::regex_error e) {
        return false;
    }
    
    return true;
}

bool is_file_empty(std::ifstream &input_file) {
    // Set the read pointer to the end:
    input_file.seekg(0, std::ios_base::end);
    std::streampos file_size = input_file.tellg();

    // Now set the read pointer back to normal:
    input_file.seekg(0);
    return (!file_size);
}

void process_file(std::ifstream &input_file, std::ofstream &output_file,
                  std::regex &regex, std::string &string_pattern) {

    std::int64_t line_count = 0;
    std::int64_t success_count = 0;

    output_file << "List of lines that fail " << string_pattern << ":\n";
    for (std::string line; std::getline(input_file, line); ) {
        line_count++;
        if (std::regex_match(line, regex))
            success_count++;
        else
            output_file << line << "\n";
    }


    double percentage = ((double)success_count / line_count) * 100;
    cout << "The regex_pattern " << string_pattern
         << " matches " << success_count << "/"
         << line_count << " (" << percentage << "%)\n";
}

int main(int argc, char *argv[]) {
    if (argc != 3)
        help();
    
    // Verify Regex pattern
    std::string regex_pattern = argv[1];
    if (!verify_regex_pattern(regex_pattern)) {
        std::cerr << "Error: " << regex_pattern << " is not a valid regex pattern.\n";
        exit(EXIT_FAILURE);
    }

    std::string filename = argv[2];
    std::ifstream input_file{filename, std::ios_base::in};
    if (!input_file) {
        std::cerr << "Error: \"" << filename << "\" does not exist. Aborting.\n";
        exit(EXIT_FAILURE);
    }

    // Check if input_file is empty; Abort if empty:
    if (is_file_empty(input_file)) {
        std::cerr << "Error: \"" << filename << "\" is empty. Aborting.\n";
        exit(EXIT_FAILURE);
    }
    
    // Clip out the file extension:
    auto last_dot_position = filename.rfind(".");  
    std::string output_filename = filename + "_error";
    if (last_dot_position != std::string::npos) {
        std::string extension = filename.substr(last_dot_position + 1);
        output_filename = filename.substr(0, last_dot_position) + "_error" + "." + extension;
    }

    std::ofstream output_file{output_filename, std::ios_base::out};
    if (!output_file) {
        std::cerr << "Error: Cannot create \"" << output_filename << "\n";
        exit(EXIT_FAILURE);
    }
 
    
    std::regex regex{regex_pattern};
    process_file(input_file, output_file, regex, regex_pattern);
}
