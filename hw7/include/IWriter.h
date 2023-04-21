#pragma once

#include <string>

class IWriter
{
public:
    virtual ~IWriter() = default;

    virtual void write(int64_t timestamp, std::string const& out) = 0;
};