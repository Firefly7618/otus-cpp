#include "utility/Reader.h"

#include <string>
#include <iostream>
#include <memory>

void print_usage()
{
    std::cout << "usage: bulk <block size>" << std::endl; 
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments" << std::endl;
        print_usage();
        return 0;
    }

    size_t block_size = 0;

    try
    {
        block_size = std::stoull(argv[1]);
    }
    catch(std::invalid_argument const& ex)
    {
        std::cout << "Invalid arguments: " << ex.what() << std::endl;
        print_usage();
        return 0;
    }

    Reader reader;
    reader.read(block_size);

    return 0;
}