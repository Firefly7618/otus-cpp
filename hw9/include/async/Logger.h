#pragma once

#include "async/ThreadSafeQueue.h"

#include <vector>
#include <string>
#include <thread>

namespace async::helpers
{

class Logger
{
public:

    explicit Logger(std::size_t workers_num);

    Logger() = delete;
    Logger(Logger&&) = delete;
    Logger(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;

    ~Logger();

    void log(std::vector<std::string> const& commands);

protected:

    virtual void worker_function() = 0;

protected:

    std::vector<std::thread> m_loggers;
    ThreadSafeQueue<std::vector<std::string>> m_task_queue;
};
 
class StdOutLogger : public Logger
{
public:
    explicit StdOutLogger(std::size_t workers_num)
    : Logger(workers_num)
    { }

private:

    void worker_function() override;

};

class FileLogger : public Logger
{
public:
    explicit FileLogger(std::size_t workers_num)
    : Logger(workers_num)
    { }

private:

    void worker_function() override;
};


} // async::helpers