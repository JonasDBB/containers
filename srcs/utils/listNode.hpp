#ifndef LISTNODE_HPP
# define LISTNODE_HPP
# include <cstddef>

namespace ft
{
	template <class T>
	class listNode
	{
	public:
		typedef	T			value_type;
		typedef value_type&	reference;
		typedef	value_type*	pointer;

		listNode		*_previous;
		listNode		*_next;
		T				_val;

	public:
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
}

#endif
