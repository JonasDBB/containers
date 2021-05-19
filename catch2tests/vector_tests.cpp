#include "catch.hpp"
#include "../srcs/ft_vector.hpp"
#include <vector>

#define realvect std::vector
#define myvector ft::vector

TEST_CASE("vector constructors", "[vector]")
{
	realvect<int>	real1;
	myvector<int>	mine1;
	REQUIRE(mine1 == real1);

	realvect<int>	real2(4, 100);
	myvector<int>	mine2(4, 100);
	REQUIRE(mine2 == real2);

	realvect<int>	real3(real2.begin(), real2.end());
	myvector<int>	mine3(mine2.begin(), mine2.end());
	REQUIRE(mine3 == real3);

	realvect<int>	real4(real3);
	myvector<int>	mine4(mine3);
	REQUIRE(mine4 == real4);

	int intarr[] = {16, 2, 77, 29};
	realvect<int>	real5(intarr, intarr + sizeof(intarr) / sizeof(int));
	myvector<int>	mine5(intarr, intarr + sizeof(intarr) / sizeof(int));
	REQUIRE(mine5 == real5);
}

TEST_CASE("vector assignment", "[vector]")
{
	realvect<int>	real1(3, 0);
	myvector<int>	mine1(3, 0);
	REQUIRE(mine1 == real1);

	realvect<int>	real2(5, 0);
	myvector<int>	mine2(5, 0);
	REQUIRE(mine2 == real2);

	real1 = real2;
	mine1 = mine2;
	REQUIRE(mine1 == real1);
	REQUIRE(mine2 == real2);

	real1 = realvect<int>();
	mine1 = myvector<int>();
	REQUIRE(mine1 == real1);
}

TEST_CASE("vector begin end", "[vector]")
{
	realvect<int>	real1;
	myvector<int>	mine1;
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
	realvect<int>	real1(5);
	myvector<int>	mine1(5);
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

TEST_CASE("const it", "[vector]")
{

}

