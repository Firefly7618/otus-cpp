#include "bulk.h"

#include <string_view>
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>

namespace bulk
{

constexpr std::string_view bulk_str = "bulk";

bool read_bulk(
    size_t bulk_size,
    bool cur_block_is_dynamic,
    bulk_info& cur_bulk,
    bool& next_block_is_dynamic)
{
    next_block_is_dynamic = false;

    size_t commands_count = 0;
    size_t inner_blocks_count = 0;
    bool first_command = true;

    while (true)
    {
        // end of a static command block
        if (not cur_block_is_dynamic and commands_count == bulk_size)
        {
            return true;
        }

        std::string command;
        if (not (std::cin >> command))
        {
            if (cur_block_is_dynamic)
            {
                cur_bulk.second.clear();
            }

            return false;
        }

        if ("{" == command)
        {
            if (cur_block_is_dynamic)
            {
                // process inside block
                ++inner_blocks_count;
                continue;
            }
            else if (0 == commands_count) // this is a first command => we are reading a dynamic block
            {
                cur_block_is_dynamic = true;
                continue;
            }
            else
            {
                next_block_is_dynamic = true;
                return true;
            }
        }
        else if ("}" == command)
        {
            if (not cur_block_is_dynamic)
            {
                std::cout << "Invalid commands" << std::endl;
                return false;
            }

            // end of a dynamic block
            if (0 == inner_blocks_count)
            {
                return true;
            }

            --inner_blocks_count;
            continue;
        }

        if (first_command)
        {
            const auto now = std::chrono::system_clock::now();
            cur_bulk.first = std::chrono::duration_cast<std::chrono::seconds>(
                                now.time_since_epoch()).count();

            first_command = false;
        }

        cur_bulk.second.push_back(command);

        ++commands_count;
    }
}

std::string create_output_string(bulk_info const& bulk)
{
    std::string out{bulk_str};
    out.append(": ");
    
    auto const& commands = bulk.second;
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

void print_bulk(std::string const& out)
{
    std::cout << out << std::endl;
}

void write_bulk(int64_t timestamp, std::string const& out)
{
    std::string filename{bulk_str};
    filename.append(std::to_string(timestamp)).append(".log");

    std::ofstream outfile (filename);
    outfile << out << std::endl;
}

} //ns bulk