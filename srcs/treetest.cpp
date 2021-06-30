#include <iostream>
#include <map>
#include "utils/MapNode.hpp"

#define node ft::MapNode<Key, T>
template <class Key, class T>
void	_printNode(std::string root_path, node *root)
{
	node	*tmp = root;
	std::cout << ".";
	for (int i = 0; root_path[i]; ++i)
	{
		if (root_path[i] == 'L')
		{
			if (tmp->_left == NULL)
				return ;
			tmp = tmp->_left;
		}
		if (root_path[i] == 'R')
		{
			if (tmp->_right == NULL)
				return ;
			tmp = tmp->_right;
		}
	}
}

template <class Key, class T>
void	print(node *root)
{
	if (root == 0)
	{
		std::cout << "Tree is empty" << std::endl;
		return ;
	}
	std::string		root_path;
	int				layer = 0;
	root_path = "";
	int				starting_tabs = 32;
	int				starting_gap = 32;
	while (layer < 6)
	{
		root_path.clear();
		int		tmp_tabs = starting_tabs;
		int		tmp_gap = starting_gap;
		for (int tmp_layer = layer; tmp_layer; --tmp_layer)
		{
			root_path.append("L");
			tmp_gap = tmp_gap / 2;
			tmp_tabs -= tmp_gap;
		}
		while (root_path.find('L') != std::string::npos)
		{
			if (root_path.find('R') == std::string::npos)
				for (; tmp_tabs; --tmp_tabs)
					std::cout << "  ";
			else
				for (int tmp_gap2 = tmp_gap * 2; tmp_gap2; --tmp_gap2)
					std::cout << "  ";
			_printNode(root_path, root);
			size_t	L_found = root_path.find_last_of('L');
			root_path[L_found] = 'R';
			++L_found;
			for (; L_found != root_path.size(); ++L_found)
			{
				root_path[L_found] = 'L';
			}
		}
		if (root_path.find('R') == std::string::npos)
			for (; tmp_tabs; --tmp_tabs)
				std::cout << "  ";
		else
			for (int tmp_gap2 = tmp_gap * 2; tmp_gap2; --tmp_gap2)
				std::cout << "  ";
		_printNode(root_path, root);
		std::cout << std::endl << std::endl << std::endl;
		layer++;
	}
}

template <class Key, class T>
node*	rrot(node *nd)
{
	node *l = nd->_left;
	node *r = nd->_right;

	l->_right = nd;
	nd->_left = r;

	nd->updateHeight();
	l->updateHeight();
	return (l);
}

template <class Key, class T>
node*	lrot(node *nd)
{
	node *l = nd->_left;
	node *r = nd->_right;

	r->_left = nd;
	nd->_right = l;

	nd->updateHeight();
	r->updateHeight();
	return (r);
}

template <class Key, class T>
node*	insrt(node *root, ft::pair<Key, T> val)
{
	if (!root)
		return (new node(val));
	Key k = val.first;
	if (k < root->key())
		root->_left = insrt(root->_left, val);
	else if (k > root->key())
		root->_right = insrt(root->_right, val);
	else
		return (root);

	root->updateHeight();

	if (root->balance() > 1 && k < root->_left->key())
		return (rrot(root));
	if (root->balance() < -1 && k > root->_right->key())
		return (lrot(root));
	if (root->balance() > 1 && k > root->_left->key())
	{
		root->_left = lrot(root->_left);
		return (rrot(root));
	}
	if (root->balance() < -1 && k < root->_right->key())
	{
		root->_right = rrot(root->_right);
		return (rrot(root));
	}
	return (root);
}


void	mappies()
{
	ft::MapNode<int, int> *root = NULL;
//	for (int i = 0; i < 5; ++i)
//	{
//		ft::pair<int, int> pr(i, -i);
//		root = insrt(root, pr);
//	}
	root = insrt(root, ft::pair<int, int>(1,-1));
	root = insrt(root, ft::pair<int, int>(2,-2));
	root = insrt(root, ft::pair<int, int>(3,-3));
//	std::cout << *root << std::endl;
//	std::cout << *root->_right << std::endl;
//	std::cout << *root->_left << std::endl;
	print(root);
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

