#include "catch.hpp"
#include "../srcs/ft_vector.hpp"
#include <vector>

namespace ft
{
	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc> &mine,
					const std::vector<T, Alloc> &real)
	{
//		auto x = mine.capacity();
//		auto y = real.capacity();
//		x = x + 1 - 1;
//		y = y + 1 - 1;
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

#define origivec std::vector
#define jonasvec ft::vector

TEST_CASE("vector constructors", "[vector]")
{
	origivec<int>	real1;
	jonasvec<int>	mine1;
	REQUIRE(mine1 == real1);

	origivec<int>	real2(4, 100);
	jonasvec<int>	mine2(4, 100);
	REQUIRE(mine2 == real2);

	origivec<int>	real3(real2.begin(), real2.end());
	jonasvec<int>	mine3(mine2.begin(), mine2.end());
	REQUIRE(mine3 == real3);

	origivec<int>	real4(real3);
	jonasvec<int>	mine4(mine3);
	REQUIRE(mine4 == real4);

	int intarr[] = {16, 2, 77, 29};
	origivec<int>	real5(intarr, intarr + sizeof(intarr) / sizeof(int));
	jonasvec<int>	mine5(intarr, intarr + sizeof(intarr) / sizeof(int));
	REQUIRE(mine5 == real5);
}

TEST_CASE("vector assignment", "[vector]")
{
	origivec<int>	real1(3, 0);
	jonasvec<int>	mine1(3, 0);
	REQUIRE(mine1 == real1);

	origivec<int>	real2(5, 0);
	jonasvec<int>	mine2(5, 0);
	REQUIRE(mine2 == real2);

	real1 = real2;
	mine1 = mine2;
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);

	real1 = origivec<int>();
	mine1 = jonasvec<int>();
	REQUIRE(mine1 == real1);
}

TEST_CASE("vector begin end", "[vector]")
{
	origivec<int>	real1;
	jonasvec<int>	mine1;
	for (int i = 1; i <= 5; i++)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}
	REQUIRE(mine1 == real1);

	auto realIt1 = real1.begin();
	auto myIt1 = mine1.begin();
	REQUIRE(*realIt1 == *myIt1);

	for (; realIt1 != real1.end() && myIt1 != mine1.end(); realIt1++, myIt1++)
		REQUIRE(*realIt1 == *myIt1);
	// check last value, since end iterator is 1 past the end
	REQUIRE(*(realIt1 - 1) == *(myIt1 - 1));
}

TEST_CASE("vector rbegin rend", "[vector]")
{
	origivec<int>	real1(5);
	jonasvec<int>	mine1(5);
	REQUIRE(mine1 == real1);

	auto realRevIt = real1.rbegin();
	auto mineRevIt = mine1.rbegin();
	int i = 0;
	for (; realRevIt != real1.rend(); realRevIt++)
		*realRevIt = ++i;
	i = 0;
	for (; mineRevIt != mine1.rend(); mineRevIt++)
		*mineRevIt = ++i;
	REQUIRE(mine1 == real1);
}

TEST_CASE("vector size", "[vector]")
{
	origivec<int>	real1;
	jonasvec<int>	mine1;
	for (int i = 0; i < 10; i++)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}
	REQUIRE(mine1 == real1);

	real1.insert(real1.end(), 10, 100);
	mine1.insert(mine1.end(), 10, 100);
	REQUIRE(mine1 == real1);

	real1.pop_back();
	mine1.pop_back();
	REQUIRE(mine1 == real1);
}

TEST_CASE("vector max size", "[vector]")
{
	origivec<int>	real1;
	jonasvec<int>	mine1;

	for (int i = 0; i < 100; i++)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}
	REQUIRE(mine1 == real1);
	REQUIRE(mine1.max_size() == real1.max_size());
}

TEST_CASE("vector resize", "[vector]")
{
	origivec<int>	real1;
	jonasvec<int>	mine1;

	for (int i = 0; i < 10; i++)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}

	real1.resize(5);
	mine1.resize(5);
	REQUIRE(mine1 == real1);

	real1.resize(8, 100);
	mine1.resize(8, 100);
	REQUIRE(mine1 == real1);

	real1.resize(12);
	mine1.resize(12);
	REQUIRE(mine1 == real1);
}

TEST_CASE("vector reserve", "[vector]")
{
	origivec<int>	real1;
	jonasvec<int>	mine1;

	for (int i = 0; i < 100; i++)
	{
		real1.push_back(i);
		mine1.push_back(i);
		REQUIRE(mine1 == real1);
	}

	origivec<int>	real2;
	jonasvec<int>	mine2;

	real2.reserve(100);
	mine2.reserve(100);
	REQUIRE(mine2 == real2);
	for (int i = 0; i < 100; i++)
	{
		real2.push_back(i);
		mine2.push_back(i);
		REQUIRE(mine2 == real2);
	}
}

TEST_CASE("vector bracket operator", "[vector]")
{
	origivec<int>	real1(10);
	jonasvec<int>	mine1(10);

	origivec<int>::size_type realSz = real1.size();
	jonasvec<int>::size_type mineSz = mine1.size();

	for (unsigned int i = 0; i < realSz; i++)
		real1[i] = i;
	for (unsigned int i = 0; i < mineSz; i++)
		mine1[i] = i;
	REQUIRE(mine1 == real1);

	for (unsigned int i = 0; i < realSz / 2; i++)
	{
		int tmp;
		tmp = real1[realSz - 1 - i];
		real1[realSz - 1 - i] = real1[i];
		real1[i] = tmp;
	}

	for (unsigned int i = 0; i < mineSz / 2; i++)
	{
		int tmp;
		tmp = mine1[mineSz - 1 - i];
		mine1[mineSz - 1 - i] = mine1[i];
		mine1[i] = tmp;
	}
	REQUIRE(mine1 == real1);
}


