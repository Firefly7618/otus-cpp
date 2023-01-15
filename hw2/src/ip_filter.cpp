#include "ip_filter.h"

#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <iostream>

namespace ip_filter
{

void print_ip(auto ip)
{
    for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
     {
        if (ip_part != ip->cbegin())
         {
            std::cout << ".";

            }
         std::cout << *ip_part;
    }

    std::cout << std::endl;
}

void filter(std::vector<std::vector<std::string>> const& ip_pool,
            std::string_view const first_byte_value)
{
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        if (first_byte_value == ip->front())
        {
            print_ip(ip);
        }
    }
}

void filter(std::vector<std::vector<std::string>> const& ip_pool, 
            std::string_view const first_byte_value, 
            std::string_view const second_byte_value)
{
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        if (first_byte_value == ip->at(0) and second_byte_value == ip->at(1))
        {
            print_ip(ip);
        }
    }
}

void filter_any(std::vector<std::vector<std::string>> const& ip_pool,
                std::string_view const byte_value)
{
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        if ( std::any_of(ip->cbegin(), ip->cend(), [&byte_value](auto const& ip_part) -> bool
        {
            return byte_value == ip_part;
        }))
        {
            print_ip(ip);
        }
    }
}

} // ns ip_filter