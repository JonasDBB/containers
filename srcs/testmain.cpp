//#include "containers/ft_stack.hpp"
#include "containers/ft_vector.hpp"
//#include "containers/ft_queue.hpp"
#include "containers/ft_list.hpp"
#include <iostream>
#include <vector>
#include <list>

int		main(int ac, char **av)
{
	ft::vector<int> vec(4, 5);

	ft::vector<int>::iterator it1 = vec.begin();
	ft::vector<int>::const_iterator it2 = vec.begin();
	if (it1 == it2)
		std::cout << "yay" << std::endl;
	if (it2 == it1)
		std::cout << "yay" << std::endl;

	ft::vector<int>::iterator it3;
	it3 = it2;

	ft::vector<int>::reverse_iterator rit1 = vec.rbegin();
	ft::vector<int>::const_reverse_iterator rit2 = vec.rbegin();
	if (rit1 == rit2)
		std::cout << "yay" << std::endl;



	//	for (int i = 1; i < 5; i++)
//		lst.push_back(i);
//	lst.printlist();
////	lst.printlistbackwards();
//	std::list<int>::iterator it1 = lst.begin();
//	std::cout << "addr " << &(*it1) << std::endl;
//	std::cout << "it =" << *it1 << "=" << std::endl;
//	std::cout << "addr " << &(*it1) << std::endl;
//	it1++;
//	std::cout << "addr " << &(*it1) << std::endl;
//	std::cout << "it =" << *it1 << "=" << std::endl;
//	std::cout << "addr " << &(*it1) << std::endl;
//	ft::list<int> lst2(lst);
//	lst2.printlist();
//	lst2.printlistbackwards();
//	for (int i = 0; i < 5; i++)
//		lst.push_back(i);
//
//	lst.clear();

#ifndef ASAN
	std::string line = av[0];
	line = "leaks " + line.substr(line.rfind('/') + 1, line.back()) +
		   " | grep \"total leaked bytes\"";
	system(line.c_str());
#endif
	(void) ac;
	(void) av;
}
