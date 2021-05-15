#ifndef REVERSERANDOMACCESSITERATOR_HPP
# define REVERSERANDOMACCESSITERATOR_HPP
# include "RandomAccessIterator.hpp"
# include "type_traits.hpp"

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

		explicit ReverseIterator(iterator_type it) : _base(it + 1)
		{}

		template <class Iter>
		ReverseIterator(const ReverseIterator<Iter>& rev_it)
		{
			*this = rev_it;
		}

		~ReverseIterator() {} //NOLINT

		iterator_type base() const
		{
			return (this->_base);
		}

		reference operator*() const
		{
			return (*(this->_base - 1));
		}

		ReverseIterator operator+(difference_type n) const
		{
			ReverseIterator tmp(this->_base - n - 1);
			return (tmp);
		}

		ReverseIterator& operator++()
		{
			this->_base--;
			return (*this);
		}

		ReverseIterator operator++(int)
		{
			ReverseIterator tmp(*this);
			++(*this);
			return (tmp);
		}

		ReverseIterator& operator+=(difference_type n)
		{
			this->_base -= n;
			return (*this);
		}

		ReverseIterator operator-(difference_type n) const
		{
			ReverseIterator tmp(this->_base + n - 1);
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
			--(*this);
			return (tmp);
		}

		ReverseIterator& operator-=(difference_type n)
		{
			this->_base += n;
			return (*this);
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type n) const
		{
			return (this->_base[-n-1]);
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
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
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
