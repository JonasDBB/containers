#include "catch.hpp"
#include "../srcs/containers/ft_map.hpp"
#include <map>

namespace ft
{
	template<class T, class Alloc>
	bool operator==(const ft::map<T, Alloc> &mine,
					const std::map<T, Alloc> &real)
	{
		if (mine.size() != real.size())
			return (false);
		if (mine.get_allocator() != real.get_allocator())
			return (false);
		auto myit = mine.begin();
		auto realit = real.begin();
		for (size_t i = 0; i < mine.size(); ++i, ++myit, ++realit)
		{
			if (myit->first != realit->first || myit->second != realit->second)
				return (false);
		}
		return (true);
	}

	template<class T, class Alloc>
	bool operator==(const std::map<T, Alloc> &real,
					const ft::map<T, Alloc> &mine)
	{ return (mine == real); }

	template<class T, class Alloc>
	bool operator!=(const ft::map<T, Alloc> &mine,
					const std::map<T, Alloc> &real)
	{ return !(mine == real); }

	template<class T, class Alloc>
	bool operator!=(const std::map<T, Alloc> &real,
					const ft::map<T, Alloc> &mine)
	{ return !(mine == real); }

	template<class T, class Compare, class Alloc>
	bool operator==(const ft::map<T, Compare, Alloc> &mine,
					const std::map<T, Compare, Alloc> &real)
	{
		if (mine.size() != real.size())
			return (false);
		if (mine.get_allocator() != real.get_allocator())
			return (false);
		auto myit = mine.begin();
		auto realit = real.begin();
		for (size_t i = 0; i < mine.size(); ++i, ++myit, ++realit)
		{
			if (myit->first != realit->first || myit->second != realit->second)
				return (false);
		}
		return (true);
	}

	template<class T, class Compare, class Alloc>
	bool operator==(const std::map<T, Compare, Alloc> &real,
					const ft::map<T, Compare, Alloc> &mine)
	{ return (mine == real); }

	template<class T, class Compare, class Alloc>
	bool operator!=(const ft::map<T, Compare, Alloc> &mine,
					const std::map<T, Compare, Alloc> &real)
	{ return !(mine == real); }

	template<class T, class Compare, class Alloc>
	bool operator!=(const std::map<T, Compare, Alloc> &real,
					const ft::map<T, Compare, Alloc> &mine)
	{ return !(mine == real); }
}

#define origimap std::map
#define jonasmap ft::map

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

TEST_CASE("map constructors", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;
	REQUIRE(mine1 == real1);

	real1['a'] = 10;
	mine1['a'] = 10;
	real1['b'] = 30;
	mine1['b'] = 30;
	real1['c'] = 50;
	mine1['c'] = 50;
	real1['d'] = 70;
	mine1['d'] = 70;
	REQUIRE(mine1 == real1);

	origimap<char, int>	real2(real1.begin(), real1.end());
	jonasmap<char, int>	mine2(mine1.begin(), mine1.end());
	REQUIRE(mine2 == real2);

	origimap<char, int>	real3(real2);
	jonasmap<char, int>	mine3(mine2);
	REQUIRE(mine3 == real3);

	origimap<char, int, classcomp>	real4;
	jonasmap<char, int, classcomp>	mine4;
	REQUIRE(mine4 == real4);

	bool(*f)(char, char) = fncomp;
	origimap<char, int, bool(*)(char, char)>	real5(f);
	jonasmap<char, int, bool(*)(char, char)>	mine5(f);
	REQUIRE(mine5 == real5);
}

TEST_CASE("map assignment", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;
	origimap<char, int>	real2;
	jonasmap<char, int>	mine2;

	real1['x'] = 8;
	mine1['x'] = 8;
	real1['y'] = 16;
	mine1['y'] = 16;
	real1['z'] = 32;
	mine1['z'] = 32;

	real2 = real1;
	mine2 = mine1;
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);

	real1 = origimap<char, int>();
	mine1 = jonasmap<char, int>();
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);
}

TEST_CASE("map begin end", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;

	real1['b'] = 100;
	mine1['b'] = 100;
	real1['a'] = 200;
	mine1['a'] = 200;
	real1['c'] = 300;
	mine1['c'] = 300;
	auto realIt1 = real1.begin();
	auto myIt1 = mine1.begin();
	REQUIRE(myIt1->first == realIt1->first);
	REQUIRE(myIt1->second == realIt1->second);

	for (; realIt1 != real1.end() && myIt1 != mine1.end(); ++realIt1, ++myIt1)
	{
		REQUIRE(myIt1->first == realIt1->first);
		REQUIRE(myIt1->second == realIt1->second);
	}

	REQUIRE((--realIt1)->first == (--myIt1)->first);
	REQUIRE((--realIt1)->second == (--myIt1)->second);
}

TEST_CASE("map rbegin rend", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;

	real1['x'] = 100;
	mine1['x'] = 100;
	real1['y'] = 200;
	mine1['y'] = 200;
	real1['z'] = 300;
	mine1['z'] = 300;

	auto realRevIt1 = real1.rbegin();
	auto myRevIt1 = mine1.rbegin();
	REQUIRE(realRevIt1->first == myRevIt1->first);
	REQUIRE(realRevIt1->second == myRevIt1->second);

	for (; realRevIt1 != real1.rend() && myRevIt1 != mine1.rend(); ++realRevIt1, ++myRevIt1)
	{
		REQUIRE(realRevIt1->first == myRevIt1->first);
		REQUIRE(realRevIt1->second == myRevIt1->second);
	}

	REQUIRE((--realRevIt1)->first == (--myRevIt1)->first);
	REQUIRE((--realRevIt1)->second == (--myRevIt1)->second);
}

TEST_CASE("map empty", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;

	real1['b'] = 10;
	mine1['b'] = 10;
	real1['a'] = 20;
	mine1['a'] = 20;
	real1['c'] = 30;
	mine1['c'] = 30;

	int realSum = 0;
	while (!real1.empty())
	{
		++realSum;
		real1.erase(real1.begin());
	}

	int mySum = 0;
	while (!mine1.empty())
	{
		++mySum;
		mine1.erase(mine1.begin());
	}
	REQUIRE(mine1 == real1);
	REQUIRE(mySum == realSum);
}

TEST_CASE("map size", "[map]")
{
	origimap<char, int> real1;
	jonasmap<char, int> mine1;
	real1['a'] = 101;
	mine1['a'] = 101;
	real1['b'] = 202;
	mine1['b'] = 202;
	real1['c'] = 302;
	mine1['c'] = 302;
	REQUIRE(mine1.size() == real1.size());
}

//TEST_CASE("map max size", "[map]")
//{
//	// THIS WILL NOT WORK, MY MAPNODE IS NOT THE SAME AS THE REAL MAPNODE
//	origimap<int, int>	real1;
//	jonasmap<int, int>	mine1;
//	REQUIRE(mine1 == real1);
//	REQUIRE(mine1.max_size() == real1.max_size());
//}

TEST_CASE("map bracket operator", "[map]")
{
	origimap<char, std::string>	real1;
	jonasmap<char, std::string>	mine1;
	real1['a'] = "an elemenent";
	mine1['a'] = "an elemenent";
	real1['b'] = "another element";
	mine1['b'] = "another element";
	real1['c'] = real1['b'];
	mine1['c'] = mine1['b'];
	REQUIRE(mine1 == real1);

	std::string dummy;
	dummy = real1['d'];
	dummy = mine1['d'];
	REQUIRE(mine1 == real1);
}

TEST_CASE("map insert", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;
	real1.insert(std::pair<char, int>('a', 100));
	mine1.insert(ft::pair<char, int>('a', 100));
	real1.insert(std::pair<char, int>('z', 200));
	mine1.insert(ft::pair<char, int>('z', 200));
	REQUIRE(mine1 == real1);

	std::pair<origimap<char, int>::iterator, bool> realRet;
	ft::pair<jonasmap<char, int>::iterator, bool> myRet;
	realRet = real1.insert(std::pair<char, int>('z', 500));
	myRet = mine1.insert(ft::pair<char, int>('z', 500));
	REQUIRE(mine1 == real1);
	REQUIRE(realRet.second == myRet.second);

	auto realIt = real1.begin();
	auto myIt = mine1.begin();
	real1.insert(realIt, std::pair<char, int>('b', 300));
	mine1.insert(myIt, ft::pair<char, int>('b', 300));
	REQUIRE(mine1 == real1);
	real1.insert(realIt, std::pair<char, int>('c', 400));
	mine1.insert(myIt, ft::pair<char, int>('c', 400));
	REQUIRE(mine1 == real1);

	origimap<char, int>	real2;
	jonasmap<char, int>	mine2;
	real2.insert(real1.begin(), real1.find('c'));
	mine2.insert(mine1.begin(), mine1.find('c'));
	REQUIRE(mine2 == real2);
}

TEST_CASE("map erase", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;
	origimap<char, int>::iterator realIt;
	jonasmap<char, int>::iterator myIt;

	int n = 10;
	char c = 'a';
	for (int i = 0; i < 6; ++i, ++c, n += 10)
	{
		real1[c] = n;
		mine1[c] = n;
	}
	realIt = real1.find('b');
	myIt = mine1.find('b');
	REQUIRE(myIt->first == realIt->first);
	REQUIRE(myIt->second == realIt->second);

	real1.erase('c');
	mine1.erase('c');
	REQUIRE(mine1 == real1);

	realIt = real1.find('e');
	myIt = mine1.find('e');
	real1.erase(realIt, real1.end());
	mine1.erase(myIt, mine1.end());
	REQUIRE(mine1 == real1);
}

TEST_CASE("map swap", "[map]")
{
	origimap<char, int>	real1, real2;
	jonasmap<char, int>	mine1, mine2;
	real1['x'] = 100;

	mine1['x'] = 100;
	real1['y'] = 200;
	mine1['y'] = 200;
	real2['a'] = 11;

	mine2['a'] = 11;
	real2['b'] = 22;
	mine2['b'] = 22;
	real2['c'] = 33;
	mine2['c'] = 33;
	real1.swap(real2);

	mine1.swap(mine2);
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);
}

TEST_CASE("map clear", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;

	int n = 100;
	char c = 'x';
	for (int i = 0; i < 3; ++i, ++c, n += 100)
	{
		real1[c] = n;
		mine1[c] = n;
	}
	REQUIRE(mine1 == real1);

	real1.clear();
	mine1.clear();
	REQUIRE(mine1 == real1);

	real1['a'] = 1101;
	mine1['a'] = 1101;
	real1['b'] = 2202;
	mine1['b'] = 2202;
	REQUIRE(mine1 == real1);
}

TEST_CASE("map key comp", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;

	origimap<char, int>::key_compare realComp = real1.key_comp();
	jonasmap<char, int>::key_compare myComp = mine1.key_comp();

	int n = 100;
	char c = 'a';
	for (int i = 0; i < 3; ++i, ++c, n += 100)
	{
		real1[c] = n;
		mine1[c] = n;
	}
	char realHigh = real1.rbegin()->first;
	char myHigh = mine1.rbegin()->first;
	REQUIRE(realHigh == myHigh);

	auto realIt = real1.begin();
	auto myIt = mine1.begin();
	while (realComp((*realIt++).first, realHigh) && myComp((*myIt++).first, myHigh))
	{
		REQUIRE(realIt->first == myIt->first);
		REQUIRE(realIt->second == myIt->second);
	}
}

TEST_CASE("map value comp", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;

	int n = 1001;
	char c = 'x';
	for (int i = 0; i < 3; ++i, ++c, n += 1001)
	{
		real1[c] = n;
		mine1[c] = n;
	}
	REQUIRE(mine1 == real1);

	std::pair<char, int> realHigh(*real1.rbegin());
	ft::pair<char, int> myHigh(*mine1.rbegin());

	auto realIt = real1.begin();
	auto myIt = mine1.begin();
	while (real1.value_comp()(*realIt++, realHigh) && mine1.value_comp()(*myIt++, myHigh))
	{
		REQUIRE(realIt->first == myIt->first);
		REQUIRE(realIt->second == myIt->second);
	}
}

TEST_CASE("map find", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;
	origimap<char, int>::iterator realIt;
	jonasmap<char, int>::iterator myIt;
	int n = 50;
	char c = 'a';
	for (int i = 0; i < 4; ++i, ++c, n += 50)
	{
		real1[c] = n;
		mine1[c] = n;
	}

	realIt = real1.find('b');
	myIt = mine1.find('b');
	if (realIt != real1.end() && myIt != mine1.end())
	{
		REQUIRE(myIt->first == realIt->first);
		REQUIRE(myIt->second == realIt->second);
		real1.erase(realIt);
		mine1.erase(myIt);
	}
	else
	{
		REQUIRE(realIt == real1.end());
		REQUIRE(myIt == mine1.end());
	}
	REQUIRE(mine1 == real1);
}

TEST_CASE("map count", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;
	int n = 101;
	char c = 'a';
	for (int i = 0; i < 3; ++i, c += 2, n += 101)
	{
		real1[c] = n;
		mine1[c] = n;
	}
	REQUIRE(mine1 == real1);

	for (char a = 'a'; a < 'h'; ++a)
		REQUIRE(real1.count(a) == mine1.count(a));
}

TEST_CASE("map lower upper bound", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;
	origimap<char, int>::iterator realItLow, realItHigh;
	jonasmap<char, int>::iterator myItLow, myItHigh;

	int n = 20;
	char c = 'a';
	for (int i = 0; i < 5; ++i, ++c, n += 20)
	{
		real1[c] = n;
		mine1[c] = n;
	}

	realItLow = real1.lower_bound('b');
	myItLow = mine1.lower_bound('b');
	REQUIRE(myItLow->first == realItLow->first);
	REQUIRE(myItLow->second == realItLow->second);

	realItHigh = real1.upper_bound('d');
	myItHigh = mine1.upper_bound('d');
	REQUIRE(myItHigh->first == realItHigh->first);
	REQUIRE(myItHigh->second == realItHigh->second);

	real1.erase(realItLow, realItHigh);
	mine1.erase(myItLow, myItHigh);
	REQUIRE(mine1 == real1);
}

TEST_CASE("map equal range", "[map]")
{
	origimap<char, int>	real1;
	jonasmap<char, int>	mine1;

	int n = 10;
	char c = 'a';
	for (int i = 0; i < 3; ++i, ++c, n += 10)
	{
		real1[c] = n;
		mine1[c] = n;
	}

	std::pair<origimap<char, int>::iterator, origimap<char, int>::iterator> realRet;
	ft::pair<jonasmap<char, int>::iterator, jonasmap<char, int>::iterator> myRet;
	realRet = real1.equal_range('b');
	myRet = mine1.equal_range('b');
	REQUIRE(realRet.first->first == myRet.first->first);
	REQUIRE(realRet.first->second == myRet.first->second);
	REQUIRE(realRet.second->first == myRet.second->first);
	REQUIRE(realRet.second->second == myRet.second->second);
}

TEST_CASE("map relational operators", "[map]")
{
	origimap<char, int> real1;
	origimap<char, int> real2;
	jonasmap<char, int>	mine1;
	jonasmap<char, int>	mine2;

	real1['a'] = 100;
	mine1['a'] = 100;
	real1['b'] = 200;
	mine1['b'] = 200;

	real2['a'] = 10;
	mine2['a'] = 10;
	real2['z'] = 1000;
	mine2['z'] = 1000;

	REQUIRE((mine1 == mine2) == (real1 == real2));
	REQUIRE((mine1 != mine2) == (real1 != real2));
	REQUIRE((mine1 > mine2) == (real1 > real2));
	REQUIRE((mine1 < mine2) == (real1 < real2));
	REQUIRE((mine1 <= mine2) == (real1 <= real2));
	REQUIRE((mine1 >= mine2) == (real1 >= real2));
}

TEST_CASE("map swap overload", "[map]")
{
	origimap<char, int>	real1, real2;
	jonasmap<char, int>	mine1, mine2;
	real1['x'] = 100;

	mine1['x'] = 100;
	real1['y'] = 200;
	mine1['y'] = 200;
	real2['a'] = 11;

	mine2['a'] = 11;
	real2['b'] = 22;
	mine2['b'] = 22;
	real2['c'] = 33;
	mine2['c'] = 33;
	swap(real1, real2);

	swap(mine1, mine2);
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);
}


