#ifndef FT_MAP_HPP
# define FT_MAP_HPP
# include "../iterators/NodeIterator.hpp"
# include "../iterators/ReverseIterator.hpp"
# include "../utils/type_traits.hpp"
# include "../utils/Utils.hpp"
# include "../utils/ft_pair.hpp"
# include "../utils/MapNode.hpp"
# include <memory>

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<T> >
	class map
	{
	public:
		typedef	Key															key_type;
		typedef	T															mapped_type;
		typedef	pair<const key_type, mapped_type>							value_type;
		typedef	Compare														key_compare;
		typedef	Alloc														allocator_type;
		typedef	value_type&													reference;
		typedef	const value_type&											const_reference;
		typedef	value_type*													pointer;
		typedef	const value_type*											const_pointer;
		typedef MapNode<key_type, mapped_type>								node;
		typedef NodeIterator<value_type, node, node*, node&>				iterator;
		typedef NodeIterator<value_type, node, const node*, const node&>	const_iterator;
		typedef ReverseIterator<iterator>									reverse_iterator;
		typedef ReverseIterator<const_iterator>								const_reverse_iterator;
		typedef ptrdiff_t													difference_type;
		typedef size_t														size_type;
		typedef typename Alloc::template rebind<node>::other				node_alloc;

		class value_compare : public binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			key_compare	comp;
			value_compare(key_compare c) : comp(c) {}
		public:
			bool operator()(const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

	private:
		size_type	_size;
		node		*_root;
		node_alloc	_alloc;


	public:
		// default constructor
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_size(0),
				_root(NULL),
				_alloc(alloc)
		{
			(void)comp;
		}

		// range constructor
/*		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_size(0),
				_root(NULL),
				_alloc(alloc)
		{
			// insert maybe?
		}

		// copy constructor
		map(const map& x) :
				_size(0),
				_root(NULL),
				_alloc(x._alloc)
		{
			// prob also insert
		}

		// destructor
		~map()
		{
			this->clear();
		}

		// assignment operator
		map&	operator=(const map& x)
		{
			this->clear();
			this->_alloc = x._alloc;
			// prob another insert
			return (*this);
		}
*/
		/* ==ITERATOR FUNCTIONS== */
/*		iterator				begin()
		{
			// find lowest val
		}

		const_iterator			begin() const
		{

		}

		iterator				end()
		{

		}

		const_iterator			end() const
		{

		}

		reverse_iterator		rbegin()
		{

		}

		const_reverse_iterator	rbegin() const
		{

		}

		reverse_iterator		rend()
		{

		}

		const_reverse_iterator	rend() const
		{

		}
*/
		/* ==CAPACITY FUNCTIONS== */
		bool		empty() const
		{
			return (this->_size == 0);
		}

		size_type	size() const
		{
			return (this->_size);
		}

		size_type	max_size() const
		{
			return (this->_alloc.max_size());
		}

		/* ==ELEMENT ACCESS FUNCTIONS== */
		mapped_type&	operator[](const key_type& k)
		{
			value_type *ins = new value_type(k,mapped_type());
//			value_type *ins = new ft::pair<key_type,mapped_type>(k, mapped_type());
//			MapNode<Key, T> *nwnd = new node(ins);
//			this->_root = insertNode(this->_root, *nwnd);
//			return(nwnd->_val.second);
			insert(*ins);
			return ins->second;
		}

		/* ==MODIFIER FUNCTIONS== */
		bool	insert(const value_type& val)
		{
			size_type oldsize = this->_size;
			this->_root = insertNode(this->_root, val);
			myprnt(this->_root);
			if (this->_size == oldsize)
				return (false);
			return (true);
		}

/*		iterator	insert(iterator position, const value_type& val)
		{

		}

		template <class InputIterator>
		void		insert(InputIterator first, InputIterator last,
							typename iterator_traits<InputIterator>::type* = NULL)
		{

		}

		void		erase(iterator position)
		{

		}

		size_type	erase(const key_type& k)
		{

		}
*/
/*		void		erase(iterator first, iterator last)
		{
			while (first != last)
				this->erase(first++);
			return (last);
		}

		void		swap(map& x)
		{

		}

		void		clear()
		{

		}
*/
		/* ==OBSERVER FUNCTIONS== */
		key_compare		key_comp() const
		{

		}

		value_compare	value_comp() const
		{

		}

		allocator_type	get_allocator() const
		{
			return (this->_alloc);
		}

		/* ==OPERATION FUNCTIONS== */
//		iterator		find(const key_type& k)
//		{
//			node* ret = this->_root;
//			while (ret->key())
//
//			return (ret);
//		}
/*
		const_iterator	find(const key_type& k) const
		{

		}
*/
		size_type		count(const key_type& k) const
		{
			if (this->find(k) == this->end())
				return (0);
			return (1);
		}

/*		iterator		lower_bound(const key_type& k)
		{

		}

		const_iterator	lower_bound(const key_type& k) const
		{

		}

		iterator		upper_bound(const key_type& k)
		{

		}

		const_iterator	upper_bound(const key_type& k) const
		{

		}

		pair<const_iterator, const_iterator>	equal_range(const key_type& k) const
		{

		}

		pair<iterator, iterator>				equal_range(const key_type& k)
		{

		}
*/
	private:
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


		node*	insertNode(node *root, ft::pair<Key, T> val)
		{
			if (!root)
			{
				++this->_size;
				return (new node(val));
			}
			Key k = val.first;
			if (k < root->key())
			{
				root->_left = insertNode(root->_left, val);
			}
			else if (k > root->key())
			{
				root->_right = insertNode(root->_right, val);
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

		node*	deleteNode(node* root, const Key& k)
		{
			if (!root)
				return (root);
			if (k < root->key())
				root->_left = deleteNode(root->_left, k);
			else if (k > root->key())
				root->_right = deleteNode(root->_right, k);
			else
			{
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
					root->_left = deleteNode(root->_left, tmp->key());
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
	};

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::map<Key, T, Compare, Alloc>::iterator it0 = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::iterator it1 = rhs.begin();
		for (; it0 != lhs.end() && it1 != rhs.end(); ++it0, ++it1)
		{
			if (*it0 != *it1)
				return (false);
		}
		return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
