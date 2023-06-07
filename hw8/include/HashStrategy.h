#pragma once

#include "HashOptions.h"

#include <memory>
#include <string>

class IHashStrategy
{
public:

    virtual std::size_t calc_hash(std::string const& input_string) = 0;

};

class BoostDefaultHashStrategy : public IHashStrategy
{
public:

    std::size_t calc_hash(std::string const& input_string) override;

};

class CRC32HashStrategy : public IHashStrategy
{
public:

    std::size_t calc_hash(std::string const& input_string) override;

};


std::unique_ptr<IHashStrategy> create_hash_strategy(HASH_ALGORITHM hash_algo);
