#include "catch.hpp"
#include "../srcs/containers/ft_queue.hpp"
#include <queue>
#include <iostream>
#include <list>

namespace ft
{
	template<class T, class Container>
	bool operator==(const ft::queue<T, Container> &mine, const std::queue<T, Container> &real)
	{
		if (mine.empty() != real.empty())
			return (false);
		if (mine.size() != real.size())
			return (false);
		ft::queue<T, Container> myTmp(mine);
		std::queue<T, Container> rlTmp(real);
		for (size_t i = real.size(); i; i--)
		{
			if (myTmp.front() != rlTmp.front())
				return (false);
			if (myTmp.back() != rlTmp.back())
				return (false);
			myTmp.pop();
			rlTmp.pop();
		}
		return (true);
	}

	template<class T, class Container>
	bool operator==(const std::queue<T, Container> &real, const ft::queue<T, Container> &mine)
	{ return (mine == real); }

	template<class T, class Container>
	bool operator!=(const ft::queue<T, Container> &mine, const std::queue<T, Container> &real)
	{ return !(mine == real); }

	template<class T, class Container>
	bool operator!=(const std::queue<T, Container> &real, const ft::queue<T, Container> &mine)
	{ return !(mine == real); }
}

#define origiqueue std::queue
#define jonasqueue ft::queue

TEST_CASE("queue constructor", "[queue]")
{
	origiqueue<int>	real1;
	jonasqueue<int>	mine1;
	REQUIRE(mine1 == real1);

	std::list<int>		lst(3, 100);
	std::deque<int>		deq(2, 200);

	origiqueue<int>	real2(deq);
	jonasqueue<int>	mine2(deq);
	REQUIRE(mine2 == real2);

	origiqueue<int, std::list<int> >	real3;
	jonasqueue<int, std::list<int> >	mine3;
	REQUIRE(mine3 == real3);

	origiqueue<int, std::list<int> >	real4(lst);
	jonasqueue<int, std::list<int> >	mine4(lst);
	REQUIRE(mine4 == real4);
}

TEST_CASE("queue push", "[queue]")
{
	origiqueue<int>	real1;
	jonasqueue<int>	mine1;

	for (int i = 1; i <= 10; i++)
	{
		real1.push(i);
		mine1.push(i);
	}
	REQUIRE(mine1 == real1);
}

TEST_CASE("queue empty", "[queue]")
{
	origiqueue<int>	real1;
	jonasqueue<int>	mine1;

	for (int i = 1; i <= 10; i++)
	{
		real1.push(i);
		mine1.push(i);
	}
	int realSum(0), mineSum(0);
	while (!real1.empty())
	{
		realSum += real1.front();
		real1.pop();
	}
	while (!mine1.empty())
	{
		mineSum += mine1.front();
		mine1.pop();
	}
	REQUIRE(mine1 == real1);
	REQUIRE(mineSum == realSum);
}

TEST_CASE("queue size", "[queue]")
{
	origiqueue<int>	real1;
	jonasqueue<int>	mine1;

	REQUIRE(mine1 == real1);
	for (int i = 1; i <= 10; i++)
	{
		real1.push(i);
		mine1.push(i);
	}
	REQUIRE(mine1 == real1);
	real1.pop();
	mine1.pop();
	REQUIRE(mine1 == real1);
}

TEST_CASE("queue front", "[queue]")
{
	origiqueue<int>	real1;
	jonasqueue<int>	mine1;

	real1.push(77);
	mine1.push(77);

	real1.push(16);
	mine1.push(16);
	REQUIRE(mine1 == real1);

	real1.front() -= real1.back();
	mine1.front() -= mine1.back();
	REQUIRE(mine1 == real1);
}

TEST_CASE("queue back", "[queue]")
{
	origiqueue<int>	real1;
	jonasqueue<int>	mine1;

	real1.push(12);
	mine1.push(12);

	real1.push(75);
	mine1.push(75);
	REQUIRE(mine1 == real1);

	real1.back() -= real1.front();
	mine1.back() -= mine1.front();
	REQUIRE(mine1 == real1);
}

TEST_CASE("queue pop", "[queue]")
{
	origiqueue<int>	real1;
	jonasqueue<int>	mine1;
	for (int i = 0; i < 5; i++)
	{
		real1.push(i);
		mine1.push(i);
	}
	while (!real1.empty())
		real1.pop();
	while (!mine1.empty())
		mine1.pop();
	REQUIRE(mine1 == real1);
}

TEST_CASE("queue relational operators", "[queue]")
{
	origiqueue<int>	real1;
	jonasqueue<int>	mine1;
	origiqueue<int>	real2;
	jonasqueue<int>	mine2;

	for (int i = 0; i < 3; i++)
	{
		real1.push(100);
		mine1.push(100);
	}

	for (int i = 0; i < 2; i++)
	{
		real2.push(200);
		mine2.push(200);
	}

	REQUIRE_FALSE(real1 == real2);
	REQUIRE_FALSE(mine1 == mine2);

	REQUIRE((mine1 == mine2) == (real1 == real2));
	REQUIRE((mine1 != mine2) == (real1 != real2));
	REQUIRE((mine1 > mine2) == (real1 > real2));
	REQUIRE((mine1 < mine2) == (real1 < real2));
	REQUIRE((mine1 <= mine2) == (real1 <= real2));
	REQUIRE((mine1 >= mine2) == (real1 >= real2));
}
