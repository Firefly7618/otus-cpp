#pragma once

#include "HashOptions.h"
#include "HashStrategy.h"

#include <memory>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>

class FileComparator
{
public:

    FileComparator() = delete;

    FileComparator(
        std::vector<std::string> const& files_list,
        size_t block_size,
        HASH_ALGORITHM hash_algo)
    : m_files_list(files_list.begin(), files_list.end()) // TODO: maybe it should have been list from the beginning
    , m_block_size(block_size)
    , m_hash_strategy(create_hash_strategy(hash_algo))
    {
    }

    void find_equal_files();

private:

    enum class CompareResult
    {
        Unequal,
        Equal,
        File1_IO_Error,
        File2_IO_Error
    };

    CompareResult compare_files(std::string const& file_path1, std::string const& file_path2);

    std::size_t get_hash(std::string const& file_path, size_t block_num);

private:

    std::list<std::string> m_files_list;
    size_t m_block_size;
    std::unique_ptr<IHashStrategy> m_hash_strategy;

    // map: filepath -> vector of hashes of each block
    std::unordered_map<std::string, std::vector<std::size_t>> m_file2hashes;

    // Files that couldn't be opened or read
    std::vector<std::string> m_failed_files;
};