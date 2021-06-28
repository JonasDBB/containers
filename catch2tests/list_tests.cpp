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

	for (; realIt1 != real1.end() && myIt1 != mine1.end(); ++realIt1, ++myIt1)
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
	// THIS WILL NOT WORK, MY LISTNODE IS NOT THE SAME AS THE REAL LISTNODE

//	origilist<int>	real1;
//	jonaslist<int>	mine1;
//	REQUIRE(mine1 == real1);
//	REQUIRE(mine1.max_size() == real1.max_size());
}

TEST_CASE("list front", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;

	real1.push_back(77);
	mine1.push_back(77);
	real1.push_back(22);
	mine1.push_back(22);

	real1.front() -= real1.back();
	mine1.front() -= mine1.back();
	REQUIRE(mine1 == real1);
}

TEST_CASE("list back", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;

	real1.push_back(10);
	mine1.push_back(10);
	while (real1.back() != 0)
		real1.push_back((real1.back() - 1));
	while (mine1.back() != 0)
		mine1.push_back((mine1.back() - 1));
	REQUIRE(mine1 == real1);
}

TEST_CASE("list assign", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;
	origilist<int>	real2;
	jonaslist<int>	mine2;

	real1.assign(7, 100);
	mine1. assign(7, 100);
	REQUIRE(mine1 == real1);

	real2.assign(real1.begin(), real1.end());
	mine2.assign(mine1.begin(), mine1.end());
	REQUIRE(mine2 == mine1);

	int intarr[] = {1776, 7, 4};
	real1.assign(intarr, intarr + 3);
	mine1.assign(intarr, intarr + 3);
	REQUIRE(mine1 == real1);
}

TEST_CASE("list push front", "[list]")
{
	origilist<int>	real1(2, 100);
	jonaslist<int>	mine1(2, 100);

	real1.push_back(200);
	mine1.push_back(200);
	REQUIRE(mine1 == real1);

	real1.push_back(300);
	mine1.push_back(300);
	REQUIRE(mine1 == real1);
}

TEST_CASE("list pop front", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;

	real1.push_back(100);
	mine1.push_back(100);
	real1.push_back(200);
	mine1.push_back(200);
	real1.push_back(300);
	mine1.push_back(300);

	int realN = 0;
	while (!real1.empty())
	{
		real1.pop_front();
		++realN;
	}

	int mineN = 0;
	while (!mine1.empty())
	{
		mine1.pop_front();
		++mineN;
	}
	REQUIRE(mine1 == real1);
	REQUIRE(realN == mineN);
}

TEST_CASE("list push back", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;

	real1.push_back(100);
	mine1.push_back(100);
	REQUIRE(mine1 == real1);
}

TEST_CASE("list pop back", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;
	int realSum = 0;
	int mineSum = 0;
	real1.push_back(100);
	mine1.push_back(100);
	real1.push_back(200);
	mine1.push_back(200);
	real1.push_back(300);
	mine1.push_back(300);

	while (!real1.empty())
	{
		realSum += real1.back();
		real1.pop_back();
	}

	while (!mine1.empty())
	{
		mineSum += mine1.back();
		mine1.pop_back();
	}
	REQUIRE(mine1 == real1);
	REQUIRE(mineSum == realSum);
}

TEST_CASE("list insert", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;
	auto realIt = real1.begin();
	auto mineIt = mine1.begin();
	for (int i = 1; i <= 5; ++i)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}
	++realIt;
	++mineIt;
	real1.insert(realIt, 10);
	mine1.insert(mineIt, 10);
	REQUIRE(mine1 == real1);

	real1.insert(realIt, 2, 20);
	mine1.insert(mineIt, 2, 20);
	REQUIRE(mine1 == real1);

	--realIt;
	--mineIt;

	std::vector<int> vec(2, 30);
	real1.insert(realIt, vec.begin(), vec.end());
	mine1.insert(mineIt, vec.begin(), vec.end());
	REQUIRE(mine1 == real1);
}

TEST_CASE("list erase", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;
	std::list<int>::iterator realIt1, realIt2;
	ft::list<int>::iterator mineIt1, mineIt2;
	realIt1 = realIt2 = real1.begin();
	mineIt1 = mineIt2 = mine1.begin();

	for (int i = 1; i < 10; ++i)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}
	REQUIRE(mine1 == real1);
	std::advance(realIt2, 6);
	ft::advance(mineIt2, 6);
	++realIt1;
	++mineIt1;
	REQUIRE(*mineIt1 == *realIt1);
	REQUIRE(*mineIt2 == *realIt2);

	realIt1 = real1.erase(realIt1);
	mineIt1 = mine1.erase(mineIt1);
	REQUIRE(mine1 == real1);
	REQUIRE(*mineIt1 == *realIt1);

	realIt2 = real1.erase(realIt2);
	mineIt2 = mine1.erase(mineIt2);
	REQUIRE(mine1 == real1);
	REQUIRE(*mineIt2 == *realIt2);

	++realIt1;
	++mineIt1;
	--realIt2;
	--mineIt2;

	real1.erase(realIt1, realIt2);
	mine1.erase(mineIt1, mineIt2);
	REQUIRE(mine1 == real1);
}

TEST_CASE("list swap", "[list]")
{
	origilist<int>	real1(3, 100);
	jonaslist<int>	mine1(3, 100);
	origilist<int>	real2(5, 200);
	jonaslist<int>	mine2(5, 200);

	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);
	real1.swap(real2);
	mine1.swap(mine2);
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);
}

TEST_CASE("list resize", "[list]")
{
	origilist<int> real1;
	jonaslist<int> mine1;
	for (int i = 1; i < 10; ++i)
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

TEST_CASE("list clear", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;

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

TEST_CASE("list splice", "[list]")
{
	origilist<int> real1, real2;
	jonaslist<int> mine1, mine2;
	origilist<int>::iterator realIt;
	jonaslist<int>::iterator mineIt;

	for (int i = 1; i < 5; ++i)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}
	for (int i = 1; i < 4; ++i)
	{
		real2.push_back(i);
		mine2.push_back(i);
	}
	realIt = real1.begin();
	mineIt = mine1.begin();
	++realIt;
	++mineIt;

	real1.splice(realIt, real2);
	mine1.splice(mineIt, mine2);
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);

	real2.splice(real2.begin(), real1, realIt);
	mine2.splice(mine2.begin(), mine1, mineIt);
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);

	realIt = real1.begin();
	mineIt = mine1.begin();
	std::advance(realIt, 3);
	ft::advance(mineIt, 3);
	real1.splice(real1.begin(), real1, realIt, real1.end());
	mine1.splice(mine1.begin(), mine1, mineIt, mine1.end());
	REQUIRE(mine1 == real1);
}

TEST_CASE("list remove", "[list]")
{
	int intarr[] = {17, 89, 7, 14};
	origilist<int>	real1(intarr, intarr + 4);
	jonaslist<int>	mine1(intarr, intarr + 4);

	real1.remove(89);
	mine1.remove(89);
	REQUIRE(mine1 == real1);

	real1.remove(55);
	mine1.remove(55);
	REQUIRE(mine1 == real1);
}

bool	single_digit(const int& value)
{ return (value<10); }

struct	is_odd {
	bool	operator()(const int& value)
	{ return (value % 2) == 1; }
};

TEST_CASE("list remove_if", "[list]")
{
	int intarr[] = {15, 36, 7, 17, 20, 39, 4, 1};
	origilist<int>	real1(intarr, intarr + 8);
	jonaslist<int>	mine1(intarr, intarr + 8);

	real1.remove_if(single_digit);
	mine1.remove_if(single_digit);
	REQUIRE(mine1 == real1);

	real1.remove_if(is_odd());
	mine1.remove_if(is_odd());
	REQUIRE(mine1 == real1);
}

bool	same_integral_part(double first, double second)
{ return(int(first)==int(second)); }

struct	is_near {
	bool	operator()(double first, double second)
	{ return (fabs(first - second) < 5.0); }
};

TEST_CASE("list unique", "[list]")
{
	double	dubarr[] = {12.15,  2.72, 73.0,  12.77,  3.14, 12.77, 73.35, 72.25, 15.3, 72.25};
	origilist<double>	real1(dubarr, dubarr + 10);
	jonaslist<double>	mine1(dubarr, dubarr + 10);

	real1.sort();
	mine1.sort();
	REQUIRE(mine1 == real1);

	real1.unique();
	mine1.unique();
	REQUIRE(mine1 == real1);

	real1.unique(same_integral_part);
	mine1.unique(same_integral_part);
	REQUIRE(mine1 == real1);

	real1.unique(is_near());
	mine1.unique(is_near());
	REQUIRE(mine1 == real1);
}

bool	mycomparison(double first, double second)
{ return(int(first) < int(second)); }

TEST_CASE("list merge", "[list]")
{
	origilist<double>	real1, real2;
	jonaslist<double>	mine1, mine2;

	real1.push_back(3.1);
	mine1.push_back(3.1);
	real1.push_back(2.2);
	mine1.push_back(2.2);
	real1.push_back(2.9);
	mine1.push_back(2.9);

	real2.push_back(3.7);
	mine2.push_back(3.7);
	real2.push_back(7.1);
	mine2.push_back(7.1);
	real2.push_back(1.4);
	mine2.push_back(1.4);

	real1.sort();
	mine1.sort();
	real2.sort();
	mine2.sort();
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);

	real1.merge(real2);
	mine1.merge(mine2);
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);

	real2.push_back(2.1);
	mine2.push_back(2.1);

	real1.merge(real2, mycomparison);
	mine1.merge(mine2, mycomparison);
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);
}

bool	compare_nocase(const std::string& first, const std::string& second)
{
	unsigned int i = 0;
	while ((i < first.length()) && (i < second.length()))
	{
		if (tolower(first[i]) < tolower(second[i])) return true;
		else if (tolower(first[i]) > tolower(second[i])) return false;
		++i;
	}
	return (first.length() < second.length());
}

TEST_CASE("list sort", "[list]")
{
	origilist<std::string>	real1;
	jonaslist<std::string>	mine1;

	real1.push_back("one");
	mine1.push_back("one");
	real1.push_back("two");
	mine1.push_back("two");
	real1.push_back("Three");
	mine1.push_back("Three");

	real1.sort();
	mine1.sort();
	auto realit = real1.begin();
	auto mineit = mine1.begin();
	REQUIRE(mine1 == real1);

	real1.sort(compare_nocase);
	mine1.sort(compare_nocase);
	realit = real1.begin();
	mineit = mine1.begin();
	REQUIRE(mine1 == real1);
}

TEST_CASE("list reverse", "[list]")
{
	origilist<int>	real1;
	jonaslist<int>	mine1;

	for (int i = 1; i < 10; ++i)
	{
		real1.push_back(i);
		mine1.push_back(i);
	}

	real1.reverse();
	mine1.reverse();
	REQUIRE(mine1 == real1);
}

TEST_CASE("list relational operators", "[list]")
{
	origilist<int>	real1(3, 100);
	jonaslist<int>	mine1(3, 100);
	origilist<int>	real2(2, 200);
	jonaslist<int>	mine2(2, 200);

	REQUIRE((mine1 == mine2) == (real1 == real2));
	REQUIRE((mine1 != mine2) == (real1 != real2));
	REQUIRE((mine1 > mine2) == (real1 > real2));
	REQUIRE((mine1 < mine2) == (real1 < real2));
	REQUIRE((mine1 <= mine2) == (real1 <= real2));
	REQUIRE((mine1 >= mine2) == (real1 >= real2));
}

TEST_CASE("list swap overload", "[list]")
{
	origilist<int>	real1(3, 100);
	jonaslist<int>	mine1(3, 100);
	origilist<int>	real2(5, 200);
	jonaslist<int>	mine2(5, 200);

	swap(real1, real2);
	swap(mine1, mine2);
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);
}
