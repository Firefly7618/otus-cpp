#include "HashStrategy.h"

#include <memory>
#include <stdexcept>

uint32_t BoostDefaultHashStrategy::calc_hash(std::string const& )
{
    // TODO: implement
    return 0;
}

uint32_t CRC32HashStrategy::calc_hash(std::string const& )
{
    // TODO: implement
    return 0;
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