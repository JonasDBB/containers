#include "catch.hpp"
#include "../srcs/containers/ft_stack.hpp"
#include "../srcs/containers/ft_vector.hpp"
#include <stack>
#include <iostream>

namespace ft
{
	template<class T, class Container>
	bool operator==(const ft::stack<T, Container> &mine, const std::stack<T, Container> &real)
	{
		if (mine.empty() != real.empty())
			return (false);
		if (mine.size() != real.size())
			return (false);
		ft::stack<T, Container> myTmp(mine);
		std::stack<T, Container> rlTmp(real);
		for (size_t i = real.size(); i; i--)
		{
			if (myTmp.top() != rlTmp.top())
				return (false);
			myTmp.pop();
			rlTmp.pop();
		}
		return (true);
	}

	template<class T, class Container>
	bool operator==(const std::stack<T, Container> &real, const ft::stack<T, Container> &mine)
	{ return (mine == real); }

	template<class T, class Container>
	bool operator!=(const ft::stack<T, Container> &mine, const std::stack<T, Container> &real)
	{ return !(mine == real); }

	template<class T, class Container>
	bool operator!=(const std::stack<T, Container> &real, const ft::stack<T, Container> &mine)
	{ return !(mine == real); }
}

#define origistack std::stack
#define jonasstack ft::stack

TEST_CASE("stack constructor", "[stack]")
{
	origistack<int>	real1;
	jonasstack<int>	mine1;
	REQUIRE(mine1 == real1);

	ft::vector<int>		myvec(3, 100);
	std::vector<int>	realvec(3, 100);
	std::deque<int>		deq(2, 200);

	origistack<int>	real2(deq);
	jonasstack<int>	mine2(deq);
	REQUIRE(mine2 == real2);

	origistack<int, std::vector<int> >	real3;
	jonasstack<int, std::vector<int> >	mine3;
	REQUIRE(mine3 == real3);

	origistack<int, std::vector<int> >	real4(realvec);
	jonasstack<int, std::vector<int> >	mine4(realvec);
	REQUIRE(mine4 == real4);

	origistack<int, ft::vector<int> >	real5(myvec);
	jonasstack<int, ft::vector<int> >	mine5(myvec);
	REQUIRE(mine5 == real5);

}

TEST_CASE("stack push", "[stack]")
{
	origistack<int>	real1;
	jonasstack<int>	mine1;

	for (int i = 1; i <= 10; i++)
	{
		real1.push(i);
		mine1.push(i);
	}
	REQUIRE(mine1 == real1);
}

TEST_CASE("stack empty", "[stack]")
{
	origistack<int>	real1;
	jonasstack<int>	mine1;

	for (int i = 1; i <= 10; i++)
	{
		real1.push(i);
		mine1.push(i);
	}
	int realSum(0), mineSum(0);
	while (!real1.empty())
	{
		realSum += real1.top();
		real1.pop();
	}
	while (!mine1.empty())
	{
		mineSum += mine1.top();
		mine1.pop();
	}
	REQUIRE(mine1 == real1);
	REQUIRE(mineSum == realSum);
}

TEST_CASE("stack size", "[stack]")
{
	origistack<int>	real1;
	jonasstack<int>	mine1;

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

TEST_CASE("stack top", "[stack]")
{
	origistack<int>	real1;
	jonasstack<int>	mine1;

	real1.push(10);
	mine1.push(10);

	real1.push(20);
	mine1.push(20);
	REQUIRE(mine1 == real1);

	real1.top() -= 5;
	mine1.top() -=5;
	REQUIRE(mine1 == real1);
}

TEST_CASE("stack pop", "[stack]")
{
	origistack<int>	real1;
	jonasstack<int>	mine1;
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

TEST_CASE("stack relational operators", "[stack]")
{
	origistack<int>	real1;
	jonasstack<int>	mine1;
	origistack<int>	real2;
	jonasstack<int>	mine2;

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
