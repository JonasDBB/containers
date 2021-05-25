#ifndef FT_LIST_HPP
# define FT_LIST_HPP
# include "../iterators/BidirectionalIterator.hpp"
# include "../iterators/ReverseIterator.hpp"
# include "../utils/type_traits.hpp"
# include "../utils/Utils.hpp"
# include "../utils/listNode.hpp"
# include <cstddef>
# include <memory>
# include <iostream>

namespace ft
{
	template <class T, class Alloc = std::allocator<listNode<T> > >
	class list
	{
	public:
		typedef	T												value_type;
		typedef	Alloc											allocator_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef value_type*										pointer;
		typedef const value_type*								const_pointer;
		typedef BidirectionalIterator<T, T*, T&>				iterator;
		typedef BidirectionalIterator<T, const T*, const T&>	const_iterator;
		typedef ReverseIterator<iterator>						reverse_iterator;
		typedef ReverseIterator<const_iterator>					const_reverse_iterator;
		typedef ptrdiff_t										difference_type;
		typedef size_t											size_type;
		typedef	listNode<T>										node;

	private:
		size_type		_size;
		node			_start;
		node			_end;
		allocator_type	_alloc;

	public:
		void	printlist()
		{
			node *crnt = this->_start._next;
			std::cout << "begin list:\t[";
			for (size_type i = 0; i < this->_size; i++)
			{
				std::cout << crnt->_val << "]";
				crnt = crnt->_next;
				if (i < this->_size - 1)
					std::cout << " [";
			}
			std::cout << "   endlist" << std::endl;
		}

		void	printlistbackwards()
		{
			node *crnt = this->_end._previous;
			std::cout << "end list:\t[";
			for (size_type i = 0; i < this->_size; i++)
			{
				std::cout << crnt->_val << "]";
				crnt = crnt->_previous;
				if (i < this->_size - 1)
					std::cout << " [";
			}
			std::cout << "   beginlist" << std::endl;
		}
		// default constructor
		explicit list(const allocator_type& alloc = allocator_type()) :
				_size(0),
				_start(0),
				_end(0),
				_alloc(alloc)
		{
			this->_start._next = &this->_end;
			this->_end._previous = &this->_start;
		}

		// fill constrcutor
		explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
				_size(0),
				_start(0),
				_end(0),
				_alloc(alloc)
		{
//			this->assign(n, val);
			this->_start._next = &this->_end;
			this->_end._previous = &this->_start;
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
			_start(x._start),
			_end(x._end),
			_alloc(x._alloc)
		{
			this->assign(x.begin(), x.end());
		}

		/* ==MODIFIER FUNCTIONS== */
		void	push_front(const value_type& val)
		{
			node *newNode = this->_alloc.allocate(1);
			this->_alloc.construct(newNode, val);
			newNode->_next = this->_start._next;
			newNode->_previous = &this->_start;
			this->_start._next->_previous = newNode;
			this->_start._next = newNode;
			this->_size++;
			printlist();
			printlistbackwards();
		}

		void	push_back(const value_type& val)
		{
			node *newNode = this->_alloc.allocate(1);
			this->_alloc.construct(newNode, val);
			newNode->_previous = this->_end._previous;
			newNode->_next = &this->_end;
			this->_end._previous->_next = newNode;
			this->_end._previous = newNode;
			this->_size++;
			printlist();
			printlistbackwards();
		}

	};
}

#endif
