#pragma once

#include <vector>
#include <string>

struct SearchOptions
{
    std::vector<std::string> include_dirs;
    std::vector<std::string> exclude_dirs;
    std::string file_mask;

    int scan_level = 0;
    size_t min_file_size = 1;
};