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
#include <cmath>
// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
struct is_near {
	bool operator()(double first, double second)
	{ return (fabs(first - second) < 5.0); }
};
void	lsttest()
{
//	ft::list<int> lst1;
//
//	for (int i = 1; i <= 5; i++)
//		lst1.push_back(i);
//
//	ft::list<int> lst2;
//	lst2.assign(lst1.rbegin(), lst1.rend());
//	lst1.assign(3, 5);
//	for (ft::list<int>::iterator it = lst2.begin(); it != lst2.end(); it++)
//		std::cout << *it << std::endl;
//	for (ft::list<int>::iterator it = lst1.begin(); it != lst1.end(); it++)
//		std::cout << *it << std::endl;

	double mydoubles[]={ 2.72,  3.14, 12.15, 12.77, 12.77,
			 15.3,  72.25, 72.25, 73.0,  73.35 };
	ft::list<double> mylist (mydoubles,mydoubles+10);

//	mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
	// 15.3,  72.25, 72.25, 73.0,  73.35

	mylist.unique();           //  2.72,  3.14, 12.15, 12.77
	// 15.3,  72.25, 73.0,  73.35

//	mylist.unique (same_integral_part);  //  2.72,  3.14, 12.15
	// 15.3,  72.25, 73.0

//	mylist.unique (is_near());           //  2.72, 12.15, 72.25

	std::cout << "mylist contains:";
	for (ft::list<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
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
// const ft::nodeit<int, node, const node*, const node&, tag>
// const ft::nodeit<int, node, node*, node&, tag>