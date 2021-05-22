#include "containers/ft_stack.hpp"
#include "containers/ft_vector.hpp"
#include <iostream>
#include <vector>
int		main(int ac, char **av)
{
	ft::vector<int> vec1(5, 100);


	ft::vector<int>::iterator it1 = vec1.begin();
	ft::vector<int>::const_iterator it2 = vec1.begin();
//	ft::vector<int>::const_iterator it3(it1);
//	if (it1 == it2)
//		std::cout << "yay" << std::endl;
//	else
//		std::cout << "sad" << std::endl;

#ifndef ASAN
	std::string line = av[0];
	line = "leaks " + line.substr(line.rfind('/') + 1, line.back()) +
		   " | grep \"total leaked bytes\"";
	system(line.c_str());
#endif
	(void) ac;
	(void) av;
}
