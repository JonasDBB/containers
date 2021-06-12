#include "catch.hpp"
#include "../srcs/containers/ft_list.hpp"
#include <list>

namespace ft
{
	template<class T, class Alloc>
	bool operator==(const ft::list<T, Alloc> &mine,
					const std::list<T, Alloc> &real)
	{
		if (mine.size() != real.size())
			return (false);
		if (mine.get_allocator() != real.get_allocator())
			return (false);
		auto myit = mine.begin();
		auto realit = real.begin();
		for (size_t i = 0; i < mine.size(); ++i, ++myit, ++realit)
		{
			if (*myit != *realit)
				return (false);
		}
		return (true);
	}

	template<class T, class Alloc>
	bool operator==(const std::list<T, Alloc> &real,
					const ft::list<T, Alloc> &mine)
	{ return (mine == real); }

	template<class T, class Alloc>
	bool operator!=(const ft::list<T, Alloc> &mine,
					const std::list<T, Alloc> &real)
	{ return !(mine == real); }

	template<class T, class Alloc>
	bool operator!=(const std::list<T, Alloc> &real,
					const ft::list<T, Alloc> &mine)
	{ return !(mine == real); }
}

#define origilist std::list
#define jonaslist ft::list

TEST_CASE("list constructors", "[list]")
{
	origilist<int> real1;
	jonaslist<int> mine1;
	REQUIRE(mine1 == real1);

	origilist<int> real2(4, 100);
	jonaslist<int> mine2(4, 100);
	REQUIRE(mine2 == real2);

	origilist<int> real3(real2.begin(), real2.end());
	jonaslist<int> mine3(mine2.begin(), mine2.end());

	origilist<int> real4(real3);
	jonaslist<int> mine4(mine3);

	int intarr[] = {16, 2, 77, 29};
	origilist<int> real5(intarr, intarr + sizeof(intarr) / sizeof(int));
	jonaslist<int> mine5(intarr, intarr + sizeof(intarr) / sizeof(int));
	REQUIRE(mine5 == real5);
}

TEST_CASE("list assignment", "[list]")
{
	origilist<int>	real1(3, 0);
	jonaslist<int>	mine1(3, 0);
	REQUIRE(mine1 == real1);

	origilist<int>	real2(5, 0);
	jonaslist<int>	mine2(5, 0);
	REQUIRE(mine2 == real2);

	real1 = real2;
	mine1 = mine2;
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);

	real1 = origilist<int>();
	mine1 = jonaslist<int>();
	REQUIRE(mine1 == real1);
}

TEST_CASE("list begin end", "[list]")
{
	int intarr[] = {75,23,65,42,13};
	origilist<int>	real1(intarr, intarr + 5);
	jonaslist<int>	mine1(intarr, intarr + 5);
	REQUIRE(mine1 == real1);

	auto realIt1 = real1.begin();
	auto myIt1 = mine1.begin();
	REQUIRE(*realIt1 == *myIt1);

	for (; realIt1 != real1.end() && myIt1 != mine1.end(); realIt1++, myIt1++)
		REQUIRE(*realIt1 == *myIt1);

	// check last value, since end iterator is 1 past the end
	REQUIRE(*(--realIt1) == *(--myIt1));
}

TEST_CASE("list rbegin rend", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;

	for (int i = 1; i <= 5; ++i)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}

	auto realRevIt = real1.rbegin();
	auto myRevIt = mine1.rbegin();
	REQUIRE(*realRevIt == *myRevIt);

	for (; realRevIt != real1.rend() && myRevIt != mine1.rend(); realRevIt++, myRevIt++)
		REQUIRE(*realRevIt == *myRevIt);
	REQUIRE(*(--realRevIt) == *(--myRevIt));

	origilist<int>	real2(5);
	jonaslist<int>	mine2(5);
	REQUIRE(mine2 == real2);

	auto realRevIt1 = real2.rbegin();
	auto mineRevIt = mine2.rbegin();
	int i = 0;
	for (; realRevIt1 != real2.rend(); realRevIt1++)
		*realRevIt1 = ++i;
	i = 0;
	for (; mineRevIt != mine2.rend(); mineRevIt++)
		*mineRevIt = ++i;
	REQUIRE(mine2 == real2);
}

TEST_CASE("list empty", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;
	int	realsum(0);
	int minesum(0);

	for (int i = 1; i <= 10; i++)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}
	while (!real1.empty())
	{
		realsum += real1.front();
		real1.pop_front();
	}
	while (!mine1.empty())
	{
		minesum += mine1.front();
		mine1.pop_front();
	}
	REQUIRE(mine1 == real1);
	REQUIRE(minesum == realsum);
}

	TEST_CASE("list size", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;
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

TEST_CASE("list max size", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;

	for (int i = 0; i < 100; i++)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}
	REQUIRE(mine1 == real1);
//	REQUIRE(mine1.max_size() == real1.max_size());
}

