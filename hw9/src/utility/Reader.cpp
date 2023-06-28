#include "utility/Reader.h"
#include "async/async.h"

#include <string>
#include <vector>
#include <iostream>


void Reader::read(size_t bulk_size)
{
    clear_bulk_info();

    bool reading_dynamic_block = false;

    while (true)
    {
        // end of a static command block
        if (not reading_dynamic_block and m_commands_count == bulk_size and bulk_size != 0)
        {
            notify_writer(bulk_size);
        }

        std::string command;
        if (not (std::cin >> command))
        {
            if (not reading_dynamic_block)
            {
                notify_writer(bulk_size);
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
                notify_writer(bulk_size);
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
                notify_writer(bulk_size);
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

        m_commands.push_back(command);

        ++m_commands_count;
    }
}

void Reader::notify_writer(size_t bulk_size)
{
    if (m_commands.empty())
    {
        clear_bulk_info();
        return;
    }

    auto context = async::connect(bulk_size);

    for (const auto& command : m_commands)
    {
        async::receive(context, command.data(), command.size());
    }

    async::disconnect(std::move(context));

    clear_bulk_info();
}

void Reader::clear_bulk_info()
{
    m_commands.clear();
    m_commands_count = 0;
    m_inner_blocks_count = 0;
}