#ifndef NODEITERATOR_HPP
# define NODEITERATOR_HPP
# include "BidirectionalIterator.hpp"
# include "../utils/type_traits.hpp"
# include "../utils/ListNode.hpp"

namespace ft
{
	template <class T, class Node, class Pointer, class Reference, class Category = ft::bidirectional_iterator_tag>
	class NodeIterator : public BidirectionalIterator<Node, Node*, Node&>
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

	public:
		NodeIterator() //: _val(NULL)
		{
			this->_val = NULL;
		}

		NodeIterator(pointer val) //: _val(val)
		{
			this->_val = (val);
		}

		NodeIterator(const this_type& x)
		{
			*this = x;
		}

		~NodeIterator() {}

		NodeIterator&	operator=(const this_type& x)
		{
			BidirectionalIterator<Node,Node*, Node&>::operator=(x);
//			this->_val = &(*x);
			return (*this);
		}

		NodeIterator operator++(int)
		{
			NodeIterator<T, Node, Pointer, Reference> tmp(*this);
			this->_val = this->_val->_next;
			return (tmp);
		}

		NodeIterator operator--(int)
		{
			NodeIterator<T, Node, Pointer, Reference> tmp(*this);
			this->_val = this->_val->_previous;
			return (tmp);
		}

		NodeIterator &operator++()
		{
			this->_val = this->_val->_next;
			return (*this);
		}

		NodeIterator &operator--()
		{
			this->_val = this->_val->_previous;
			return (*this);
		}

//		operator const_type() const
//		{
//			return const_type(this->_val);
//		}

		operator this_type() const
		{
			return this_type(this->_val);
		}
	};
}

#endif
