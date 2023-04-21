#include "Writer.h"
#include "BulkConstants.h"

#include <iostream>
#include <fstream>

void FileWriter::write(int64_t timestamp, std::string const& out)
{
    std::string filename{bulk_consts::bulk_str};
    filename.append(std::to_string(timestamp)).append(".log");

    std::ofstream outfile (filename);
    outfile << out << std::endl;
}

void StdoutWriter::write(int64_t, std::string const& out)
{
    std::cout << out << std::endl;
}
