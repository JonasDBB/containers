#include "catch.hpp"
#include "../srcs/ft_vector.hpp"
#include <vector>
#include <iostream>

namespace ft {

	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc> &mine,
					const std::vector<T, Alloc> &real)
	{
		if (mine.capacity() != real.capacity())
			return (false);
		if (mine.size() != real.size())
			return (false);
		if (mine.get_allocator() != real.get_allocator())
			return (false);
		auto myit = mine.begin();
		auto realit = real.begin();
		for (size_t i = 0; i < mine.size(); i++, myit++, realit++)
		{
			if (*myit != *realit)
				return (false);
		}
		return (true);
	}

	template<class T, class Alloc>
	bool operator==(const std::vector<T, Alloc> &real,
					const ft::vector<T, Alloc> &mine)
	{ return (mine == real); }

	template<class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc> &mine,
					const std::vector<T, Alloc> &real)
	{ return !(mine == real); }

	template<class T, class Alloc>
	bool operator!=(const std::vector<T, Alloc> &real,
					const ft::vector<T, Alloc> &mine)
	{ return !(mine == real); }
}

TEST_CASE("vector constructors", "[vector]")
{
	std::vector<int>	real1;
	ft::vector<int>		mine1;
	REQUIRE(mine1 == real1);

	std::vector<int>	real2(4, 100);
	ft::vector<int>		mine2(4, 100);
	REQUIRE(mine2 == real2);

	std::vector<int>	real3(real2.begin(), real2.end());
	ft::vector<int>		mine3(mine2.begin(), mine2.end());
	REQUIRE(mine3 == real3);

	std::vector<int>	real4(real3);
	ft::vector<int>		mine4(mine3);
	REQUIRE(mine4 == real4);

	int intarr[] = {16, 2, 77, 29};
	std::vector<int>	real5(intarr, intarr + sizeof(intarr) / sizeof(int));
	ft::vector<int>		mine5(intarr, intarr + sizeof(intarr) / sizeof(int));
	REQUIRE(mine5 == real5);
}

TEST_CASE("vector assignment", "[vector]")
{
	std::vector<int>	real1 (3, 0);
	ft::vector<int>		mine1 (3, 0);

	std::vector<int>	real2 (5, 0);
	ft::vector<int>		mine2 (5, 0);

	real1 = real2;
	mine1 = mine2;

	real1 = std::vector<int>();
	mine1 = ft::vector<int>();

	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);
}

