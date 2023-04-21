#include "bulk.h"

#include <string>
#include <iostream>

void print_usage()
{
    std::cout << "usage: bulk <block size>" << std::endl; 
}

void bulk_main(size_t block_size)
{
    using namespace bulk;

    bool read = true;
    bool dynamic_block = false;

    while (read)
    {
        bulk_info bulk;
        bool next_block_is_dynamic = false;

        read = read_bulk(block_size, dynamic_block, bulk, next_block_is_dynamic);

        if (not bulk.second.empty())
        {
            std::string const out = create_output_string(bulk);
            print_bulk(out);
            write_bulk(bulk.first, out);
        }

        dynamic_block = next_block_is_dynamic;
    }
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

    bulk_main(block_size);

    return 0;
}