/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 08/23/2023 at 10:36 PM
 *
 * FileLogger.hpp
 * Simple File logger class.
 * ------------------------------------------------------------------------------
 */

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>

const std::string DEFAULT_LOG_FILE_LOCATION = "DefaultLogFile.txt";

class FileLogger {
public:
	FileLogger() =default;

    FileLogger(const std::string filename) : _filename{filename} {
        _logger = spdlog::basic_logger_mt("file_logger", filename);
    }

    FileLogger(const std::filesystem::path file_path) : _filename{file_path.string()} {
        _logger = spdlog::basic_logger_mt("file_logger", _filename);
    }

    std::shared_ptr<spdlog::logger>& logger() { return this->_logger; }


private:
    std::string _filename;
    std::shared_ptr<spdlog::logger> _logger = spdlog::basic_logger_mt("file_logger",
                                                                      std::filesystem::current_path() / DEFAULT_LOG_FILE_LOCATION);
};
