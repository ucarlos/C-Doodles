/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 08/23/2023 at 10:54 PM
 *
 * Logger.hpp
 * A simple logger class that wraps around spdlog.
 * ------------------------------------------------------------------------------
 */


#ifndef LOGGER_H
#define LOGGER_H

#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/details/log_msg.h>
#include <spdlog/sinks/ansicolor_sink.h>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>

class Logger {
public:
    Logger() = default;
    explicit Logger(std::string logger_name) : _logger_name{std::move(logger_name)} { }
    spdlog::sinks::ansicolor_stderr_sink<spdlog::details::console_mutex>& logger() const { return *_logger; }

    void debug(const std::string &message) {
        if (!log_level_is_at_least(spdlog::level::debug))
            return;

        this->_log_message = spdlog::details::log_msg{this->_logger_name, spdlog::level::debug, message};
        this->_logger->log(_log_message);
    }

    void info(const std::string &message) {
        if (!log_level_is_at_least(spdlog::level::info))
            return;

        this->_log_message = spdlog::details::log_msg{this->_logger_name, spdlog::level::info, message};
        this->_logger->log(this->_log_message);
    }

    void error(const std::string &message) {
        if (!log_level_is_at_least(spdlog::level::err))
            return;

        this->_log_message = spdlog::details::log_msg{this->_logger_name, spdlog::level::err, message};
        this->_logger->log(this->_log_message);
    }

    void critical(const std::string &message) {
        if (!log_level_is_at_least(spdlog::level::critical))
            return;

        this->_log_message = spdlog::details::log_msg{this->_logger_name, spdlog::level::critical, message};
        this->_logger->log(this->_log_message);
    }

    void warn(const std::string &message) {
        if (!log_level_is_at_least(spdlog::level::warn))
            return;

        this->_log_message = spdlog::details::log_msg{this->_logger_name, spdlog::level::warn, message};
        this->_logger->log(this->_log_message);
    }


private:
    spdlog::details::log_msg _log_message{};
    std::string _logger_name{"logger"};
    // This is set as a unique_ptr to shut up clang-d from reporting "call to implicitly-deleted copy constructor".
    std::unique_ptr<spdlog::sinks::ansicolor_stderr_sink_mt> _logger{ new spdlog::sinks::ansicolor_stderr_sink_mt{} };
        
    bool log_level_is_at_least(const spdlog::level::level_enum required_level) {
        // This is done because the log levels aren't in sequential order (i.e. I can't do log_level < debug)
        // the enum isn't ordered by intensity current_level; I know it's disgusting.
        const static std::unordered_map<spdlog::level::level_enum, std::unordered_set<spdlog::level::level_enum>> allowed_log_level_map = {
            {spdlog::level::info, {spdlog::level::info, spdlog::level::debug, spdlog::level::warn, spdlog::level::err, spdlog::level::critical}},
            {spdlog::level::debug, {spdlog::level::debug, spdlog::level::warn, spdlog::level::err, spdlog::level::critical}},
            {spdlog::level::warn, {spdlog::level::warn, spdlog::level::err, spdlog::level::critical}},
            {spdlog::level::err, {spdlog::level::err, spdlog::level::critical}},
            {spdlog::level::critical, {spdlog::level::critical}}
        };
        
        spdlog::level::level_enum current_level = this->_logger->level();
        return allowed_log_level_map.at(required_level).find(current_level) != allowed_log_level_map.at(required_level).end();
    }
};


#endif
