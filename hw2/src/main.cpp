#include "ip_filter.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

namespace
{

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

} // ns

int main()
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        std::sort(ip_pool.begin(), ip_pool.end(), [](auto const& lhs, auto const& rhs) -> bool
        {
            if (lhs[0] != rhs[0])
            {
                return std::stoul(lhs[0]) > std::stoul(rhs[0]);
            }

            if (lhs[1] != rhs[1])
            {
                return std::stoul(lhs[1]) > std::stoul(rhs[1]);
            }

            if (lhs[2] != rhs[2])
            {
                return std::stoul(lhs[2]) > std::stoul(rhs[2]);
            }

            return std::stoul(lhs[3]) > std::stoul(rhs[3]);

        });

        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            ip_filter::print_ip(ip);
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // filter by first byte and output
        constexpr std::string_view filter_byte_1 = "1";
        ip_filter::filter(ip_pool, filter_byte_1);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // filter by first and second bytes and output
        constexpr std::string_view filter_byte_46 = "46";
        constexpr std::string_view filter_byte_70 = "70";
        ip_filter::filter(ip_pool, filter_byte_46, filter_byte_70);

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // filter by any byte and output
        ip_filter::filter_any(ip_pool, filter_byte_46);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
