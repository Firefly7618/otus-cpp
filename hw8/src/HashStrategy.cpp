#include "HashStrategy.h"

#include <boost/crc.hpp>
#include <boost/functional/hash.hpp>

#include <memory>
#include <stdexcept>

std::size_t BoostDefaultHashStrategy::calc_hash(std::string const& input_string)
{
    // Standard hash
    boost::hash<std::string> string_hash;
    return string_hash(input_string);
}

std::size_t CRC32HashStrategy::calc_hash(std::string const& input_string)
{
    boost::crc_32_type result;
    result.process_bytes(input_string.data(), input_string.length());
    return result.checksum();
}

std::unique_ptr<IHashStrategy> create_hash_strategy(HASH_ALGORITHM hash_algo)
{
    switch (hash_algo)
    {
        case HASH_ALGORITHM::Default:
            return std::make_unique<BoostDefaultHashStrategy>();

        case HASH_ALGORITHM::CRC32:
            return std::make_unique<CRC32HashStrategy>();

        default:
            throw std::logic_error("Invald hash algorithm");
    }
}