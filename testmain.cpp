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

class testclass
{
private:
	char *str;
public:
	testclass()
	{
		this->str = (char*)malloc(5);
		std::cout << "constructor" << std::endl;
	}
	~testclass()
	{
		free(this->str);
	}
};

class Test
{
public:
	Test() : _x(0)
	{
		std::cout << "ik ben test" << std::endl;
		std::cout << this << std::endl;
	}
	Test(Test const &src) : _x(1)
	{
		std::cout << "ik ben test copy" << std::endl;
		std::cout << this << std::endl;
		*this = src;
	}
	~Test()
	{
		std::cout << "ik was test" << std::endl;
	}
	Test		&operator=(Test const &src)
	{
		std::cout << "Ik assign test" << std::endl;
		this->_x = src._x;
		return *this;
	}

	void		setX(int newX)
	{
		this->_x = newX;
	}
	int			getX()
	{
		return this->_x;
	}

private:
	int		_x;
};

using namespace ft;

void	complexclass()
{
	vector<Test> vc;

	vc.reserve(10);
	vc.push_back(Test());
	for (int i = 0; i < 10; i++)
		std::cout << vc[i].getX() << std::endl;
	std::allocator<Test>	alloc;
	Test					sample;
	int						amount;

	amount = 15;
	Test*	tests = alloc.allocate(amount);
	std::cout << "pointer " << tests << std::endl;
	alloc.construct(tests + 1, sample);
	tests[0].setX(18);
	tests[1].setX(19);

	for (int i = 0; i < amount; i++)
		std::cout << "Test " << i << ": " << tests[i].getX() << std::endl;
}

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
	while (it != vc0.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << "dist: " << vc0.end() - vc0.begin() << std::endl;
	std::cout << "begin > begin: ";
	if (vc0.begin() > vc0.begin())
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
	std::cout << "begin < begin: ";
	if (vc0.begin() < vc0.begin())
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
	std::cout << "begin >= begin: ";
	if (vc0.begin() >= vc0.begin())
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
	std::cout << "begin <= begin: ";
	if (vc0.begin() <= vc0.begin())
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
}

void	assign_test()
{
	vector<int> first;
	vector<int> second;
	vector<int> third;

	first.assign (7,100);			// 7 ints with a value of 100

	vector<int>::iterator it;
	it = first.begin()+1;

	second.assign (it,first.end()-1);	// the 5 central values of first

//	int myints[] = {1776,7,4};
//	third.assign (myints,myints+3);	// assigning from array.

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
//	std::cout << "Size of third: " << int (third.size()) << '\n';
}

int		main(int ac, char **av)
{
	complexclass();
//	capacity_size_test();
//	basic_it();
//	assign_test();
#ifndef ASAN
	std::string line = av[0];
	line = "leaks " + line.substr(line.rfind('/') + 1, line.back()) +
		   " | grep \"total leaked bytes\"";
	system(line.c_str());
#endif
	(void) ac;
	(void) av;
}
