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
		{
			if (this->_next && this->_previous)	// both exist
			{
				this->_previous->_next = this->_next;
				this->_next->_previous = this->_previous;
			}
			else if (this->_next)				// only next exists
				this->_next->_previous = NULL;
			else if (this->_previous)			// only previous exists
				this->_previous->_next = NULL;
		}

		listNode&	operator=(const listNode& x)
		{
			this->_previous = x._previous;
			this->_next = x._next;
			this->_val = x._val;
			return (*this);
		}

		listNode	operator++(int)
		{
			listNode<T>	tmp(*this);
			*this = this->_next;
			return (tmp);
		}

		listNode	operator--(int)
		{
			listNode<T> tmp(*this);
			*this = this->_previous;
			return (tmp);
		}

		listNode&	operator++()
		{
			*this = this->_next;
		}

		listNode&	operator--()
		{
			*this = *this->_previous;
		}

		operator value_type() const
		{
			return (this->_val);
		}
	};
}

#endif
