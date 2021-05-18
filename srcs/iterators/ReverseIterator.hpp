#ifndef REVERSEACCESSITERATOR_HPP
# define REVERSEACCESSITERATOR_HPP
# include "RandomAccessIterator.hpp"
# include "BidirectionalIterator.hpp"
# include "../utils/type_traits.hpp"

namespace ft {
	template<class Iterator>

	class ReverseIterator {

	public:
		typedef Iterator								iterator_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;

	private:
		Iterator _base;

	public:
		ReverseIterator() : _base() {}

		explicit ReverseIterator(iterator_type it)
		{
			Iterator tmp(it);
			this->_base = ++tmp;
		}

		template <class Iter>
		explicit ReverseIterator(const ReverseIterator<Iter>& rev_it) : _base(rev_it._base) {}

		~ReverseIterator() {} //NOLINT

		iterator_type base() const
		{
			return (this->_base);
		}

		reference operator*() const
		{
			Iterator tmp = this->_base;
			return (*--tmp);
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		ReverseIterator& operator++()
		{
			this->_base--;
			return (*this);
		}

		ReverseIterator operator++(int)
		{
			ReverseIterator tmp(*this);
			this->_base--;
			return (tmp);
		}

		ReverseIterator& operator--()
		{
			this->_base++;
			return (*this);
		}

		ReverseIterator operator--(int)
		{
			ReverseIterator tmp(*this);
			this->_base++;
			return (tmp);
		}

		// only works for Random Access Iterator
		ReverseIterator operator+(difference_type n) const
		{
			return (ReverseIterator(this->_base - n));
		}

		// only works for Random Access Iterator
		ReverseIterator& operator+=(difference_type n)
		{
			this->_base -= n;
			return (*this);
		}

		// only works for Random Access Iterator
		ReverseIterator operator-(difference_type n) const
		{
			return (ReverseIterator(this->_base + n));
		}

		// only works for Random Access Iterator
		ReverseIterator& operator-=(difference_type n)
		{
			this->_base += n;
			return (*this);
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}
	};

	template <class Iterator>
	bool operator==(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Iterator>
	bool operator<(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (rhs.base() < lhs.base());
	}

	template <class Iterator>
	bool operator<=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class Iterator>
	bool operator>(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (rhs < lhs);
	}

	template <class Iterator>
	bool operator>=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class Iterator>
	ReverseIterator<Iterator> operator+(typename ReverseIterator<Iterator>::difference_type n,
										const ReverseIterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}

	template <class Iterator>
	typename ReverseIterator<Iterator>::difference_type  operator-(
			const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}
#endif
