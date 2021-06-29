//#include "containers/ft_stack.hpp"
//#include "containers/ft_queue.hpp"
#include "containers/ft_vector.hpp"
//#include "iterators/BidirectionalIterator.hpp"
#include "containers/ft_list.hpp"
#include "utils/ListNode.hpp"
#include <iostream>
#include <vector>
#include <list>

void	ittests()
{
	ft::vector<int> vec;
	for (int i = 1; i <=5; i++)
		vec.push_back(i);
	ft::vector<int>::iterator it1 = vec.begin();
	ft::vector<int>::const_iterator it2 = vec.begin();
	for (; it1 != vec.end(); ++it1);
	for (; it2 != vec.end(); ++it2);
	if (it1 == it2)
		;
	if (it2 == it1)
		;
	ft::vector<int>::const_iterator it3;
	it3 = it1;

	ft::vector<int>::reverse_iterator rit1 = vec.rbegin();
	ft::vector<int>::const_reverse_iterator rit2 = vec.rbegin();
	for (; rit1 != vec.rend(); ++rit1);
	for (; rit2 != vec.rend(); ++rit2);
	if (rit1 == rit2)
		;
	if (rit2 == rit1)
		;
	ft::vector<int>::reverse_iterator rit3;
	rit3 = rit2;
}

class testclass {
private:
	int x;
public:
	testclass() {}
	testclass(int x) : x(x){}
	int	getx() const {return this->x;}
	bool operator==(const testclass rhs) const
	{return (this->x == rhs.x);}
	bool operator!=(const testclass rhs) const
	{return (this->x != rhs.x);}
	bool operator<(const testclass& rhs) const
	{return (this->x < rhs.x);}
	bool operator>(const testclass& rhs) const
	{return (this-> x > rhs.x);}
	bool operator>=(const testclass& rhs) const
	{return (this-> x >= rhs.x);}
	bool operator<=(const testclass& rhs) const
	{return (this-> x <= rhs.x);}

};

bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

void	lsttest()
{
	std::list<std::string>	lst0(5, "hey");
	ft::list<std::string>	lst1(4, "hey");
	std::list<std::string>::iterator	it0(lst0.begin());
	ft::list<std::string>::iterator		it1(lst1.begin());
	for (; it0 != lst0.end() && it1 != lst1.end(); ++it0, ++it1)
	{
		if (*it0 == *it1)
			std::cout << "it workie" << std::endl;
	}
}


int		main(int ac, char **av)
{
	ittests();
//	lsttest();

#ifndef ASAN
	std::string line = av[0];
	line = "leaks " + line.substr(line.rfind('/') + 1, line.back()) +
		   " | grep \"total leaked bytes\"";
	system(line.c_str());
#endif
	(void) ac;
	(void) av;
}



