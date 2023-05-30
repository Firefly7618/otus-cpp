#pragma once

#include <boost/filesystem.hpp>

#include <vector>
#include <string>

struct SearchOptions
{
    std::vector<std::string> include_dirs;
    std::vector<std::string> exclude_dirs;
    std::string file_mask;

    int scan_level = 0;
    size_t min_file_size = 1;

    void verify_options();

    // get the list of files which match with the search options
    std::vector<std::string> get_files_list();

private:
    bool check_file_params(const boost::filesystem::path& path_to_check);
};