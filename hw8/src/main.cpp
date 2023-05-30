#include "SearchOptions.h"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

std::vector<std::string> get_filepaths(
    std::vector<std::string> const& include_dirs,
    std::vector<std::string> const& exclude_dirs,
    std::string const& file_mask,
    int scan_level,
    size_t filesize
)
{
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
                if (not file_mask.empty())
                {
                    boost::regex re(file_mask, boost::regex_constants::grep | boost::regex_constants::icase);

                    if (not boost::regex_match(dir_it->path().filename().string(), re))
                    {
                        std::cout << "Didn't match " << dir_it->path().filename().string() << std::endl;
                        continue;
                    }
                }
                
                if (fs::file_size(dir_it->path()) < filesize)
                {
                    continue;
                }

                // TODO: remove this output
                std::cout << fs::canonical(dir_it->path()) << std::endl;
                // TODO: think about saving paths instead of strings as an optimization
                filepaths.push_back(dir_it->path().string());
            }
        }
    }

    return filepaths;
}

int main(int argc, char* argv[])
{
    po::options_description desc("Usage");
    po::variables_map vm;

    SearchOptions search_options;

    std::string file_mask;
    size_t block_size = 0;
    std::string hash_alg;

    desc.add_options()

    // TODO: set default value for hash algorithm

    ("help,h", "Show help")
    ("include-dir,i", po::value<std::vector<std::string>>(&search_options.include_dirs)->multitoken()->required(), "Include directories")
    ("exclude-dir,e", po::value<std::vector<std::string>>(&search_options.exclude_dirs)->multitoken(), "Exclude directories that match")
    ("filename,n", po::value<std::string>(&search_options.file_mask), "Filename interpreted as a POSIX-basic regular expression")
    ("scan-level,l", po::value<int>(&search_options.scan_level)->default_value(0), "Level of scanning")
    ("file-size,s", po::value<size_t>(&search_options.min_file_size)->default_value(1), "Minimum file size")
    ("block-size,b", po::value<size_t>(&block_size)->required(), "Block size for reading files")
    ("hash,h", po::value<std::string>(&hash_alg), "Hash algorithm used for comparison")
    ;

    try
    {
        po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
        po::store(parsed, vm);
        po::notify(vm);

        // TODO: maybe this is better than so many parameters...
        //std::cout << vm["scan-level"].as<size_t>() << std::endl;

        auto filepaths = get_filepaths(search_options.include_dirs, search_options.exclude_dirs,
                search_options.file_mask, search_options.scan_level, search_options.min_file_size);

        // TODO: do the comparison. Filepaths are ready
    }
    catch(std::exception& ex)
    {
        std::cout << ex.what() << std:: endl;
        std::cout << desc << std::endl;
    }


    return 0;
}