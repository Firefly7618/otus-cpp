#include "reserve_allocator.h"
#include "container.h"

#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <string>


// This is to check that sanitizer is working
/*
TEST(gtest_googletest, gtest_googletest_compilation)
{
    ASSERT_TRUE(true);

    int* ii = new int(5);
    ii[0] = 17;
    std::cout << ii[0] << std::endl;
}
*/

TEST(TestAllocator, TestVectorAllocation)
{
    // less elements than allocator allocates
    {
        std::vector<int, reserve_allocator<int, 10>> v{};
        v.push_back(1);
        for (auto& elem: v)
        {
             ++elem;
        }
    }

    // allocates additional memory which is less than already allocated
    {
        std::vector<int, reserve_allocator<int, 10>> v{1,2,3};
        v.push_back(6);
        v.push_back(7);

        for (auto& elem: v)
        {
            ++elem;
        }
    }

    // allocates memory equal to what allocator is allocated
    {
        std::vector<int, reserve_allocator<int, 10>> v{1,2,3,4,5,6,7,8,9,10};
        for (auto& elem: v)
        {
                ++elem;
        }
    }

    // allocates additional memory which is more than already allocated
    {
        std::vector<int, reserve_allocator<int, 10>> v{1,2,3,4,5,6,7,8,9,10};
        bool caught_ex = false;

        try
        {
            v.push_back(11);
        }
        catch(const std::bad_alloc& ex)
        {
            caught_ex = true;
        }

        ASSERT_TRUE(caught_ex);
    }
}

TEST(TestAllocator, TestMapAllocation)
{
    // less elements than allocator allocates
    {
        std::map<int, std::string, std::less<int>, reserve_allocator<std::pair<const int, std::string>, 10>> m;
        m.insert({1, "test1"});

        for (auto& [key, value]: m)
        {
            value.append(value);
        }
    }

    // allocates additional memory which is less than already allocated
    {
        std::map<int, std::string, std::less<int>, reserve_allocator<std::pair<const int, std::string>, 10>> m{{1, "test1"},
                                                                                                     {2, "test2"},
                                                                                                     {3, "test3"}
                                                                                                    };
        m.insert({4, "test4"});
        m.insert({5, "test5"});

        for (auto& [key, value]: m)
        {
            value.append(value);
        }
    }

    // allocates memory equal to what allocator is allocated
    {
        std::map<int, std::string, std::less<int>, reserve_allocator<std::pair<const int, std::string>, 10>> m;

        for (uint8_t i=1;i <= 10; ++i)
        {
          m.insert({i, "test" + std::to_string(i)});
        }

        for (auto& [key, value]: m)
        {
            value.append(value);
        }
    }
}

TEST(TestSimpleVector, DefaultAllocator)
{
    simple_vector<int> v1(1);
    for (int i=0; i < 10; ++i)
    {
        v1.push_back(i);
    }
}

TEST(TestSimpleVector, ReserveAllocatorAllocator)
{
    simple_vector<int, reserve_allocator<int, 100>> v1(1);
    for (int i=0; i < 10; ++i)
    {
        v1.push_back(i);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
