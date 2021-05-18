#ifndef BIDIRECTIONALITERATOR_HPP
# define BIDIRECTIONALITERATOR_HPP
# include <cstddef>
# include "../utils/type_traits.hpp"

namespace ft
{
	template <class T, class Pointer, class Reference,
			class Category = ft::bidirectional_iterator_tag>
	class BidirectionalIterator {
	public:
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef ptrdiff_t	difference_type;
		typedef value_type	*pointer;
		typedef value_type	&reference;

	private:
		pointer _val;

	public:
		BidirectionalIterator() : _val(NULL)
		{}

		BidirectionalIterator(pointer val) : _val(val)
		{}

		BidirectionalIterator(const BidirectionalIterator<T, Pointer, Reference> &og)
		{
			*this = og;
		}

		virtual ~BidirectionalIterator() {} //NOLINT

		BidirectionalIterator &
		operator=(const BidirectionalIterator<T, Pointer, Reference> &x)
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

		BidirectionalIterator operator++(int)
		{
			BidirectionalIterator<T, Pointer, Reference> tmp(*this);
			this->_val++;
			return (tmp);
		}

		BidirectionalIterator operator--(int)
		{
			BidirectionalIterator<T, Pointer, Reference> tmp(*this);
			this->_val--;
			return (tmp);
		}

		BidirectionalIterator &operator++()
		{
			this->_val++;
			return (*this);
		}

		BidirectionalIterator &operator--()
		{
			this->_val--;
			return (*this);
		}

		bool operator==(BidirectionalIterator<T, Pointer, Reference> rhs)
		{
			return (this->_val == rhs._val);
		}

		bool operator!=(BidirectionalIterator<T, Pointer, Reference> rhs)
		{
			return !(this->_val == rhs._val);
		}
	};

}

#endif
