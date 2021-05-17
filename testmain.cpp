#include <iostream>
#include <vector>
#include "ft_vector.hpp"
#include "RandomAccessIterator.hpp"
#include "ReverseIterator.hpp"

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

void	vecConstr()
{
	// constructors used in the same order as described above:
	vector<int> first;                                // empty vector of ints
	vector<int> second (4,100);                       // four ints with value 100
	vector<int> third (second.begin(),second.end());  // iterating through second
	vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	vecAssignOp()
{
	vector<int> foo (3,0);
	vector<int> bar (5,0);

	bar = foo;
	foo = vector<int>();

	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';
}

void	vecBeginEnd()
{
	vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	std::cout << "myvector contains:";
	for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	vecRbeginRend()
{
	vector<int> myvector (5);  // 5 default-constructed ints

	int i=0;

	vector<int>::reverse_iterator rit = myvector.rbegin();
	for (; rit!= myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	vecSize()
{
	vector<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<10; i++) myints.push_back(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.insert (myints.end(),10,100);
	std::cout << "2. size: " << myints.size() << '\n';

	myints.pop_back();
	std::cout << "3. size: " << myints.size() << '\n';
}

void	vecMaxsize()
{
	vector<int> myvector;

	// set some content in the vector:
	for (int i=0; i<100; i++) myvector.push_back(i);

	std::cout << "size: " << myvector.size() << "\n";
	std::cout << "capacity: " << myvector.capacity() << "\n";
	std::cout << "max_size: " << myvector.max_size() << "\n";
}

void	vecResize()
{
	vector<int> myvector;

	// set some initial content:
	for (int i = 1; i < 10; i++)
		myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	for (unsigned int i=0;i<myvector.size();i++)
	{
		std::cout << ' ' << myvector[i];
		std::cout.flush();
	}
	std::cout << '\n';
}

void	vecReserv()
{
	vector<int>::size_type sz;

	vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i=0; i<100; ++i) {
		bar.push_back(i);
		if (sz!=bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
}

void	vecBrckOp()
{
	vector<int> myvector (10);   // 10 zero-initialized elements

	vector<int>::size_type sz = myvector.size();

	// assign some values:
	for (unsigned i=0; i<sz; i++) myvector[i]=i;

	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
		int temp;
		temp = myvector[sz-1-i];
		myvector[sz-1-i]=myvector[i];
		myvector[i]=temp;
	}

	std::cout << "myvector contains:";
	for (unsigned i=0; i<sz; i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void	vecAt()
{
	vector<int> myvector (10);   // 10 zero-initialized ints

	// assign some values:
	for (unsigned i=0; i<myvector.size(); i++)
		myvector.at(i)=i;

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector.at(i);
	std::cout << '\n';
}
void	vecFront()
{
	vector<int> myvector;

	myvector.push_back(78);
	myvector.push_back(16);

	// now front equals 78, and back 16

	myvector.front() -= myvector.back();

	std::cout << "myvector.front() is now " << myvector.front() << '\n';
}

void	vecBack()
{
	vector<int> myvector;

	myvector.push_back(10);

	while (myvector.back() != 0)
	{
		myvector.push_back ( myvector.back() -1 );
	}

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size() ; i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void	vecAssign()
{
	vector<int> first;
	vector<int> second;
	vector<int> third;

	first.assign (7,100);             // 7 ints with a value of 100

	vector<int>::iterator it;
	it=first.begin()+1;

	second.assign (it,first.end()-1); // the 5 central values of first

	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);   // assigning from array.

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
	std::cout << "Size of third: " << int (third.size()) << '\n';
}

//void	vecErase()
//{
//	vector<int> myvector;
//
//	// set some values (from 1 to 10)
//	for (int i=1; i<=10; i++) myvector.push_back(i);
//
//	// erase the 6th element
//	myvector.erase (myvector.begin()+5);
//
//	// erase the first 3 elements:
//	myvector.erase (myvector.begin(),myvector.begin()+3);
//
//	std::cout << "myvector contains:";
//	for (unsigned i=0; i<myvector.size(); ++i)
//		std::cout << ' ' << myvector[i];
//	std::cout << '\n';
//}

void	vecPushb()
{
	vector<int> myvector;
	int myint;

	std::cout << "Please enter some integers (enter 0 to end):\n";

	do {
		std::cin >> myint;
		myvector.push_back (myint);
	} while (myint);

	std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
}

void	vecPopb()
{
	vector<int> myvector;
	int sum (0);
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	while (!myvector.empty())
	{
		sum+=myvector.back();
		myvector.pop_back();
	}

	std::cout << "The elements of myvector add up to " << sum << '\n';
}

//void	vecInsert()
//{
//	vector<int> myvector (3,100);
//	vector<int>::iterator it;
//
//	it = myvector.begin();
//	it = myvector.insert ( it , 200 );
//
//	myvector.insert (it,2,300);
//
//	// "it" no longer valid, get a new one:
//	it = myvector.begin();
//
//	vector<int> anothervector (2,400);
//	myvector.insert (it+2,anothervector.begin(),anothervector.end());
//
//	int myarray [] = { 501,502,503 };
//	myvector.insert (myvector.begin(), myarray, myarray+3);
//
//	std::cout << "myvector contains:";
//	for (it=myvector.begin(); it<myvector.end(); it++)
//		std::cout << ' ' << *it;
//	std::cout << '\n';
//}

void	vecSwap()
{
	vector<int> foo (3,100);   // three ints with a value of 100
	vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';
}

void	vecClear()
{
	vector<int> myvector;
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	myvector.clear();
	myvector.push_back (1101);
	myvector.push_back (2202);

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void	vecRelOps()
{
	vector<int> foo (3,100);   // three ints with a value of 100
	vector<int> bar (2,200);   // two ints with a value of 200

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

void	vectests()
{
//	vecConstr();
//	The contents of fifth are: 16 2 77 29
//	vecAssignOp();
//	Size of foo: 0
//	Size of bar: 3
//	vecBeginEnd();
//	myvector contains: 1 2 3 4 5
//	vecRbeginRend();
//	myvector contains: 5 4 3 2 1
//	vecSize();
//	0. size: 0
//	1. size: 10
//	2. size: 20
//	3. size: 19
//	vecMaxsize();
//	size: 100
//	capacity: 128
//	max_size: 4611686018427387903
//	vecResize();
//	myvector contains: 1 2 3 4 5 100 100 100 0 0 0 0
//	vecReserv();
//	making foo grow:
//	capacity changed: 1
//	capacity changed: 2
//	capacity changed: 4
//	capacity changed: 8
//	capacity changed: 16
//	capacity changed: 32
//	capacity changed: 64
//	capacity changed: 128
//	making bar grow:
//	capacity changed: 100
//	vecBrckOp();
//	myvector contains: 9 8 7 6 5 4 3 2 1 0
//	vecAt();
//	myvector contains: 0 1 2 3 4 5 6 7 8 9
//	vecFront();
//	myvector.front() is now 62
//	vecBack();
//	myvector contains: 10 9 8 7 6 5 4 3 2 1 0
//	vecAssign();
//	Size of first: 7
//	Size of second: 5
//	Size of third: 3
//	vecPushb();
//	myvector stores n numbers. // where n is the amount of numbers entered
//	vecPopb();
//	The elements of myvector add up to 600
	// ===========================================================vecInsert();
//	myvector contains: 501 502 503 300 300 400 400 200 100 100 100
//	==============================================================vecErase();
//	myvector contains: 4 5 7 8 9 10
//	vecSwap();
//	foo contains: 200 200 200 200 200
//	bar contains: 100 100 100
//	vecClear();
//	myvector contains: 100 200 300
//	myvector contains: 1101 2202
	vecRelOps();
//	foo and bar are not equal
//	foo is less than bar
//	foo is less than or equal to bar
}

int		main(int ac, char **av)
{
	vectests();
#ifndef ASAN
	std::string line = av[0];
	line = "leaks " + line.substr(line.rfind('/') + 1, line.back()) +
		   " | grep \"total leaked bytes\"";
	system(line.c_str());
#endif
	(void) ac;
	(void) av;
}
