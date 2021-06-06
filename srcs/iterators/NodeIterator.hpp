#ifndef NODEITERATOR_HPP
# define NODEITERATOR_HPP
# include "../utils/type_traits.hpp"
//# include "BidirectionalIterator.hpp"
# include "../utils/ListNode.hpp"

namespace ft
{
	template <class T, class Node, class Pointer, class Reference, class Category = ft::bidirectional_iterator_tag>
	class NodeIterator
	{
	public:
		typedef ListNode<T>										node;

		typedef NodeIterator<T, node, node*, node&>				this_type;
		typedef NodeIterator<T, node, const node*, const node&>	const_type;
		typedef Category										iterator_category;
		typedef T												value_type;
		typedef ptrdiff_t										difference_type;
		typedef node*											pointer;
		typedef node&											reference;
	private:
		ListNode<T> *_val;

	public:
		NodeIterator()
		{}

		NodeIterator(ListNode<T> *val) : _val(val)
		{
		}

		NodeIterator(const this_type& x)
		{
			*this = x;
		}

		~NodeIterator() {}

		NodeIterator&	operator=(const this_type& x)
		{
			this->_val = x._val;
			return (*this);
		}

		reference operator*() const
		{
			return (*this->_val);
		}

		pointer operator->() const
		{
			return &(*this->_val);
		}

		virtual NodeIterator operator++(int)
		{
			NodeIterator<T, Node, Pointer, Reference> tmp(*this);
			this->_val = this->_val->_next;
			return (tmp);
		}

		virtual NodeIterator operator--(int)
		{
			NodeIterator<T, Node, Pointer, Reference> tmp(*this);
			this->_val = this->_val->_previous;
			return (tmp);
		}

		virtual NodeIterator &operator++()
		{
			this->_val = this->_val->_next;
			return (*this);
		}

		virtual NodeIterator &operator--()
		{
			this->_val = this->_val->_previous;
			return (*this);
		}

		bool operator==(NodeIterator<T, Node, Pointer, Reference> rhs)
		{
			return (this->_val == rhs._val);
		}

		bool operator!=(NodeIterator<T, Node, Pointer, Reference> rhs)
		{
			return !(*this == rhs);
		}

		operator NodeIterator<T, Node, const T*, const T&>() const
		{
			return NodeIterator<T, Node, const T*, const T&>(this->_val);
		}

		operator NodeIterator<T, Node, T*, T&>() const
		{
			return NodeIterator<T, Node, T*, T&>(this->_val);
		}
	};
}

#endif
