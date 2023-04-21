#pragma once

#include "IWriter.h"

#include <string>

class FileWriter : public IWriter
{
public:
    ~FileWriter() = default;

    void write(int64_t timestamp, std::string const& out) override;
};

class StdoutWriter : public IWriter
{
public:

    ~StdoutWriter() = default;   

    void write(int64_t timestamp, std::string const& out) override;
};