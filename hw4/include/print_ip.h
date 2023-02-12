#pragma once

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>


namespace ip_printer
{

template <typename IntegerT,
        std::enable_if_t<std::is_integral<IntegerT>::value, bool> = true>
std::string ip_to_string(IntegerT ip)
{
    unsigned char bytes[sizeof(ip)] = {};
    std::copy(static_cast<const unsigned char*>(static_cast<const void*>(&ip)),
          static_cast<const unsigned char*>(static_cast<const void*>(&ip)) + sizeof(ip),
          bytes);

    std::string out;
    out.reserve(sizeof(ip) * 4); // 3 numbers + "."

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

template <typename StringT,
        std::enable_if_t<std::is_same<StringT, std::string>::value, bool> = true>
std::string ip_to_string(const StringT& ip)
{
    return ip;
}

template <
    template <typename, typename> typename ContainerT,
    typename Type,
	typename Allocator = std::allocator<Type>,
    typename = std::enable_if_t<
        std::is_same_v<ContainerT<Type, Allocator>, std::vector<Type, Allocator>> ||
        std::is_same_v<ContainerT<Type, Allocator>, std::list<Type, Allocator>>>>
std::string ip_to_string(const ContainerT<Type, Allocator>& container)
{
    std::string out;

    constexpr std::size_t digits = 3;
    out.reserve(container.size() * digits);

    for (auto it = container.cbegin(); it != container.cend(); ++it)
    {
        out.append(std::to_string(*it));

        if (std::next(it) != container.cend())
        {
            out.append(".");
        }
    }

    return out;
}

} // namespace ip_printer


/*
template <typename Integer,
        std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
void print_ip(Integer ip_int)
{
    std::cout << ip_printer::ip_to_string(ip_int) << std::endl;
}
*/

template <typename T>
void print_ip(T ip)
{
    std::cout << ip_printer::ip_to_string(ip) << std::endl;
}