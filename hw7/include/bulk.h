#pragma once

#include <utility>
#include <vector>
#include <string>

namespace bulk
{

using bulk_info =  std::pair<int64_t, std::vector<std::string>>;

bool read_bulk(
    size_t bulk_size,
    bool cur_block_is_dynamic,
    bulk_info& cur_bulk,
    bool& next_block_is_dynamic);

std::string create_output_string(bulk_info const& bulk);

void print_bulk(std::string const& out);

void write_bulk(int64_t timestamp, std::string const& out);

}