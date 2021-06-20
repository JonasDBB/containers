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
		// default constructor
		explicit list(const allocator_type& alloc = allocator_type()) :
				_size(0),
				_sentinel(T()),
				_alloc(alloc)
		{
			this->_sentinel._next = &this->_sentinel;
			this->_sentinel._previous = &this->_sentinel;
		}

		// fill constrcutor
		explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
				_size(0),
				_sentinel(T()),
				_alloc(alloc)
		{
			this->_sentinel._next = &this->_sentinel;
			this->_sentinel._previous = &this->_sentinel;
			this->assign(n, val);
		}

		// range constructor
		template <class InputIterator>
		list(InputIterator first, InputIterator last,
			 const allocator_type& alloc = allocator_type(),
			 typename iterator_traits<InputIterator>::type* = NULL) :
			 _size(0),
			 _sentinel(T()),
			 _alloc(alloc)
		{
			this->_sentinel._next = &this->_sentinel;
			this->_sentinel._previous = &this->_sentinel;
			this->assign(first, last);
		}

		// copy constructor
		list(const list& x) :
				_size(0),
				_sentinel(T()),
				_alloc(x._alloc)
		{
			this->_sentinel._next = &this->_sentinel;
			this->_sentinel._previous = &this->_sentinel;
			this->assign(x.begin(), x.end());
		}

		// destructor
		~list()
		{
			clear();
		}

		// assignment operator
		list&	operator=(const list& x)
		{
			this->clear();
			this->_alloc = x._alloc;
		 	this->assign(x.begin(), x.end());
			return (*this);
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
			return (iterator(this->_sentinel._next->_previous));
		}

		const_iterator			end() const
		{
			return (const_iterator(this->_sentinel._next->_previous));
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

		iterator	insert(iterator position, const value_type& val)
		{
			node *newNode = this->_alloc.allocate(1);
			this->_alloc.construct(newNode, val);
			node *loc = &(*position);
			newNode->_previous = loc->_previous;
			newNode->_next = loc;
			loc->_previous->_next = newNode;
			loc->_previous = newNode;
			++this->_size;
			return (iterator(newNode));
		}

		void		insert(iterator position, size_type n, const value_type& val)
		{
			for (size_type i = 0; i < n; ++i)
				insert(position, val);
		}

		template <class InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last,
						   typename iterator_traits<InputIterator>::type* = NULL)
		{
			for (; first != last; ++first)
				insert(position, *first);
		}

		iterator	erase(iterator position)
		{
			node *tmp = &(*position);
			++position;
			this->_alloc.destroy(tmp);
			this->_alloc.deallocate(tmp, 1);
			--this->_size;
			return (position);
		}

		iterator	erase(iterator first, iterator last)
		{
			while (first != last)
				this->erase(first++);
			return (last);
		}

		void	swap(list& x)
		{
			ft::swap(*this, x);
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
		void	splice(iterator position, list& x)
		{
			splice(position, x, x.begin(), x.end());
		}

		void	splice(iterator position, list& x, iterator i)
		{
			iterator n(i);
			splice(position, x, i, ++n);
		}

		void	splice(iterator position, list& x, iterator first, iterator last)
		{
			node *loc = &(*position);
			node *firstLoc = &(*first);
			node *lastLoc = &(*--last);
			size_type len = ft::distance(first, last) + 1;
			this->_size += len;
			x._size -= len;
			// remove from x list
			firstLoc->_previous->_next = lastLoc->_next;
			lastLoc->_next->_previous = firstLoc->_previous;
			// set links in new elems to this list
			firstLoc->_previous = loc->_previous;
			lastLoc->_next = loc;
			// link this to new elems
			loc->_previous->_next = firstLoc;
			loc->_previous = lastLoc;
		}

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
				++it1;
				for (; it1 != this->end(); it1++)
				{
					if (*it1 == *it0)
						it1 = erase(it1);
					if (it1 == this->end())
						break;
				}
			}
		}

		template <class BinaryPredicate>
		void	unique(BinaryPredicate binary_pred)
		{
			for (iterator it0 = this->begin(); it0 != this->end(); it0++)
			{
				iterator it1 = it0;
				++it1;
				for (; it1 != this->end(); it1++)
				{
					if (binary_pred(*it1, *it0))
						it1 = erase(it1);
					if (it1 == this->end())
						break;
				}
			}
		}

		void	merge(list& x)
		{
			if (this == &x)
				return;
			while (x._size)
			{
				iterator it0 = x.begin();
				iterator it1 = this->begin();
				for (; *it1 < *it0 && it1 != this->end(); ++it1);
				node* fromX = &(*it0);
				node* loc = &(*it1);
				fromX->_next->_previous = fromX->_previous;
				fromX->_previous->_next = fromX->_next;
				fromX->_previous = loc->_previous;
				fromX->_next = loc;
				loc->_previous->_next = fromX;
				loc->_previous = fromX;
				++this->_size;
				--x._size;
			}
		}

		template <class Compare>
		void	merge(list& x, Compare comp)
		{
			if (this == &x)
				return;
			while (x._size)
			{
				iterator it0 = x.begin();
				iterator it1 = this->begin();
				for (; !comp(*it0, *it1) && it1 != this->end(); ++it1);
				node* fromX = &(*it0);
				node* loc = &(*it1);
				fromX->_next->_previous = fromX->_previous;
				fromX->_previous->_next = fromX->_next;
				fromX->_previous = loc->_previous;
				fromX->_next = loc;
				loc->_previous->_next = fromX;
				loc->_previous = fromX;
				++this->_size;
				--x._size;
			}
		}

		void	sort()
		{
			if (this->_size <= 1)
				return;
			iterator it = begin();
			for (size_type m = this->_size / 2; m; --m, ++it);
			ft::list<T> tmp;
			tmp.splice(tmp.begin(), *this, it, this->end());
			this->sort();
			tmp.sort();
			this->merge(tmp);
		}

		template <class Compare>
		void	sort(Compare comp)
		{
			if (this->_size <= 1)
				return;
			iterator it = begin();
			for (size_type m = this->_size / 2; m; --m, ++it);
			ft::list<T> tmp;
			tmp.splice(tmp.begin(), *this, it, this->end());
			this->sort();
			tmp.sort();
			this->merge(tmp, comp);
		}

		void	reverse()
		{
			ft::swap(this->_sentinel._next, this->_sentinel._previous);
			for (iterator it = this->begin(); it != this->end(); it++)
				ft::swap((*it)._next, (*it)._previous);
		}

		/* ==OBSERVER FUNCTIONS== */
		allocator_type	get_allocator() const
		{
			return (this->_alloc);
		}
	};

	/* ==NON-MEMBER FUNCTION OVERLOADS== */

	template <class T, class Alloc>
	bool	operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::list<T,Alloc>::iterator it0 = lhs.begin();
		typename ft::list<T,Alloc>::iterator it1 = rhs.begin();
		for (; it0 != lhs.end() && it1 != rhs.end(); ++it0, ++it1)
		{
			if (*it0 != *it1)
				return (false);
		}
		return (true);
	}

	template <class T, class Alloc>
	bool	operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool	operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool	operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}


	template <class T, class Alloc>
	void	swap(list<T,Alloc>& x, list<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
