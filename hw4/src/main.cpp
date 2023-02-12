#include "print_ip.h"

#include <iostream>

int main(int, char *[])
{
    // integer values
    std::cout << print_ip( int8_t{-1} ) << std::endl; // 255
    std::cout << print_ip( int16_t{0} ) << std::endl; // 0.0
    std::cout << print_ip( int32_t{2130706433} ) << std::endl; // 127.0.0.1
    std::cout << print_ip( int64_t{8875824491850138409} ) << std::endl;// 123.45.67.89.101.112.131.41

    return 0;
}