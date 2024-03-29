#ifndef REVERSEACCESSITERATOR_HPP
# define REVERSEACCESSITERATOR_HPP
# include "../utils/type_traits.hpp"

namespace ft
{
	template<class Iterator>
	class ReverseIterator {

	public:
		typedef Iterator											iterator_type;
		typedef typename Iterator::iterator_category				iterator_category;
		typedef typename Iterator::value_type						value_type;
		typedef typename Iterator::difference_type					difference_type;
		typedef typename Iterator::pointer							pointer;
		typedef typename Iterator::reference						reference;
		typedef ReverseIterator<iterator_type>						this_type;
		typedef ReverseIterator<typename iterator_type::const_type>	const_type;

	private:
		Iterator _base;

	public:
		ReverseIterator() : _base() {}

		explicit ReverseIterator(iterator_type it) : _base(it)
		{}

		template <class Iter>
		ReverseIterator(const ReverseIterator<Iter>& rev_it) : _base(rev_it.base()) {}

		~ReverseIterator() {} //NOLINT

		iterator_type base() const
		{
			return (this->_base);
		}

		reference operator*() const
		{
			Iterator tmp = this->_base;
			return (*(--tmp));
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

		// only works if underlying iterator is of type Random Access Iterator
		ReverseIterator operator+(difference_type n) const
		{
			return (ReverseIterator(this->_base - n));
		}

		// only works if underlying iterator is of type Random Access Iterator
		ReverseIterator& operator+=(difference_type n)
		{
			this->_base -= n;
			return (*this);
		}

		// only works if underlying iterator is of type Random Access Iterator
		ReverseIterator operator-(difference_type n) const
		{
			return (ReverseIterator(this->_base + n));
		}

		// only works if underlying iterator is of type Random Access Iterator
		ReverseIterator& operator-=(difference_type n)
		{
			this->_base += n;
			return (*this);
		}

		// only works if underlying iterator is of type Random Access Iterator
		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

		operator const_type() const
		{
			typename iterator_type::const_type tmp(this->_base);
			return (ReverseIterator<typename iterator_type::const_type>(tmp));
		}
	};

	template <class Iter1, class Iter2>
	bool operator==(const ReverseIterator<Iter1>& lhs, const ReverseIterator<Iter2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator!=(const ReverseIterator<Iter1>& lhs, const ReverseIterator<Iter2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator<(const ReverseIterator<Iter1>& lhs, const ReverseIterator<Iter2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator<=(const ReverseIterator<Iter1>& lhs, const ReverseIterator<Iter2>& rhs)
	{
		return !(lhs.base() >= rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator>(const ReverseIterator<Iter1>& lhs, const ReverseIterator<Iter2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator>=(const ReverseIterator<Iter1>& lhs, const ReverseIterator<Iter2>& rhs)
	{
		return !(lhs.base() >= rhs.base());
	}

	// only works if underlying iterator is of type Random Access Iterator
	template <class Iterator>
	ReverseIterator<Iterator> operator+(typename ReverseIterator<Iterator>::difference_type n,
										const ReverseIterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}

	// only works if underlying iterator is of type Random Access Iterator
	template <class Iterator>
	typename ReverseIterator<Iterator>::difference_type
	operator-(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}
#endif
