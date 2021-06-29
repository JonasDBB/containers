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

		explicit ListNode(const value_type& val) : ANode<T>(val), _previous(NULL), _next(NULL)
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

		ListNode*	previous() const
		{
			return (this->_previous);
		}

		ListNode*	next() const
		{
			return (this->_next);
		}

		operator ListNode<T>() const
		{
			return ListNode<T>(this->_val);
		}

		operator value_type() const
		{
			return (this->_val);
		}

		ListNode&	operator=(const value_type& val)
		{
			this->_val = val;
			return (*this);
		}

		void abstr() {}

		bool	operator==(const ListNode<T> &rhs) const
		{
			return (this->_val == rhs._val);
		}

		bool	operator!=(const ListNode<T> &rhs) const
		{
			return (this->_val != rhs._val);
		}

		bool	operator<(const ListNode<T> &rhs) const
		{
			return (this->_val < rhs._val);
		}

		bool	operator>(const ListNode<T> &rhs) const
		{
			return (this->_val > rhs._val);
		}

		bool	operator<=(const ListNode<T> &rhs) const
		{
			return (this->_val <= rhs._val);
		}

		bool	operator>=(const ListNode<T> &rhs) const
		{
			return (this->_val >= rhs._val);
		}

		bool	operator==(const T &rhs) const	{ return (this->_val == rhs); }

		bool	operator!=(const T &rhs) const	{ return (this->_val != rhs); }

		bool	operator<(const T &rhs) const	{ return (this->_val < rhs); }

		bool	operator>(const T &rhs) const	{ return (this->_val > rhs); }

		bool	operator<=(const T &rhs) const	{ return (this->_val <= rhs); }

		bool	operator>=(const T &rhs) const	{ return (this->_val >= rhs); }

		template <class T1>
		friend 	bool	operator==(const T1 &lhs, const ListNode<T1> &rhs);
		template <class T1>
		friend 	bool	operator<(const T1 &lhs, const ListNode<T1> &rhs);

	};

	template <class T>
	bool	operator==(const T &lhs, const ListNode<T> &rhs) 	{ return (lhs == rhs._val); }

	template <class T>
	bool	operator!=(const T &lhs, const ListNode<T> &rhs)	{ return !(lhs == rhs); }

	template <class T>
	bool	operator<(const T &lhs, const ListNode<T> &rhs)		{ return (lhs < rhs._val); }

	template <class T>
	bool	operator>(const T &lhs, const ListNode<T> &rhs)		{ return !(rhs > lhs); }

	template <class T>
	bool	operator<=(const T &lhs, const ListNode<T> &rhs)	{ return !(rhs < lhs); }

	template <class T>
	bool	operator>=(const T &lhs, const ListNode<T> &rhs)	{ return !(lhs < rhs); }

	template<class T>
	std::ostream& operator<<(std::ostream& os, const ListNode<T> &node)
	{
		os << node._val;
		return (os);
	}
}

#endif
