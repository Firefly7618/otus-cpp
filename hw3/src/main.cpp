#include "reserve_allocator.h"
#include "container.h"

#include <map>
#include <iostream>

unsigned int factorial(int n)
{
	if (n < 0)
	{
		return 0;
	}

    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

int main(int, char *[])
{
	// std map usage

	auto m = std::map<int, int>{};

	for (int i = 0; i < 10; ++i)
	{
		m[i] = factorial(i);
	}

	auto m2 = std::map<int, int, std::less<int>,
		reserve_allocator<std::pair<const int, int>>>{};

	for (int i = 0; i < 10; ++i)
	{
		m2[i] = factorial(i);
	}

	for (const auto& [key, value]: m2)
	{
		std::cout << key << " " << value << std::endl;
	}

	// simple vector usage
	simple_vector<int> v1(10);
	for (int i = 0; i < 10; ++i)
	{
		v1[i] = i;
	}

	simple_vector<int, reserve_allocator<int>> v2(10);
	for (int i = 0; i < 10; ++i)
	{
		v2[i] = i;
	}

	for (const auto& value: v2)
	{
		std::cout << value << std::endl;
	}

	return 0;
}