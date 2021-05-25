#include "containers/ft_stack.hpp"
#include "containers/ft_vector.hpp"
#include "containers/ft_queue.hpp"
#include "containers//ft_list.hpp"
#include <iostream>
#include <vector>
#include <list>

int		main(int ac, char **av)
{
	std::list<int> lst(5, 10);
	std::list<int>::iterator it1 = lst.begin();
	std::list<int>::iterator it2 = lst.begin();
	it2++;
//	if (it1 < it2)
//		std::cout << "yay";
#ifndef ASAN
	std::string line = av[0];
	line = "leaks " + line.substr(line.rfind('/') + 1, line.back()) +
		   " | grep \"total leaked bytes\"";
	system(line.c_str());
#endif
	(void) ac;
	(void) av;
}
