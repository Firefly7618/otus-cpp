#include "SearchOptions.h"

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

namespace fs = boost::filesystem;

void SearchOptions::verify_options()
{
    if (scan_level < 0)
    {
        throw std::invalid_argument("Invalid scan level");
    }
}

std::vector<std::string> SearchOptions::get_files_list()
{
    if (include_dirs.empty())
    {
        throw std::logic_error("Empty list of directories included in search");
    }

    std::vector<std::string> filepaths;

    for (auto const& dir : include_dirs)
    {
        fs::path dir_path(dir);

        fs::recursive_directory_iterator dir_it(dir_path);
        fs::recursive_directory_iterator end;

        for (; dir_it != end; ++dir_it)
        {
            while (dir_it != end and dir_it.depth() > scan_level)
            {
                dir_it.pop();
            }

            if (dir_it == end)
            {
                break;
            }

            if (fs::is_directory(dir_it->path()))
            {
                auto const& cur_dir_name = dir_it->path().filename().string();
                if (std::end(exclude_dirs) != std::find(std::begin(exclude_dirs), std::end(exclude_dirs), cur_dir_name))
                {
                    dir_it.no_push(); // don't recurse into this directory.
                }
            }
            else
            {
                if (check_file_params(dir_it->path()))
                {
                    // TODO: remove this output
                    std::cout << fs::canonical(dir_it->path()) << std::endl;
                    // TODO: think about saving paths instead of strings as an optimization
                    filepaths.push_back(dir_it->path().string());
                }
            }
        }
    }

    return filepaths;
}

bool SearchOptions::check_file_params(const fs::path& path_to_check)
{
    if (not file_mask.empty())
    {
        boost::regex re(file_mask, boost::regex_constants::grep | boost::regex_constants::icase);

        if (not boost::regex_match(path_to_check.filename().string(), re))
        {
            std::cout << "Didn't match " << path_to_check.filename().string() << std::endl;
            return false;
        }
    }

    if (fs::file_size(path_to_check) < min_file_size)
    {
        return false;
    }

    return true;
}