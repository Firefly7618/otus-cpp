#include "print_ip.h"

#include <gtest/gtest.h>


// This is to check that senitizer is working
/*
TEST(gtest_googletest, gtest_googletest_compilation)
{
    ASSERT_TRUE(true);

    int* ii = new int(5);
    ii[0] = 17;
    std::cout << ii[0] << std::endl;
}
*/

TEST(test_print_ip_int, test_print_ip_int)
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


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}