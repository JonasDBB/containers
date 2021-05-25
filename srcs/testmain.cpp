#include "containers/ft_stack.hpp"
#include "containers/ft_vector.hpp"
#include "containers/ft_queue.hpp"
#include "containers//ft_list.hpp"
#include <iostream>
#include <vector>
#include <list>

int		main(int ac, char **av)
{
	ft::list<int> lst;

	for (int i = 0; i < 5; i++)
		lst.push_front(i);
	for (int i = 0; i < 5; i++)
		lst.push_back(i);

#ifndef ASAN
	std::string line = av[0];
	line = "leaks " + line.substr(line.rfind('/') + 1, line.back()) +
		   " | grep \"total leaked bytes\"";
	system(line.c_str());
#endif
	(void) ac;
	(void) av;
}
