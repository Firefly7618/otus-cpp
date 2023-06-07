#include "FileComparator.h"

#include <boost/filesystem.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <system_error>

namespace fs = boost::filesystem;

void FileComparator::find_equal_files()
{
    for (auto it1 = m_files_list.begin(); it1 != m_files_list.end(); it1++)
    {
        bool found_eq = false;
        bool io_error = false;

        for (auto it2 = std::next(it1); it2 != m_files_list.end(); )
        {
            auto const compare_result = compare_files(*it1, *it2);

            if (CompareResult::Unequal == compare_result)
            {
                it2++;
            }
            else if (CompareResult::Equal == compare_result)
            {
                // print the file with which other files are compared
                // only the first time when the equal file is found
                if (not found_eq)
                {
                    found_eq = true;
                    std::cout << *it1 << std::endl;
                }

                std::cout << *it2 << std::endl;

                it2 = m_files_list.erase(it2);
            }
            else if (CompareResult::File1_IO_Error == compare_result)
            {
                io_error = true;
                break;
            }
            else if (CompareResult::File2_IO_Error == compare_result)
            {
                m_failed_files.push_back(*it2);
                it2 = m_files_list.erase(it2);
            }
        }

        if (io_error)
        {
            m_failed_files.push_back(*it1);
        }
        else if (found_eq)
        {
            std::cout << "\n";
        }
    }

    if (not m_failed_files.empty())
    {
        std::cout << "Files which couldn't be compared" << std::endl;
        for (const auto& failed_file: m_failed_files)
        {
            std::cout << failed_file << std::endl;
        }
    }
}

FileComparator::CompareResult FileComparator::compare_files(
    std::string const& file_path1,
    std::string const& file_path2)
{
    fs::path path1(file_path1);
    fs::path path2(file_path2);

    // compare sizes
    auto const f1_size = fs::file_size(path1);
    if (f1_size != fs::file_size(path2))
    {
        return CompareResult::Unequal;
    }

    size_t number_of_blocks = f1_size / m_block_size + (f1_size % m_block_size == 0 ? 0 : 1);

    for (size_t block_num = 0; block_num < number_of_blocks; ++block_num)
    {           
        auto const hash1 = get_hash(file_path1, block_num);
        if (0 == hash1)
        {
            return CompareResult::File1_IO_Error;
        }

        auto const hash2 = get_hash(file_path2, block_num);
        if (0 == hash2)
        {
            return CompareResult::File2_IO_Error;
        }

        if (hash1 != hash2)
        {
            return CompareResult::Unequal;
        }
    }

    return CompareResult::Equal;
}

std::size_t FileComparator::get_hash(std::string const& file_path, size_t block_num)
{
    auto& file_hashes = m_file2hashes[file_path];

    if (file_hashes.size() > block_num) // block has been already read
    {
        return file_hashes.at(block_num);
    }
    else if (file_hashes.size() == block_num)
    {
        if(std::ifstream is{file_path})
        {
            is.seekg(block_num * m_block_size);

            std::string block (m_block_size, '\0');
            is.read(&block[0], m_block_size);

            // TODO: remove this printing
            //std::cout << file_path << " " << block_num << " " << block << std::endl;

            auto const result = m_hash_strategy->calc_hash(block);

            file_hashes.push_back(result);

            return result;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        throw std::logic_error("Invalid file_hashes size");
    }
}