#pragma once

#include "HashOptions.h"

#include <memory>
#include <string>

// wrapper object around hash algorithms
// in constructor decide which algorithm will be used
// public method hash

// TODO: do smth like a hashing strategy

class IHashStrategy
{
public:

    virtual uint32_t calc_hash(std::string const& input_string) = 0;

};

class BoostDefaultHashStrategy : public IHashStrategy
{
public:

    uint32_t calc_hash(std::string const& input_string) override;

};

class CRC32HashStrategy : public IHashStrategy
{
public:

    uint32_t calc_hash(std::string const& input_string) override;

};


std::unique_ptr<IHashStrategy> create_hash_strategy(HASH_ALGORITHM hash_algo);
