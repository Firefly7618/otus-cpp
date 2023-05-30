#include "SearchOptions.h"
#include "HashOptions.h"
#include "HashStrategy.h"

#include <boost/program_options.hpp>

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

void find_equal_files(
    std::vector<std::string> const& files_list,
    HASH_ALGORITHM hash_algo,
    size_t )
{
    // map: filepath -> vector of hashes
    //std::map<std::string, std::vector<???> 

    /*
    // Standard hash
    boost::hash<std::string> string_hash;
    std::size_t h = string_hash("Hash me");
    */

   auto hash_strategy = create_hash_strategy(hash_algo);

   /*
   // CRC 32

   */

    for (auto it1 = files_list.begin(); it1 != files_list.end(); it1++)
    {
        for (auto it2 = std::next(it1); it2 != files_list.end(); it2++)
        {
            fs::path path1(*it1);
            fs::path path2(*it2);

            // compare sizes
            if (fs::file_size(path1) != fs::file_size(path2))
            {
                continue;
            }


        }
    }
}

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

        // TODO: maybe this is better than so many parameters...
        //std::cout << vm["scan-level"].as<size_t>() << std::endl;

        hash_options.verify_options();
        search_options.verify_options();

        auto const hash_algo = hash_options.parse_hash_algo();

        auto filepaths = search_options.get_files_list();

        // TODO: do the comparison. Filepaths are ready
        find_equal_files(filepaths, hash_algo, hash_options.block_size);
    }
    catch(std::exception& ex)
    {
        std::cout << ex.what() << std:: endl;
        std::cout << desc << std::endl;
    }

    return 0;
}