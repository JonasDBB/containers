#ifndef REVERSERANDOMACCESSITERATOR_HPP
# define REVERSERANDOMACCESSITERATOR_HPP
# include "RandomAccessIterator.hpp"
# include "type_traits.hpp"

namespace ft {
	template<class Iterator>

	class reverse_iterator {
	private:
		Iterator _base;

	public:
		typedef Iterator iterator_type;
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;


	public:
		reverse_iterator() : _base() {}

		explicit reverse_iterator(iterator_type it) : _base(it + 1)
		{}

		template <class Iter>
		reverse_iterator( const reverse_iterator<Iter>& rev_it)
		{
			*this = rev_it;
		}

		~reverse_iterator() {} //NOLINT

		iterator_type base() const
		{
			return (this->_base);
		}

		reference operator*() const
		{
			return (*(this->_base - 1));
		}

		reverse_iterator operator+(difference_type n) const
		{
			reverse_iterator tmp(this->_base - n);
			return (tmp);
		}

		reverse_iterator& operator++()
		{
			this->_base--;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			++(*this);
			return (tmp);
		}

		reverse_iterator& operator+=(difference_type n)
		{
			this->_base -= n;
		}

		reverse_iterator operator-(difference_type n) const
		{
			reverse_iterator tmp(this->_base + n);
			return (tmp);
		}

		reverse_iterator& operator--()
		{
			this->_base++;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			--(*this);
			return (tmp);
		}

		reverse_iterator& operator-=(difference_type n)
		{
			this->_base += n;
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
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
										 const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type  operator-(
			const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs - rhs);
	}
}
#endif
