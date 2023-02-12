#include "print_ip.h"

#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <list>



TEST(test_print_ip, test_print_ip_int)
{
    {
        auto const ip_str = ip_printer::ip_to_string( int8_t{-1} ); // 255
        EXPECT_EQ(ip_str, "255");
    }

    {
        auto const ip_str = ip_printer::ip_to_string( int16_t{0} ); // 0.0
        EXPECT_EQ(ip_str, "0.0");
    }

    {
        auto const ip_str = ip_printer::ip_to_string( int32_t{2130706433} );
        EXPECT_EQ(ip_str, "127.0.0.1");
    }

    {
        auto const ip_str = ip_printer::ip_to_string( int64_t{8875824491850138409} );
        EXPECT_EQ(ip_str, "123.45.67.89.101.112.131.41");
    }
}

TEST(test_print_ip, test_print_ip_string)
{
    {
        const std::string str {"abcd"};
        auto const ip_str = ip_printer::ip_to_string(str);
        EXPECT_EQ(ip_str, str);
    }
}

TEST(test_print_ip, test_print_ip_container)
{
    {
        const std::vector<int> v {100, 200, 300, 400};
        auto const ip_str = ip_printer::ip_to_string(v);

        EXPECT_EQ(ip_str, "100.200.300.400");
    }

    {
        const std::list<int> v {400, 300, 200, 100};
        auto const ip_str = ip_printer::ip_to_string(v);

        EXPECT_EQ(ip_str, "400.300.200.100");
    }

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}