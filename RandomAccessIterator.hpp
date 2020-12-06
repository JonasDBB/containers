/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   random_access_iterator.hpp                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 11:28:30 by jbennink      #+#    #+#                 */
/*   Updated: 2020/12/06 11:28:30 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP
# include <cstddef>
# include <iterator>

namespace ft
{
	template <class T, class Pointer, class Reference,
	        class Category = std::random_access_iterator_tag, class Distance = ptrdiff_t>
	class RandomAccessIterator {
	public:
		typedef Category iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef value_type *pointer;
		typedef value_type &reference;

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

		~RandomAccessIterator()
		{} //NOLINT

		reference operator*() const
		{
			return (*this->_val);
		}

		pointer operator->() const
		{
			return &(*this->_val);
		}

		RandomAccessIterator &
		operator=(const RandomAccessIterator<T, Pointer, Reference> &x)
		{
			this->_val = x._val;
			return (*this);
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

		bool operator==(RandomAccessIterator<T, Pointer, Reference>& rhs)
		{
			return (this->_val == rhs._val);
		}

		bool operator!=(RandomAccessIterator<T, Pointer, Reference>& rhs)
		{
			return (this->_val != rhs._val);
		}
	};

	template<class Iterator>
	ptrdiff_t	distance(Iterator first, Iterator last)
	{
		ptrdiff_t	ret = 0;
		while (first != last)
		{
			first++;
			ret++;
		}
		return (ret);
	}
}
#endif
