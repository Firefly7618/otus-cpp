#include "HashOptions.h"

#include <string>
#include <string_view>
#include <stdexcept>


namespace
{

constexpr const std::string_view default_hash_algo {"default"};
constexpr const std::string_view crc32_hash_algo {"crc32"};

} // ns unknown

HASH_ALGORITHM HashOptions::parse_hash_algo()
{
    if (default_hash_algo == hash_algo or hash_algo.empty())
    {
        return HASH_ALGORITHM::Default;
    }
    else if (crc32_hash_algo == hash_algo)
    {
        return HASH_ALGORITHM::Default;
    }
    else
    {
        throw std::invalid_argument("Unknown hash algorithm");
    }
}

void HashOptions::verify_options()
{
    if (block_size == 0)
    {
        throw std::invalid_argument("Invalid block size");
    }
}