//#include "containers/ft_stack.hpp"
#include "containers/ft_vector.hpp"
//#include "containers/ft_queue.hpp"
#include "containers/ft_list.hpp"
#include <iostream>
#include <vector>
#include <list>


void	ittests()
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
//	if (rit1 == rit2)
//		std::cout << "yay" << std::endl;
//	if (rit2 == rit1)
//		std::cout << "yay" << std::endl;
}

void	lsttest()
{
	ft::list<int> lst;
	for (int i = 0; i < 5; i++)
		lst.push_back(i);
//	lst.assign(10, 15);
	lst.printlist();
	lst.printlistbackwards();
}


int		main(int ac, char **av)
{
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
