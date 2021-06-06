#ifndef BIDIRECTIONALITERATOR_HPP
# define BIDIRECTIONALITERATOR_HPP
# include <cstddef>
# include "../utils/type_traits.hpp"

namespace ft
{
	template <class T, class Pointer, class Reference,
	        class Category = ft::random_access_iterator_tag>
	class BidirectionalIterator {
	public:
		typedef	BidirectionalIterator<T, T*, T&>				this_type;
		typedef BidirectionalIterator<T, const T*, const T&>	const_type;
		typedef Category										iterator_category;
		typedef T												value_type;
		typedef ptrdiff_t										difference_type;
		typedef T*												pointer;
		typedef T&												reference;

	protected:
		pointer _val;

	public:
		BidirectionalIterator() : _val(NULL)
		{}

		explicit BidirectionalIterator(pointer val) : _val(val)
		{}

		BidirectionalIterator(const BidirectionalIterator<T, Pointer, Reference> &og)
		{
			*this = og;
		}

		virtual ~BidirectionalIterator() {}

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

		virtual BidirectionalIterator operator++(int)
		{
			BidirectionalIterator<T, Pointer, Reference> tmp(*this);
			this->_val++;
			return (tmp);
		}

		virtual BidirectionalIterator operator--(int)
		{
			BidirectionalIterator<T, Pointer, Reference> tmp(*this);
			this->_val--;
			return (tmp);
		}

		virtual BidirectionalIterator &operator++()
		{
			this->_val++;
			return (*this);
		}

		virtual BidirectionalIterator &operator--()
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
			return !(*this == rhs);
		}

		operator BidirectionalIterator<T, const T*, const T&>() const
		{
			return BidirectionalIterator<T, const T*, const T&>(this->_val);
		}

		operator BidirectionalIterator<T, T*, T&>() const
		{
			return BidirectionalIterator<T, T*, T&>(this->_val);
		}
	};
}
#endif
