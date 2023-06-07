#include "SearchOptions.h"
#include "HashOptions.h"
#include "HashStrategy.h"
#include "FileComparator.h"

#include <boost/program_options.hpp>

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    po::options_description desc("Usage");
    po::variables_map vm;

    SearchOptions search_options;
    HashOptions hash_options;

    desc.add_options()

    // TODO: set default value for hash algorithm

    ("help,h", "Show help")
    ("include-dir,i", po::value<std::vector<std::string>>(&search_options.include_dirs)->multitoken()->required(), "Include directories")
    ("exclude-dir,e", po::value<std::vector<std::string>>(&search_options.exclude_dirs)->multitoken(), "Exclude directories that match")
    ("filename,n", po::value<std::string>(&search_options.file_mask), "Filename interpreted as a POSIX-basic regular expression")
    ("scan-level,l", po::value<int>(&search_options.scan_level)->default_value(0), "Level of scanning")
    ("file-size,s", po::value<size_t>(&search_options.min_file_size)->default_value(1), "Minimum file size")
    ("block-size,b", po::value<size_t>(&hash_options.block_size)->required(), "Block size for reading files")
    ("hash,h", po::value<std::string>(&hash_options.hash_algo), "Hash algorithm used for comparison")
    ;

    try
    {
        po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
        po::store(parsed, vm);
        po::notify(vm);

        hash_options.verify_options();
        search_options.verify_options();

        auto const hash_algo = hash_options.parse_hash_algo();

        auto filepaths = search_options.get_files_list();

        FileComparator comparator(filepaths, hash_options.block_size, hash_algo);
        comparator.find_equal_files();
    }
    catch(std::exception& ex)
    {
        std::cout << ex.what() << std:: endl;
        std::cout << desc << std::endl;
    }

    return 0;
}