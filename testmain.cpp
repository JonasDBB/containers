/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testmain.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 10:56:31 by jbennink      #+#    #+#                 */
/*   Updated: 2020/11/30 10:56:31 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "ft_vector.hpp"
#include "RandomAccessIterator.hpp"

using namespace ft;

void	capacity_size_test()
{
	vector<int> vc0;
	vector<int> vc1;
	vector<int> vc2;

	std::cout << "\n==CAPACITY AND RESIZE TESTS==\n" << std::endl;
	std::cout << "with push back\n" << vc0.capacity() << " " << vc0.size() << std::endl;
	for (int i = 0; i < 5000000; i++)
		vc0.push_back(i);
	std::cout << vc0.capacity() << " " << vc0.size() << std::endl;
	std::cout << "with resize\n" << vc1.capacity() << " " << vc1.size() << std::endl;
	vc1.resize(5000000);
	std::cout << vc1.capacity() << " " << vc1.size() << std::endl;
	std::cout << "with reserve\n" << vc2.capacity() << " " << vc2.size() << std::endl;
	vc2.reserve(5000000);
	std::cout << vc2.capacity() << " " << vc2.size() << std::endl;
}

void	basic_it()
{
	vector<int> vc0;

	for (int i = 0; i < 10; i++)
		vc0.push_back(i);
	vector<int>	vc1(vc0.begin(), vc0.end());
	vector<int>::iterator it = vc0.begin();
	for (int i = 0; i < 10; i++)
	{
		std::cout << "0: " << vc0[i] * 2 << " 1: " << vc1[i] * 2 << std::endl;
	}
//	while (it != vc0.end())
//	{
//		std::cout << *it << std::endl;
//		it++;
//	}
}

void	assign_test()
{
	vector<int> first;
	vector<int> second;
	vector<int> third;

	first.assign (7,100);             // 7 ints with a value of 100

	vector<int>::iterator it;
	it = first.begin()+1;

	second.assign (it,first.end()-1); // the 5 central values of first

	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);   // assigning from array.

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
	std::cout << "Size of third: " << int (third.size()) << '\n';
}

int		main()
{
//	capacity_size_test();
//	basic_it();
	assign_test();
}
