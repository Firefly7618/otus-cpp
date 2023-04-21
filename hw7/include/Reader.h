#pragma once

#include "IObservable.h"
#include "IWriter.h"

#include <list>
#include <vector>
#include <memory>

class Reader : public IObservable
{
public:

    ~Reader() = default;

    void add_observer(const std::shared_ptr<IWriter>& obs) override
    {
        m_writers.emplace_back(obs);
    }

    void read(size_t bulk_size);

private:
    void notify_writer() override;

    void clear_bulk_info();

private:

    std::list<std::weak_ptr<IWriter>> m_writers;

    // Information about currently processed bulk
    std::vector<std::string> m_commands;
    int64_t m_timestamp;
    size_t m_commands_count;
    size_t m_inner_blocks_count;
    bool m_first_command;
};