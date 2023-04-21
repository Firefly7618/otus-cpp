#include "Reader.h"
#include "BulkConstants.h"

#include <string>
#include <vector>
#include <chrono>
#include <iostream>

namespace
{

std::string create_output_string(std::vector<std::string> commands)
{
    std::string out{bulk_consts::bulk_str};
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

void Reader::read(size_t bulk_size)
{
    clear_bulk_info();

    bool reading_dynamic_block = false;

    while (true)
    {
        // end of a static command block
        if (not reading_dynamic_block and m_commands_count == bulk_size and bulk_size != 0)
        {
            notify_writer();
        }

        std::string command;
        if (not (std::cin >> command))
        {
            if (not reading_dynamic_block)
            {
                notify_writer();
            }

            // end of processing
            return;
        }

        if ("{" == command)
        {
            if (reading_dynamic_block)
            {
                // process inner block
                ++m_inner_blocks_count;
                continue;
            }
            else if (0 != m_commands_count)
            {
                // we've been reading a static block
                // let's notify writer about currently processed commands
                notify_writer();
            }
            
            // we are starting reading a dynamic block
            reading_dynamic_block = true;
            continue;
        }
        else if ("}" == command)
        {
            if (not reading_dynamic_block)
            {
                std::cout << "Invalid commands" << std::endl;
                return;
            }

            // end of a dynamic block
            if (0 == m_inner_blocks_count)
            {
                reading_dynamic_block = false;
                notify_writer();
            }
            else
            {
                --m_inner_blocks_count;
            }

            continue;
        }
        else if (0 == bulk_size and not reading_dynamic_block)
        {
            std::cout << "Invalid commands" << std::endl;
            return;
        }

        if (m_first_command)
        {
            const auto now = std::chrono::system_clock::now();
            m_timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                                now.time_since_epoch()).count();

            m_first_command = false;
        }

        m_commands.push_back(command);

        ++m_commands_count;
    }
}

void Reader::notify_writer()
{
    if (m_commands.empty())
    {
        clear_bulk_info();
        return;
    }
    auto out_str = create_output_string(m_commands);

    for (auto it = m_writers.begin(); it != m_writers.end();)
    {
        auto ptr = it->lock();
        if (ptr)
        {
            ptr->write(m_timestamp, out_str);
            it++;
        }
        else
        {
            m_writers.erase(it);
        }
    }

    clear_bulk_info();
}

void Reader::clear_bulk_info()
{
    m_commands.clear();
    m_timestamp = 0;
    m_commands_count = 0;
    m_inner_blocks_count = 0;
    m_first_command = true;
}