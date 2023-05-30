#pragma once

#include <string>

enum class HASH_ALGORITHM
{
    Default,    // default boost::hash implementation
    CRC32
};

struct HashOptions
{
    size_t block_size = 0;
    std::string hash_algo;

    void verify_options();

    HASH_ALGORITHM parse_hash_algo();
};