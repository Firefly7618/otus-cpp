#pragma once

#include <list>
#include <vector>
#include <memory>

class Reader
{
public:

    ~Reader() = default;

    void read(size_t bulk_size);

private:
    void notify_writer(size_t bulk_size);

    void clear_bulk_info();

private:

    // Information about currently processed bulk
    std::vector<std::string> m_commands;
    size_t m_commands_count;
    size_t m_inner_blocks_count;
};