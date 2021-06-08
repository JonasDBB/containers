#ifndef FT_LIST_HPP
# define FT_LIST_HPP
# include "../iterators/NodeIterator.hpp"
# include "../iterators/ReverseIterator.hpp"
# include "../utils/type_traits.hpp"
# include "../utils/Utils.hpp"
# include "../utils/ListNode.hpp"
# include <cstddef>
# include <memory>
# include <iostream>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class list
	{
	public:
		typedef	T														value_type;
		typedef	Alloc													allocator_type;
		typedef value_type&												reference;
		typedef const value_type&										const_reference;
		typedef value_type*												pointer;
		typedef const value_type*										const_pointer;
		typedef	ListNode<T>												node;
		typedef NodeIterator<T, node, node*, node&>						iterator;
		typedef NodeIterator<T, node, const node*, const node&>			const_iterator;
		typedef ReverseIterator<iterator>								reverse_iterator;
		typedef ReverseIterator<const_iterator>							const_reverse_iterator;
		typedef ptrdiff_t												difference_type;
		typedef size_t													size_type;
		typedef typename Alloc::template rebind<ListNode<T> >::other	node_alloc;

	private:
		size_type	_size;
		node		_sentinel;
		node_alloc	_alloc;

	public:
		void	printlist()
		{
			node *crnt = this->_sentinel._next;
			std::cout << "begin list:";
			if (this->_size)
				std::cout << "\t[";
			for (size_type i = 0; i < this->_size; i++)
			{
//				std::cout << crnt->_val << " - " << crnt << "]";
				std::cout << crnt->_val << "]";
				crnt = crnt->_next;
				if (i < this->_size - 1)
					std::cout << " [";
			}
			std::cout << "\t  endlist" << std::endl;
		}

		void	printlistbackwards()
		{
			node *crnt = this->_sentinel._previous;
			std::cout << "end list:";
			if (this->_size)
				std::cout << "\t[";
			for (size_type i = 0; i < this->_size; i++)
			{
				std::cout << crnt->_val << "]";
				crnt = crnt->_previous;
				if (i < this->_size - 1)
					std::cout << " [";
			}
			std::cout << "\t  beginlist" << std::endl;
		}
		// default constructor
		explicit list(const allocator_type& alloc = allocator_type()) :
				_size(0),
				_sentinel(0),
				_alloc(alloc)
		{
			this->_sentinel._next = &this->_sentinel;
			this->_sentinel._previous = &this->_sentinel;
		}

		// fill constrcutor
		explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
				_size(0),
				_sentinel(0),
				_alloc(alloc)
		{
			this->assign(n, val);
			this->_sentinel._next = &this->_sentinel;
			this->_sentinel._previous = &this->_sentinel;
		}

		// range constructor
		template <class InputIterator>
		list(InputIterator first, InputIterator last,
			 const allocator_type& alloc = allocator_type(),
			 typename iterator_traits<InputIterator>::type* = NULL) :
			 _size(0),
			 _sentinel(0),
			 _alloc(alloc)
		{
			this->_sentinel._next = &this->_sentinel;
			this->_sentinel._previous = &this->_sentinel;
			this->assign(first, last);
		}

		// copy constructor
		list(const list& x) :
				_size(0),
				_sentinel(0),
				_alloc(x._alloc)
		{
			this->_sentinel._next = &this->_sentinel;
			this->_sentinel._previous = &this->_sentinel;
			this->assign(x.begin(), x.end());
		}

		// destructor
		~list()
		{
			while (this->_size)
				pop_back();
		}

		// assignment operator
		list&	operator=(const list& x)
		{
			this->clear();
			this->_alloc = x._alloc;
			this->assign(x.begin(), x.end());
		}

		/* ==ITERATOR FUNCTIONS== */
		iterator				begin()
		{
			return(this->_sentinel._next);
		}

		const_iterator			begin() const
		{
			return (const_iterator(this->_sentinel._next));
		}

		iterator				end()
		{
			return (iterator(&this->_sentinel));
		}

		const_iterator			end() const
		{
			return (const_iterator(&this->_sentinel));
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
			return (reverse_iterator(this->begin()));
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
		reference		front()
		{
			return (this->_sentinel._next->_val);
		}

		const_reference	front() const
		{
			return (this->_sentinel._next->_val);
		}

		reference		back()
		{
			return (this->_sentinel._previous->_val);
		}

		const_reference	back() const
		{
			return (this->_sentinel._previous->_val);
		}

		/* ==MODIFIER FUNCTIONS== */
		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last,
						typename iterator_traits<InputIterator>::type* = NULL)
		{
			this->clear();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		void	assign(size_type n, const value_type& val)
		{
			this->clear();
			for (size_type i = 0; i < n; i++)
				push_back(val);
		}

		void	push_front(const value_type& val)
		{
			node *newNode = this->_alloc.allocate(1);
			this->_alloc.construct(newNode, val);
			newNode->_next = this->_sentinel._next;
			newNode->_previous = &this->_sentinel;
			this->_sentinel._next->_previous = newNode;
			this->_sentinel._next = newNode;
			++this->_size;
		}

		void	pop_front()
		{
			node *tmp = this->_sentinel._next;
			this->_alloc.destroy(tmp);
			this->_alloc.deallocate(tmp, 1);
			--this->_size;
		}

		void	push_back(const value_type& val)
		{
			node *newNode = this->_alloc.allocate(1);
			this->_alloc.construct(newNode, val);
			newNode->_previous = this->_sentinel._previous;
			newNode->_next = &this->_sentinel;
			this->_sentinel._previous->_next = newNode;
			this->_sentinel._previous = newNode;
			++this->_size;
		}

		void	pop_back()
		{
			node *tmp = this->_sentinel._previous;
			this->_alloc.destroy(tmp);
			this->_alloc.deallocate(tmp, 1);
			--this->_size;
		}

//		iterator	insert(iterator position, const value_type& val)
//		{
//
//		}
//
//		void		insert(iterator position, size_type n, const value_type& val)
//		{
//
//		}
//
//		template <class InputIterator>
//		void		insert(iterator position, InputIterator first, InputIterator last,
//						   typename iterator_traits<InputIterator>::type* = NULL)
//		{
//
//		}
//
		iterator	erase(iterator position)
		{
			node *tmp = &(*position);
			position++;
			this->_alloc.destroy(tmp);
			this->_alloc.deallocate(tmp, 1);
			--this->_size;
			return (position);
		}

		iterator	erase(iterator first, iterator last)
		{
			iterator ret = ++last;
			while (1)
			{
				node *tmp = &(*first);
				if (++first == last)
					break;
				this->_alloc.destroy(tmp);
				this->_alloc.deallocate(tmp, 1);
				--this->_size;
			}
			return (ret);
		}

		void	swap(list& x)
		{
			ft::swap(this->_size, x._size);
			ft::swap(this->_sentinel, x._sentinel);
			ft::swap(this->_alloc, x._alloc);
		}

		void	resize(size_type n, value_type val = value_type())
		{
			while (this->_size > n)
				pop_back();
			while (this->_size < n)
				push_back(val);
		}

		void	clear()
		{
			while (this->_size)
				pop_back();
		}

		/* ==OPERATION FUNCTIONS== */
//		void	splice(iterator position, list& x)
//		{
//
//		}
//
//		void	splice(iterator position, list& x, iterator i)
//		{
//
//		}
//
//		void	splice(iterator position, list& x, iterator first, iterator last)
//		{
//
//		}

		void	remove(const value_type& val)
		{
			for (iterator it = this->begin(); it != this->end(); it++)
			{
				if (*it == val)
				{
					node *tmp = &(*it);
					--it;
					this->_alloc.destroy(tmp);
					this->_alloc.deallocate(tmp, 1);
					--this->_size;
				}
			}
		}

		template <class Predicate>
		void	remove_if(Predicate pred)
		{
			for (iterator it = this->begin(); it != this->end(); it++)
			{
				if (pred(*it))
				{
					node *tmp = &(*it);
					--it;
					this->_alloc.destroy(tmp);
					this->_alloc.deallocate(tmp, 1);
					--this->_size;
				}
			}
		}

		void	unique()
		{
			for (iterator it0 = this->begin(); it0 != this->end(); it0++)
			{
				iterator it1 = it0;
				for (; it1 != this->end(); it1++)
				{
					if (*it1 == *it0)
						it1 = erase(it1);
				}
			}
		}

		template <class BinaryPredicate>
		void	unique(BinaryPredicate binary_pred)
		{
			for (iterator it0 = this->begin(); it0 != this->end(); it0++)
			{
				iterator it1 = it0;
				for (; it1 != this->end(); it1++)
				{
					if (binary_pred(it1, it0))
						it1 = erase(it1);
				}
			}
		}

//		void	merge(list& x)
//		{
//
//		}
//
//		template <class Compare>
//		void	merge(list& x, Compare comp)
//		{
//
//		}
//
//		void	sort()
//		{
//
//		}
//
//		template <class Compare>
//		void	sort(Compare comp)
//		{
//
//		}
//
//		void	reverse()
//		{
//
//		}

		/* ==OBSERVER FUNCTIONS== */
		allocator_type	get_allocator() const
		{
			return (this->_alloc);
		}
	};

	/* ==NON-MEMBER FUNCTION OVERLOADS== */

	// relational operators


	template <class T, class Alloc>
	void	swap(list<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
