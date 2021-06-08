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
		node		_start;
		node		_tail;
		node_alloc	_alloc;

	public:
		void	printlist()
		{
			node *crnt = this->_start._next;
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
			node *crnt = this->_tail._previous;
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
				_start(0),
				_tail(0),
				_alloc(alloc)
		{
			this->_start._next = &this->_tail;
			this->_tail._previous = &this->_start;
		}

		// fill constrcutor
		explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
				_size(0),
				_start(0),
				_tail(0),
				_alloc(alloc)
		{
//			this->assign(n, val);
			this->_start._next = &this->_tail;
			this->_tail._previous = &this->_start;
			for (size_type i = 0; i < n; i++)
				this->push_back(val);
		}

//		// range constructor
//		template <class InputIterator>
//		list(InputIterator first, InputIterator last,
//			 const allocator_type& alloc = allocator_type(),
//			 typename iterator_traits<InputIterator>::type* = NULL) :
//			 _size(0),
//			 _start(),
//			 _end(),
//			 _alloc(alloc)
//		{
//			this->assign(first, last);
//		}

		// copy constructor
		list(const list& x) :
				_size(0),
				_start(0),
				_tail(0),
				_alloc(x._alloc)
		{
			this->_start._next = &this->_tail;
			this->_tail._previous = &this->_start;
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
			return(this->_start._next);
		}

		const_iterator			begin() const
		{
			return (const_iterator(this->_start._next));
		}

		iterator				end()
		{
			return (iterator(&this->_tail));
		}

		const_iterator			end() const
		{
			return (const_iterator(&this->_tail));
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
			return (this->_start._next);
		}

		const_reference	front() const
		{
			return (this->_start._next);
		}

		reference		back()
		{
			return (this->_tail._previous);
		}

		const_reference	back() const
		{
			return (this->_tail._previous);
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
			newNode->_next = this->_start._next;
			newNode->_previous = &this->_start;
			this->_start._next->_previous = newNode;
			this->_start._next = newNode;
			++this->_size;
//			printlist();
//			printlistbackwards();
		}

		void	push_back(const value_type& val)
		{
			node *newNode = this->_alloc.allocate(1);
			this->_alloc.construct(newNode, val);
			newNode->_previous = this->_tail._previous;
			newNode->_next = &this->_tail;
			this->_tail._previous->_next = newNode;
			this->_tail._previous = newNode;
			++this->_size;
//			printlist();
//			printlistbackwards();
		}

		void	pop_back()
		{
			node *tmp = this->_tail._previous;
			this->_alloc.destroy(tmp);
			this->_alloc.deallocate(tmp, 1);
			--this->_size;
//			printlist();
//			printlistbackwards();
		}

		void	clear()
		{
			while (this->_size)
				pop_back();
		}

	};
}

#endif
