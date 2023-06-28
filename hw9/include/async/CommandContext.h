#pragma once

#include "async/CommandsLogger.h"

#include <vector>
#include <string>

// TODO: remove
#include <iostream>

namespace async
{

class CommandContext
{
public:
    void receive(const char* data, std::size_t data_size)
    {
        m_commands.emplace_back(data, data_size);
    }

    ~CommandContext()
    {
        // TODO: remove
        std::cout << "CommandContext desctuctor!!!" << std::endl;

        CommandsLogger::getInstance().log_commands(m_commands);
    }

private:

    std::vector<std::string> m_commands;
};

} // namespace async

