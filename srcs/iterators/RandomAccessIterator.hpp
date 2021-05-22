#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP
# include <cstddef>
# include "../utils/type_traits.hpp"
# include "BidirectionalIterator.hpp"

namespace ft
{
	template <class T, class Pointer, class Reference,
	        class Category = std::random_access_iterator_tag>
	class RandomAccessIterator {
	public:
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef ptrdiff_t	difference_type;
		typedef value_type	*pointer;
		typedef value_type	&reference;

	private:
		pointer _val;

	public:
		RandomAccessIterator() : _val(NULL)
		{}

		RandomAccessIterator(pointer val) : _val(val)
		{}

		RandomAccessIterator(const RandomAccessIterator<T, Pointer, Reference> &og)
		{
			*this = og;
		}

		virtual ~RandomAccessIterator() {} //NOLINT

		RandomAccessIterator &
		operator=(const RandomAccessIterator<T, Pointer, Reference> &x)
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

		RandomAccessIterator &operator+=(const difference_type &n)
		{
			this->_val += n;
			return (*this);
		}

		RandomAccessIterator &operator-=(const difference_type &n)
		{
			this->_val -= n;
			return (*this);
		}

		RandomAccessIterator operator+(const difference_type &n) const
		{
			RandomAccessIterator<T, Pointer, Reference> tmp(*this);
			tmp._val += n;
			return (tmp);
		}

		difference_type operator-(RandomAccessIterator it) const
		{
			return (this->_val - it._val);
		}

		RandomAccessIterator operator-(const difference_type &n) const
		{
			RandomAccessIterator<T, Pointer, Reference> tmp(*this);
			tmp._val -= n;
			return (tmp);
		}

		RandomAccessIterator operator++(int)
		{
			RandomAccessIterator<T, Pointer, Reference> tmp(*this);
			this->_val++;
			return (tmp);
		}

		RandomAccessIterator operator--(int)
		{
			RandomAccessIterator<T, Pointer, Reference> tmp(*this);
			this->_val--;
			return (tmp);
		}

		RandomAccessIterator &operator++()
		{
			this->_val++;
			return (*this);
		}

		RandomAccessIterator &operator--()
		{
			this->_val--;
			return (*this);
		}

		bool operator==(RandomAccessIterator<T, Pointer, Reference> rhs)
		{
			return (this->_val == rhs._val);
		}

		bool operator!=(RandomAccessIterator<T, Pointer, Reference> rhs)
		{
			return !(this->_val == rhs._val);
		}

		bool operator<(RandomAccessIterator<T, Pointer, Reference> rhs)
		{
			return ((rhs - *this) > 0);
		}

		bool operator>(RandomAccessIterator<T, Pointer, Reference> rhs)
		{
			return (rhs < *this);
		}

		bool operator<=(RandomAccessIterator<T, Pointer, Reference> rhs)
		{
			return !(rhs < *this);
		}

		bool operator>=(RandomAccessIterator<T, Pointer, Reference> rhs)
		{
			return !(*this < rhs);
		}

		reference operator[](difference_type n) const
		{
			return ((*(this + n)->_val));
		}
	};

}
#endif