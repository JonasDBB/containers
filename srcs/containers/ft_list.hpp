#ifndef FT_LIST_HPP
# define FT_LIST_HPP
# include "../iterators/BidirectionalIterator.hpp"
# include "../iterators/ReverseIterator.hpp"
# include "../utils/type_traits.hpp"
# include "../utils/Utils.hpp"
# include <cstddef>
# include <memory>

namespace ft
{
	template <class T>
	class listNode
	{
	public:
		typedef	T			value_type;
		typedef value_type&	reference;
		typedef	value_type*	pointer;

	private:
		listNode		*_previous;
		listNode		*_next;
		T				_val;

	public:
		explicit listNode() :
				_previous(NULL),
				_next(NULL),
				_val()
		{}

		explicit listNode(const value_type & val = value_type()) :
				_previous(NULL),
				_next(NULL),
				_val(val)
		{}

		listNode(const listNode& x)
		{
			*this = x;
		}

		~listNode()
		{}

		listNode&	operator=(const listNode& x)
		{
			this->_previous = x._previous;
			this->_next = x._next;
			this->_val = x._val;
		}

	};

	template <class T, class Alloc = std::allocator<T> >
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
		// default constructor
		explicit list(const allocator_type& alloc = allocator_type()) :
				_size(0),
				_start(),
				_end(),
				_alloc(alloc)
		{}

		// fill constrcutor
		explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
				_size(0),
				_start(),
				_end(),
				_alloc(alloc)
		{
			for (size_type i = 0; i < n; i++)
				this->push_back(val);
		}

		// range constructor
		template <class InputIterator>
		list(InputIterator first, InputIterator last,
			 const allocator_type& alloc = allocator_type(),
			 typename iterator_traits<InputIterator>::type* = NULL) :
			 _size(0),
			 _start(),
			 _end(),
			 _alloc(alloc)
		{
			this->assign(first, last);
		}

		// copy constructor
		list(const list& x) :
			_size(0),
			_start(),
			_end(),
			_alloc(x._alloc)
		{

		}

		void	push_front(const value_type& val)
		{

		}

		void	push_back(const value_type& val)
		{
			node *newNode = this->_alloc.allocate(1);
			this->_alloc.construct(newNode, val);
			this->_size++;
		}
	};
}

#endif
