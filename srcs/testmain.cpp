//#include "containers/ft_stack.hpp"
//#include "containers/ft_queue.hpp"
#include "containers/ft_vector.hpp"
//#include "iterators/BidirectionalIterator.hpp"
#include "containers/ft_list.hpp"
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

void	lsttest()
{
	ft::list<int> lst;
//	const ft::list<int> lst1(5,3);
	for (int i = 1; i <= 14; i++)
		lst.push_back(i);
	lst.reverse();
	lst.printlist();
//	ft::list<int>::iterator it1 = lst1.end();
//	ft::list<int>::const_iterator it2 = lst1.end();
//
//	if (it1 == it2)
//		std::cout << "yay" << std::endl;
//	if (it2 == it1)
//		std::cout << "yay" << std::endl;
//
//	ft::list<int>::iterator it3;
//	it3 = it2;

//	ft::list<int> a;
//	a.push_back(10);
//	a.push_back(20);
//	a.push_back(30);
//	ft::list<int> b(a);
//	ft::list<int> c(b);
//	c.reverse();
//
//	if (a==b) std::cout << "a and b are equal\n";
//	if (b!=c) std::cout << "b and c are not equal\n";
//	if (b<c) std::cout << "b is less than c\n";
//	if (c>b) std::cout << "c is greater than b\n";
//	if (a<=b) std::cout << "a is less than or equal to b\n";
//	if (a>=b) std::cout << "a is greater than or equal to b\n";
//	std::cout << std::endl;
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
