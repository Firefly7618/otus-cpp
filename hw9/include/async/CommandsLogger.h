#pragma once

#include "async/Logger.h"

namespace async
{

class CommandsLogger
{
public:

    static CommandsLogger& getInstance()
    {
        static CommandsLogger instance;
        return instance;
    }

    CommandsLogger(CommandsLogger&&) = delete;
    CommandsLogger(const CommandsLogger&) = delete;
    CommandsLogger& operator=(CommandsLogger&&) = delete;
    CommandsLogger& operator=(const CommandsLogger&) = delete;

    ~CommandsLogger() = default;

    void log_commands(std::vector<std::string> const& commands)
    {
        m_file_logger.log(commands);
        m_stdout_logger.log(commands);
    }

private:

    static const std::size_t file_loggers_num = 2;
    static const std::size_t stdout_loggers_num = 1;

    CommandsLogger()
    : m_file_logger{file_loggers_num}
    , m_stdout_logger{stdout_loggers_num}
    { }

private:

    helpers::FileLogger m_file_logger;
    helpers::StdOutLogger m_stdout_logger;
};

} // namespace async