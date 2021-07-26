#include <iostream>
#include <map>
#include "utils/MapNode.hpp"
ft::MapNode<int, int> *g_root = NULL;
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
/*   p      p
 *   |      |
 *   nd     l
 *  / \ ->   \
 * l   r      nd
 *           /
 *          r
 *
 */

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

//template <class Key, class T>
//void	rightRotate(node *nd)
//{
//	node *leftChild = nd->_left;
//	node *leftRightChild = nd->_left->_right;
//
//	leftChild->_right = nd;
//	nd->_left = leftRightChild;
//	if (leftRightChild)
//		leftRightChild->_parent = nd;
//	leftChild->_parent = nd->_parent;
//	nd->_parent = leftChild;
//	if (leftChild->_parent)
//	{
//		if (nd == leftChild->_parent->_left)
//			leftChild->_parent->_left = leftChild;
//		else
//			leftChild->_parent->_right = leftChild;
//	}
//
//	nd->updateHeight();
//	leftChild->updateHeight();
//}

//template <class Key, class T>
//void	leftRotate(node *nd)
//{
//	node *rightChild = nd->_right;
//	node *rightLeftChild = nd->_right->_left;
//
//	rightChild->_left = nd;
//	nd->_right = rightLeftChild;
//	if (rightLeftChild)
//		rightLeftChild->_parent = nd;
//	rightChild->_parent = nd->_parent;
//	nd->_parent = rightChild;
//	if (rightChild->_parent)
//	{
//		if (nd == rightChild->_parent->_right)
//			rightChild->_parent->_right = rightChild;
//		else
//			rightChild->_parent->_left = rightChild;
//	}
//
//	nd->updateHeight();
//	rightChild->updateHeight();
//}

template <class Key, class T>
node*	insrt(node *root, ft::pair<Key, T> val)
{
	if (!root)
		return (new node(val));
	Key k = val.first;
	if (k < root->key())
	{
		root->_left = insrt(root->_left, val);
	}
	else if (k > root->key())
	{
		root->_right = insrt(root->_right, val);
	}
	else
		return (root);

	root->updateHeight();

	if (root->getBalance() > 1 && k < root->_left->key())
	{
		root->rightRotate();
		return (root->_parent);
	}
	if (root->getBalance() < -1 && k > root->_right->key())
	{
		root->leftRotate();
		return (root->_parent);
	}
	if (root->getBalance() > 1 && k > root->_left->key())
	{
		root->_left->leftRotate();
		root->rightRotate();
		return (root->_parent);
	}
	if (root->getBalance() < -1 && k < root->_right->key())
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
	if (k < root->key())
		root->_left = del(root->_left, k);
	else if (k > root->key())
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
			root->_left = del(root->_left, tmp->key());
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


void	mappies()
{
//	ft::MapNode<int, int> *root = NULL;
	for (int i = 5; i >= 1; --i)
	{
		ft::pair<int, int> pr(i, -i);
		g_root = insrt(g_root, pr);
//		myprnt(g_root);
//		std::cout << std::endl;
	}
//	myprnt(g_root);
	ft::pair<int, int> mypr;
	mypr = (*g_root);
	std::cout << mypr.first << std::endl;
//	deleteNode(g_root, 5);
	g_root = del(g_root, 5);
//	myprnt(g_root);
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

