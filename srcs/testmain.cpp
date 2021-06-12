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

bool compare_nocase (const std::string& first, const std::string& second)
{
	unsigned int i=0;
	while ( (i<first.length()) && (i<second.length()) )
	{
		if (tolower(first[i])<tolower(second[i])) return true;
		else if (tolower(first[i])>tolower(second[i])) return false;
		++i;
	}
	return ( first.length() < second.length() );
}

void	lsttest()
{
//	std::list<std::string> mylist;
//	std::list<std::string>::iterator it;
//	mylist.push_back ("one");
//	mylist.push_back ("two");
//	mylist.push_back ("Three");
//
//	mylist.sort();
//
//	std::cout << "mylist contains:";
//	for (it=mylist.begin(); it!=mylist.end(); ++it)
//		std::cout << ' ' << *it;
//	std::cout << '\n';
//
//	mylist.sort(compare_nocase);
//
//	std::cout << "mylist contains:";
//	for (it=mylist.begin(); it!=mylist.end(); ++it)
//		std::cout << ' ' << *it;
//	std::cout << std::endl;
//	std::string s(NULL);
//	ft::list<std::string> lst;
//	ft::list<std::string>::iterator it;
//	lst.push_back ("one");
//	lst.push_back ("two");
//	lst.push_back ("Three");
//	ft::list<int> lst(2, 3);
//	ft::list<int>::iterator it;
	ft::list<int> lst(2,3);
	ft::list<int>::iterator it = lst.begin();
	std::cout << *it << std::endl;
	*it = 5;
	std::cout << *it << std::endl;
//	std::cout << "lst:";
//	for (it = lst.begin(); it != lst.end(); ++it)
//		std::cout << ' ' << *it;
	std::cout << std::endl;
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
