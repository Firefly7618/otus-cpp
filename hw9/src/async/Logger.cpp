#include "async/Logger.h"

#include <string>
#include <vector>
#include <string_view>
#include <iostream>
#include <fstream>
#include <chrono>

namespace
{

constexpr std::string_view bulk_str = "bulk";

std::string create_output_string(std::vector<std::string> const& commands)
{
    std::string out{bulk_str};
    out.append(": ");

    for (auto command_it = commands.begin(); command_it != commands.end(); ++command_it)
    {
        out.append(*command_it);
        if (std::next(command_it) != commands.end())
        {
            out.append(" ");
        }
    }

    return out;
}

} // unnamed namespace

namespace async::helpers
{

Logger::Logger(std::size_t workers_num)
{
	for (std::size_t i = 0; i < workers_num; ++i)
    {
		m_loggers.emplace_back(&Logger::worker_function, this);
	}
}

Logger::~Logger()
{
    m_task_queue.stop();

    for (auto& logger: m_loggers)
    {
        logger.join(); // TODO: not necessary if you use std::jthread
        // after the destructor exits, q will be destroyed
    }
}

void Logger::log(std::vector<std::string> const& commands)
{
    m_task_queue.push(commands);
}

void StdOutLogger::worker_function()
{
    while (true)
    {
        auto task = m_task_queue.pop();

        if (not task)
        {
            return;
        }

        auto out = create_output_string(*task);

        std::cout << out << std::endl;
    }
}	

void FileLogger::worker_function()
{
    while (true)
    {
        auto task = m_task_queue.pop();

        if (not task)
        {
            return;
        }

        // TODO: add postfix to determine which thread is which
        auto out = create_output_string(*task);

        auto const now = std::chrono::system_clock::now();
        int64_t const timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                                now.time_since_epoch()).count();

        std::string filename{bulk_str};
        filename.append(std::to_string(timestamp)).append(".log");

        std::ofstream outfile (filename);
        outfile << out << std::endl;
	}
}

} // namespace async::helpers