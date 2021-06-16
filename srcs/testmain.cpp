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
//	ft::vector<int>::const_iterator it2 = vec.begin();
//	if (it1 == it2)
//		std::cout << "yay" << std::endl;
//	if (it2 == it1)
//		std::cout << "yay" << std::endl;
//
//	ft::vector<int>::iterator it3;
//	it3 = it2;
//
//	ft::vector<int>::reverse_iterator rit1 = vec.rbegin();
//	ft::vector<int>::const_reverse_iterator rit2 = vec.rbegin();
//	if (rit1 == rit2)
//		std::cout << "yay" << std::endl;
//	if (rit2 == rit1)
//		std::cout << "yay" << std::endl;
}

bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

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

std::ostream& operator<<(std::ostream& os, const testclass &cls)
{os << cls.getx(); return os;}

void	lsttest()
{
	ft::list<int> first (3,100);   // three ints with a value of 100
	ft::list<int> second (5,200);  // five ints with a value of 200

	first.swap(second);

	std::cout << "first contains:";
	for (ft::list<int>::iterator it=first.begin(); it!=first.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (ft::list<int>::iterator it=second.begin(); it!=second.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
}


int		main(int ac, char **av)
{
//	ittests();
	lsttest();

#ifndef ASAN
	std::string line = av[0];
	line = "leaks " + line.substr(line.rfind('/') + 1, line.back()) +
		   " | grep \"total leaked bytes\"";
	system(line.c_str());
#endif
	(void) ac;
	(void) av;
}



