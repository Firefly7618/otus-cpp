#pragma once

#include <string>
#include <algorithm>
#include <iostream>


namespace ip_printer
{

template <typename Integer,
        std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
std::string ip_to_string(Integer ip_int)
{
    unsigned char bytes[sizeof(ip_int)] = {};
    std::copy(static_cast<const unsigned char*>(static_cast<const void*>(&ip_int)),
          static_cast<const unsigned char*>(static_cast<const void*>(&ip_int)) + sizeof(ip_int),
          bytes);

    std::string out;
    out.reserve(sizeof(ip_int) * 4); // 3 numbers + "."

    for (int i = sizeof(bytes) - 1; i >= 0 ; --i)
    {
        out.append(std::to_string(bytes[i]));
        if (i  != 0)
        {
            out.append(".");
        }
    }

    return out;
}

} // namespace ip_printer


template <typename Integer,
        std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
void print_ip(Integer ip_int)
{
    std::cout << ip_printer::ip_to_string(ip_int) << std::endl;
}