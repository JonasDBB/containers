//#include "containers/ft_stack.hpp"
//#include "containers/ft_queue.hpp"
#include "containers/ft_vector.hpp"
//#include "iterators/BidirectionalIterator.hpp"
#include "containers/ft_stack.hpp"
#include "containers/ft_list.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <map>

void	ittests()
{
//	ft::vector<int> vec;
//	for (int i = 1; i <=5; i++)
//		vec.push_back(i);
//	ft::vector<int>::iterator it1 = vec.begin();
//	ft::vector<int>::const_iterator it2 = vec.begin();
//	for (; it1 != vec.end(); ++it1);
//	for (; it2 != vec.end(); ++it2);
//	if (it1 == it2)
//		;
//	if (it2 == it1)
//		;
//	ft::vector<int>::iterator it3;
//	it3 = it2;
//
//	ft::vector<int>::reverse_iterator rit1 = vec.rbegin();
//	ft::vector<int>::const_reverse_iterator rit2 = vec.rbegin();
//	for (; rit1 != vec.rend(); ++rit1);
//	for (; rit2 != vec.rend(); ++rit2);
//	if (rit1 == rit2)
//		;
//	if (rit2 == rit1)
//		;
//	ft::vector<int>::const_reverse_iterator rit3;
//	rit3 = rit1;
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

template <class T1, class T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& pr)
{
	os << "first: " << pr.first << "\tsecond: " << pr.second;
	return (os);
}

//void	mappies()
//{
//
//}
#include <stack>
int		main(int ac, char **av)
{
//	ittests();
//	mappies();

	ft::stack<int, ft::vector<int> > stk1;
	for (int i = 0; i < 5; ++i)
		stk1.push(i);
	ft::stack<int, ft::vector<int> > stk2(stk1);
	ft::stack<int, ft::vector<int> > stk3 = stk2;
	while (!stk1.empty())
	{
		std::cout << stk1.top() << " ";
		stk1.pop();
	}
	std::cout << std::endl;
	while (!stk2.empty())
	{
		std::cout << stk2.top() << " ";
		stk2.pop();
	}
	std::cout << std::endl;
	while (!stk3.empty())
	{
		std::cout << stk3.top() << " ";
		stk3.pop();
	}
	std::cout << std::endl;


#ifndef ASAN
	std::string line = av[0];
	line = "leaks " + line.substr(line.rfind('/') + 1, line.back()) +
		   " | grep \"total leaked bytes\"";
	system(line.c_str());
#endif
	(void) ac;
	(void) av;
}



