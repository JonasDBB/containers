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
		key_compare	_comp;
		size_type	_size;
		node		*_root;
		node_alloc	_alloc;
		node		_begin;
		node		_end;


	public:
		// default constructor
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_comp(comp),
				_size(0),
				_root(NULL),
				_alloc(alloc),
				_begin(),
				_end()
		{
			this->_begin._begin = &this->_begin;
			this->_end._begin = &this->_begin;
			this->_begin._end = &this->_end;
			this->_end._end = &this->_end;
		}

		// range constructor
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
			 typename iterator_traits<InputIterator>::iterator_category* = NULL) :
				_comp(comp),
				_size(0),
				_root(NULL),
				_alloc(alloc),
				_begin(),
				_end()
		{
			this->_begin._begin = &this->_begin;
			this->_end._begin = &this->_begin;
			this->_begin._end = &this->_end;
			this->_end._end = &this->_end;
			insert(first, last);
		}

		// copy constructor
		map(const map& x) :
				_comp(x._comp),
				_size(0),
				_root(NULL),
				_alloc(x._alloc),
				_begin(),
				_end()
		{
			this->_begin._begin = &this->_begin;
			this->_end._begin = &this->_begin;
			this->_begin._end = &this->_end;
			this->_end._end = &this->_end;
			insert(x.begin(), x.end());
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
			this->insert(x.begin(), x.end());
			return (*this);
		}

		/* ==ITERATOR FUNCTIONS== */
		iterator				begin()
		{
			if (!this->_root)
				return (this->end());
			node* nd = this->_root;
			while (nd->_left)
				nd = nd->_left;
			return (iterator(nd));
		}

		const_iterator			begin() const
		{
			node* nd = this->_root;
			while (nd->_left)
				nd = nd->_left;
			return (const_iterator(nd));
		}

		iterator				end()
		{
			return (iterator(&this->_end));
		}

		const_iterator			end() const
		{
			return (const_iterator(&this->_end));
		}

		reverse_iterator		rbegin()
		{
			return (reverse_iterator(this->end()));
		}

		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(this->end()));
		}

		reverse_iterator		rend()
		{
			return (reverse_iterator(this->begin()));
		}

		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(this->begin()));
		}

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
			iterator it = find(k);
			if (it != this->end())
				return (it->second);
			return (insert(make_pair(k, mapped_type())).first->second);
		}

		/* ==MODIFIER FUNCTIONS== */
		pair<iterator, bool>	insert(const value_type& val)
		{
			size_type oldsize = this->_size;
			this->_root = insertNode(this->_root, val, NULL);
			this->updateEnds();
//			myprnt(this->_root);
			if (this->_size == oldsize)
				return (make_pair(find(val.first), false));
			return (make_pair(find(val.first), true));
		}

		iterator	insert(iterator position, const value_type& val)
		{
			(void)position;
			return (insert(val).first);
		}

		template <class InputIterator>
		void		insert(InputIterator first, InputIterator last,
						   typename iterator_traits<InputIterator>::iterator_category* = NULL)
		{
			while (first != last)
				insert(*(first++));
		}

		void		erase(iterator position)
		{
			this->_root = deleteNode(this->_root, position->first);
			this->updateEnds();
//			myprnt(this->_root);
		}

		size_type	erase(const key_type& k)
		{
			size_type oldsize = this->_size;
			this->_root = deleteNode(this->_root, k);
			this->updateEnds();
//			myprnt(this->_root);
			return (oldsize - this->_size);
		}

		void		erase(iterator first, iterator last)
		{
			while (first != last)
				this->erase(first++);
		}

		void		swap(map& x)
		{
			ft::swap(this->_size, x._size);
			ft::swap(this->_root, x._root);
			ft::swap(this->_alloc, x._alloc);
			ft::swap(this->_begin, x._begin);
			ft::swap(this->_end, x._end);
		}

		void		clear()
		{
			while (!this->empty())
				erase(this->_root->first);
//			myprnt(this->_root);
		}

		/* ==OBSERVER FUNCTIONS== */
		key_compare		key_comp() const
		{
			return (this->_comp);
		}

		value_compare	value_comp() const
		{
			return value_compare(this->_comp);
		}

		allocator_type	get_allocator() const
		{
			return (this->_alloc);
		}

		/* ==OPERATION FUNCTIONS== */
		iterator		find(const key_type& k)
		{
			if (!this->_root)
				return (this->end());
			node* nd = this->_root;
			while (nd->first != k)
			{
				if (nd->first > k)
				{
					if (nd->_left)
						nd = nd->_left;
					else
						break;
				}
				else if (nd->first < k)
				{
					if (nd->_right)
						nd = nd->_right;
					else
						break;
				}
			}
			if (nd->first != k)
				return (this->end());
			return (iterator(nd));
		}

		const_iterator	find(const key_type& k) const
		{
//			if (!this->_root)
//				return (this->end());
//			node* nd = this->_root;
//			while (nd->first != k)
//			{
//				if (nd->first > k)
//				{
//					if (nd->_left)
//						nd = nd->_left;
//					else
//						break;
//				}
//				else if (nd->first < k)
//				{
//					if (nd->_right)
//						nd = nd->_right;
//					else
//						break;
//				}
//			}
//			if (nd->first != k)
//				return (this->end());
			return (const_iterator(*(find(k))));
		}

		size_type		count(const key_type& k) const
		{
			if (this->find(k) == this->end())
				return (0);
			return (1);
		}

		iterator		lower_bound(const key_type& k)
		{
			iterator it = this->begin();
			for (; it != this->end(); ++it)
			{
				if (!it->first < k)
					break;
			}
			return (it);
		}

		const_iterator	lower_bound(const key_type& k) const
		{
			const_iterator it = this->begin();
			for (; it != this->end(); ++it)
			{
				if (!it->first < k)
					break;
			}
			return (it);
		}

		iterator		upper_bound(const key_type& k)
		{
			iterator it = this->begin();
			for (; it != this->end(); ++it)
			{
				if (it->first > k)
					break;
			}
			return (it);
		}

		const_iterator	upper_bound(const key_type& k) const
		{
			const_iterator it = this->begin();
			for (; it != this->end(); ++it)
			{
				if (it->first > k)
					break;
			}
			return (it);
		}

		pair<const_iterator, const_iterator>	equal_range(const key_type& k) const
		{
			return (make_pair(lower_bound(k), upper_bound(k)));
		}

		pair<iterator, iterator>				equal_range(const key_type& k)
		{
			return (make_pair(lower_bound(k), upper_bound(k)));
		}

	private:
		void	myprnt(node* root)
		{
			if (this->_root && this->_root->_parent)
				std::cout << "WADAFAK" << std::endl;
			if (this->_root)
				std::cout << "\t\t\t  " << *root << std::endl;
			else
			{
				std::cout << "\t\t\t  " << "EMPTY" << std::endl;
				return;
			}
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
			std::cout << std::endl;
		}


		node*	insertNode(node *current, ft::pair<Key, T> val, node* parent)
		{
			if (!current)
			{
				++this->_size;
				node *nd = this->_alloc.allocate(1);
				this->_alloc.construct(nd, val);
				nd->_begin = &this->_begin;
				nd->_end = &this->_end;
//				node* nd = new node(val, &this->_begin, &this->_end);
				nd->_parent = parent;
				return (nd);
			}
			Key k = val.first;
			if (k < current->first)
			{
				current->_left = insertNode(current->_left, val, current);
//				current->_left->_parent = current;
			}
			else if (k > current->first)
			{
				current->_right = insertNode(current->_right, val, current);
//				current->_right->_parent = current;
			}
			else
				return (current);

			current->updateHeight();

			if (current->getBalance() > 1 && k < current->_left->first)
			{
				current->rightRotate();
				return (current->_parent);
			}
			if (current->getBalance() < -1 && k > current->_right->first)
			{
				current->leftRotate();
				return (current->_parent);
			}
			if (current->getBalance() > 1 && k > current->_left->first)
			{
				current->_left->leftRotate();
				current->rightRotate();
				return (current->_parent);
			}
			if (current->getBalance() < -1 && k < current->_right->first)
			{
				current->_right->rightRotate();
				current->leftRotate();
				return (current->_parent);
			}
			return (current);
		}

		node*	deleteNode(node* root, const Key& k)
		{
			if (!root)
				return (root);
			if (k < root->first)
				root->_left = deleteNode(root->_left, k);
			else if (k > root->first)
				root->_right = deleteNode(root->_right, k);
			else
			{
				if (!root->_left && !root->_right)
				{
					node *tmp = root;
					root = NULL;
					--this->_size;
					this->_alloc.destroy(tmp);
					this->_alloc.deallocate(tmp, 1);
//					delete tmp;
				}
				else if (!root->_left || !root->_right)
				{
					node *tmp = root->_left ? root->_left : root->_right;
					tmp->_parent = root->_parent;
					node *tmp2 = root;
					root = tmp;
					--this->_size;
					this->_alloc.destroy(tmp2);
					this->_alloc.deallocate(tmp2, 1);
//					delete tmp2;
				}
				else
				{
					node *tmp = root->_left;
					while (tmp->_right)
						tmp = tmp->_right;
					root->_val = tmp->_val;
					root->_left = deleteNode(root->_left, tmp->first);
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

		void	updateEnds()
		{
			this->_begin._parent = this->_root;
			this->_end._parent = this->_root;
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
