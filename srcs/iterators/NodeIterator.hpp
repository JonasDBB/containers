#ifndef NODEITERATOR_HPP
# define NODEITERATOR_HPP
# include "BidirectionalIterator.hpp"
# include "../utils/ANode.hpp"

namespace ft
{
	template <class T, class Pointer, class Reference, class Category = ft::random_access_iterator_tag>
	class NodeIterator : public BidirectionalIterator<ANode<T>, ANode<T>*, ANode<T>&>
	{
	public:
		typedef ANode<T>										node;
		typedef BidirectionalIterator<node, node*, node&>		parent_type;
		typedef NodeIterator<node, node*, node&>				this_type;
		typedef NodeIterator<node, const node*, const node&>	const_type;
		typedef Category										iterator_category;
		typedef T												value_type;
		typedef ptrdiff_t										difference_type;
		typedef T*												pointer;
		typedef T&												reference;

		NodeIterator() : parent_type()
		{}

		explicit NodeIterator(pointer val) : parent_type(val)
		{}

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

		virtual NodeIterator operator++(int)
		{
			NodeIterator<T, Pointer, Reference> tmp(*this);
			this->_val = this->_val._next;
			return (tmp);
		}

		virtual NodeIterator operator--(int)
		{
			NodeIterator<T, Pointer, Reference> tmp(*this);
			this->_val = this->_val._previous;
			return (tmp);
		}

		virtual NodeIterator &operator++()
		{
			this->_val = this->_val._next;
			return (*this);
		}

		virtual NodeIterator &operator--()
		{
			this->_val = this->_val._previous;
			return (*this);
		}
	};
}

#endif
