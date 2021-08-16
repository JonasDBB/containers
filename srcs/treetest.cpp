#include <iostream>
#include <map>
#include "utils/MapNode.hpp"
ft::MapNode<int, double> *g_root = NULL;
#define node ft::MapNode<Key, T>

template <class Key, class T>
void	myprnt(node* root)
{
	std::cout << "\t\t\t  " << *root << std::endl;
	if (root->_left)
		std::cout << "\t" << *root->_left << "\t\t||\t";
	else
		std::cout << "\t\tLEAF\t||\t";
	if (root->_right)
		std::cout << "   " << *root->_right;
	else
		std::cout << "\tLEAF";
	std::cout << std::endl;
	if (root->_left)
	{
		if (root->_left->_left)
		{
			std::cout << *root->_left->_left << "||";
			if (root->_left->_left->_left || root->_left->_left->_right)
				std::cout << "WADDAFAK" << std::endl;
		}
		else
			std::cout << "LEAF  ||  ";
		if (root->_left->_right)
		{
			std::cout << *root->_left->_right << "  ";
			if (root->_left->_right->_left || root->_left->_right->_right)
				std::cout << "WADDAFAK" << std::endl;
		}
		else
			std::cout << "LEAF\t  ";
	}
	else
		std::cout << "\t\t\t\t  ";
	if (root->_right)
	{
		if (root->_right->_left)
		{
			std::cout << *root->_right->_left << "||";
			if (root->_right->_left->_left || root->_right->_left->_right)
				std::cout << "WADDAFAK" << std::endl;
		}
		else
			std::cout << "  LEAF  ||  ";
		if (root->_right->_right)
		{
			std::cout << *root->_right->_right << "  ";
			if (root->_right->_right->_left || root->_right->_right->_right)
				std::cout << "WADDAFAK" << std::endl;
		}
		else
			std::cout << "LEAF";
	}
	std::cout << std::endl;
}

template <class Key, class T>
node*	insrt(node *root, ft::pair<Key, T> val)
{
	if (!root)
		return (new node(val));
	Key k = val.first;
	if (k < root->first)
	{
		root->_left = insrt(root->_left, val);
	}
	else if (k > root->first)
	{
		root->_right = insrt(root->_right, val);
	}
	else
		return (root);

	root->updateHeight();

	if (root->getBalance() > 1 && k < root->_left->first)
	{
		root->rightRotate();
		return (root->_parent);
	}
	if (root->getBalance() < -1 && k > root->_right->first)
	{
		root->leftRotate();
		return (root->_parent);
	}
	if (root->getBalance() > 1 && k > root->_left->first)
	{
		root->_left->leftRotate();
		root->rightRotate();
		return (root->_parent);
	}
	if (root->getBalance() < -1 && k < root->_right->first)
	{
		root->_right->rightRotate();
		root->leftRotate();
		return (root->_parent);
	}
	return (root);
}

template <class Key, class T>
node*	del(node* root, const Key& k)
{
	if (!root)
		return (root);
	if (k < root->first)
		root->_left = del(root->_left, k);
	else if (k > root->first)
		root->_right = del(root->_right, k);
	else
	{
		// actually delete node
		if (!root->_left && !root->_right)
		{
			node *tmp = root;
			root = NULL;
			delete tmp;
		}
		else if (!root->_left || !root->_right)
		{
			node *tmp = root->_left ? root->_left : root->_right;
			*root = *tmp;
			delete tmp;
		}
		else
		{
			node *tmp = root->_left;
			while (tmp->_right)
				tmp = tmp->_right;
			root->_val = tmp->_val;
			root->_left = del(root->_left, tmp->first);
		}
	}
	if (!root)
		return (root);
	root->updateHeight();
	if (root->getBalance() > 1 && root->_left->getBalance() >= 0)
	{
		root->rightRotate();
		return (root->_parent);
	}
	if (root->getBalance() < -1 && root->_right->getBalance() <= 0)
	{
		root->leftRotate();
		return (root->_parent);
	}
	if (root->getBalance() > 1 && root->_left->getBalance() < 0)
	{
		root->_left->leftRotate();
		root->rightRotate();
		return (root->_parent);
	}
	if (root->getBalance() < -1 && root->_right->getBalance() > 0)
	{
		root->_right->rightRotate();
		root->leftRotate();
		return (root->_parent);
	}
	return (root);
}

#include <map>
void	mappies()
{
//	ft::MapNode<int, int> *root = NULL;
	for (int i = 5; i >= 1; --i)
	{
		ft::pair<int, double> pr(i, -i);
		g_root = insrt(g_root, pr);
//		myprnt(g_root);
//		std::cout << std::endl;
	}
//	myprnt(g_root);
	ft::pair<int, double> mypr;
//	mypr = (*g_root);
//	std::cout << mypr.first << std::endl;
	std::cout << g_root->first << g_root->second << std::endl;
	if (g_root->first == 4)
	{
		g_root->second = 5;
//		g_root->_val.second = 3;
	}
	std::cout << g_root->first << g_root->second << std::endl;
	std::cout << g_root->_val.first << g_root->_val.second << std::endl;
//	std::map<int, int> mp;
//	for (int i = 0; i < 5; ++i)
//		mp[i] = i;
//	std::map<int, int>::iterator it = mp.begin();
//	std::cout << it->first;
//	std::pair<const int, int> &ref(*it);
//	deleteNode(g_root, 5);
	g_root = del(g_root, 5);
	myprnt(g_root);
}

int		main(int ac, char **av)
{
	mappies();

#ifndef ASAN
	std::string line = av[0];
	line = "leaks " + line.substr(line.rfind('/') + 1, line.back()) +
		   " | grep \"total leaked bytes\"";
	system(line.c_str());
#endif
	(void) ac;
	(void) av;
}

