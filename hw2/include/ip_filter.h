#pragma once

#include <vector>
#include <string>
#include <string_view>

namespace ip_filter
{

void print_ip(auto ip);

void filter(std::vector<std::vector<std::string>> const& ip_pool,
            std::string_view const first_byte_value);


void filter(std::vector<std::vector<std::string>> const& ip_pool, 
            std::string_view const first_byte_value, 
            std::string_view const second_byte_value);


void filter_any(std::vector<std::vector<std::string>> const& ip_pool,
                std::string_view const byte_value);

}