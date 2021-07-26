#ifndef ANODE_HPP
# define ANODE_HPP
# include <cstddef>
#include <iostream>

namespace ft
{
	template <class T>
	class ANode
	{
	public:
		typedef	T			value_type;
		typedef value_type&	reference;
		typedef	value_type*	pointer;
		typedef ANode<T>	this_type;


//		ANode		*_previous;
//		ANode		*_next;
		T			_val;

		explicit ANode(const value_type& val = value_type()) :
//				_previous(NULL),
//				_next(NULL),
				_val(val)
		{}

		ANode(const ANode& x)
		{
			*this = x;
		}

		virtual ~ANode()
		{
//			if (this->_next && this->_previous)	// both exist
//			{
//				this->_previous->_next = this->_next;
//				this->_next->_previous = this->_previous;
//			}
//			else if (this->_next)				// only next exists
//				this->_next->_previous = NULL;
//			else if (this->_previous)			// only previous exists
//				this->_previous->_next = NULL;
		}

		ANode&	operator=(const ANode& x)
		{
			this->_previous = x._previous;
//			this->_next = x._next;
//			this->_val = x._val;
			return (*this);
		}

		operator value_type() const
		{
			return (this->_val);
		}

		virtual void	abstr() = 0;
	};
}

#endif
