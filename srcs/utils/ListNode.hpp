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

		ListNode(const value_type& val) : ANode<T>(val), _previous(NULL), _next(NULL)
		{}

		ListNode(const ListNode& x)
		{
			*this = x;
		}

		~ListNode()
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

		ListNode&	operator=(const ListNode& x)
		{
			this->_previous = x._previous;
			this->_next = x._next;
			this->_val = x._val;
			return (*this);
		}

		operator ListNode<T>() const
		{
			return ListNode<T>(this->_val);
		}

		void abstr() {}
	};
}

#endif
