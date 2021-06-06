#ifndef LISTNODE_HPP
# define LISTNODE_HPP
# include "ANode.hpp"

namespace ft
{
	template<class T>
	class ListNode : public ANode<T>
	{
	public:
		typedef	T			value_type;
		typedef value_type&	reference;
		typedef	value_type*	pointer;
		typedef ListNode	this_type;

		ListNode *_previous;
		ListNode *_next;

		ListNode(const value_type& val) :	ANode<T>(val)
		{}

		ListNode(const ListNode& x)
		{
			*this = x;
		}

		~ListNode()
		{}

		ListNode&	operator=(const ListNode& x)
		{
			this->_previous = x._previous;
			this->_next = x._next;
			this->_val = x._val;
			return (*this);
		}

		ListNode	operator++(int)
		{
			ListNode<T>	tmp(*this);
//			*this = this->_next;
			return (tmp);
		}

		ListNode	operator--(int)
		{
			ListNode<T> tmp(*this);
//			*this = this->_previous;
			return (tmp);
		}

		ListNode&	operator++()
		{
//			*this = this->_next;
			return (*this);
		}

		ListNode&	operator--()
		{
//			*this = *this->_previous;
			return (*this);
		}
		operator ListNode<T>() const
		{
			return ListNode<T>(this->_val);
		}
	};
}

#endif
