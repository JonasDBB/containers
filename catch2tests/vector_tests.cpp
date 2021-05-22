#include "catch.hpp"
#include "../srcs/containers/ft_vector.hpp"
#include <vector>

namespace ft
{
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

TEST_CASE("vector empty", "[vector]")
{
	origivec<int>	real1;
	jonasvec<int>	mine1;
	int	realsum(0);
	int minesum(0);

	for (int i = 1; i <= 10; i++)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}
	while (!real1.empty())
	{
		realsum += real1.back();
		real1.pop_back();
	}
	while (!mine1.empty())
	{
		minesum += mine1.back();
		mine1.pop_back();
	}
	REQUIRE(mine1 == real1);
	REQUIRE(minesum == realsum);
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

TEST_CASE("vector at", "[vector]")
{
	origivec<int>	real1(10);
	jonasvec<int>	mine1(10);

	for (unsigned int i = 0; i < real1.size(); i++)
		real1.at(i) = i;
	for (unsigned int i = 0; i < mine1.size(); i++)
		mine1.at(i) = i;
	REQUIRE(mine1 == real1);
	REQUIRE(mine1.at(4) == real1.at(4));
}

TEST_CASE("vector front back", "[vector]")
{
	origivec<int>	real1;
	jonasvec<int>	mine1;

	real1.push_back(78);
	mine1.push_back(78);
	real1.push_back(16);
	mine1.push_back(16);
	// 78 at the front, 16 at the back

	real1.front() -= real1.back();
	mine1.front() -= mine1.back();
	REQUIRE(mine1 == real1);

	origivec<int>	real2;
	jonasvec<int>	mine2;

	real2.push_back(10);
	mine2.push_back(10);
	while (real2.back() != 0)
		real2.push_back(real2.back() - 1);
	while (mine2.back() != 0)
		mine2.push_back(mine2.back() - 1);
	REQUIRE(mine2 == real2);
}

TEST_CASE("vector assign", "[vector]")
{
	origivec<int>	real1;
	origivec<int>	real2;
	origivec<int>	real3;

	jonasvec<int>	mine1;
	jonasvec<int>	mine2;
	jonasvec<int>	mine3;

	real1.assign(7, 100);
	mine1.assign(7, 100);
	REQUIRE(mine1 == real1);

	auto realIt = real1.begin() + 1;
	auto mineIt = mine1.begin() + 1;

	real2.assign(realIt, real1.end() - 1);
	mine2.assign(mineIt, mine1.end() - 1);
	REQUIRE(mine2 == real2);

	int	intarr[] = {1776, 7, 4};
	real3.assign(intarr, intarr + 3);
	mine3.assign(intarr, intarr + 3);
	REQUIRE(mine3 == real3);
}

TEST_CASE("vector pushback", "[vector]")
{
	origivec<long>	real1;
	jonasvec<long>	mine1;

	for (int i = 0; i < 1000; i++)
	{
		long x = random();
		real1.push_back(x);
		mine1.push_back(x);
	}
	REQUIRE(mine1 == real1);
}

TEST_CASE("vector popback", "[vector]")
{
	origivec<int>	real1;
	jonasvec<int>	mine1;
	int	realsum(0);
	int minesum(0);

	real1.push_back(100);
	real1.push_back(200);
	real1.push_back(300);

	mine1.push_back(100);
	mine1.push_back(200);
	mine1.push_back(300);

	while (!real1.empty())
	{
		realsum += real1.back();
		real1.pop_back();
	}
	while (!mine1.empty())
	{
		minesum += mine1.back();
		mine1.pop_back();
	}
	REQUIRE(mine1 == real1);
	REQUIRE(realsum == minesum);
}

TEST_CASE("vector insert", "[vector]")
{
	origivec<int>	real1(3, 100);
	jonasvec<int>	mine1(3, 100);

	auto realIt = real1.begin();
	auto mineIt = mine1.begin();

	realIt = real1.insert(realIt, 200);
	mineIt = mine1.insert(mineIt, 200);
	REQUIRE(mine1 == real1);
	REQUIRE(*realIt == *mineIt);

	real1.insert(realIt, 2, 300);
	mine1.insert(mineIt, 2, 300);
	REQUIRE(mine1 == real1);
	realIt = real1.begin();
	mineIt = mine1.begin();

	origivec<int>	real2(2, 400);
	jonasvec<int>	mine2(2, 400);
	real1.insert(realIt + 2, real2.begin(), real2.end());
	mine1.insert(mineIt + 2, mine2.begin(), mine2.end());
	REQUIRE(mine1 == real1);

	int	intarr[] = {501, 502, 503};
	real1.insert(real1.begin(), intarr, intarr + 3);
	mine1.insert(mine1.begin(), intarr, intarr + 3);
	REQUIRE(mine1 == real1);
}

TEST_CASE("vector erase", "[vector]")
{
	origivec<int>	real1;
	jonasvec<int>	mine1;

	for (int i = 1; i <= 10; i++)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}

	real1.erase(real1.begin() + 5);
	mine1.erase(mine1.begin() + 5);
	REQUIRE(mine1 == real1);

	real1.erase(real1.begin(), real1.begin() + 3);
	mine1.erase(mine1.begin(), mine1.begin() + 3);
	REQUIRE(mine1 == real1);
}

TEST_CASE("vector swap", "[vector]")
{
	origivec<int>	real1(3, 100);
	jonasvec<int>	mine1(3, 100);
	origivec<int>	real2(5, 200);
	jonasvec<int>	mine2(5, 200);

	real1.swap(real2);
	mine1.swap(mine2);
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);
}

TEST_CASE("vector clear", "[vector]")
{
	origivec<int>	real1;
	jonasvec<int>	mine1;

	for (int i = 100; i <= 300; i += 100)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}
	REQUIRE(mine1 == real1);

	real1.clear();
	mine1.clear();
	REQUIRE(mine1 == real1);

	real1.push_back(1101);
	mine1.push_back(1101);
	real1.push_back(2202);
	mine1.push_back(2202);
	REQUIRE(mine1 == real1);
}

TEST_CASE("vector relational operators", "[vector]")
{
	origivec<int>	real1(3, 100);
	jonasvec<int>	mine1(3, 100);
	origivec<int>	real2(2, 200);
	jonasvec<int>	mine2(2, 200);

	REQUIRE((mine1 == mine2) == (real1 == real2));
	REQUIRE((mine1 != mine2) == (real1 != real2));
	REQUIRE((mine1 > mine2) == (real1 > real2));
	REQUIRE((mine1 < mine2) == (real1 < real2));
	REQUIRE((mine1 <= mine2) == (real1 <= real2));
	REQUIRE((mine1 >= mine2) == (real1 >= real2));
}

TEST_CASE("vector swap overload", "[vector]")
{
	origivec<int>	real1(3, 100);
	jonasvec<int>	mine1(3, 100);
	origivec<int>	real2(5, 200);
	jonasvec<int>	mine2(5, 200);

	swap(real1, real2);
	swap(mine1, mine2);
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);
}
