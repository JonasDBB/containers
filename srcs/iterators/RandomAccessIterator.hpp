#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP
# include <cstddef>
# include "../utils/type_traits.hpp"

namespace ft
{
	template <class T, class Pointer, class Reference,
	        class Category = ft::random_access_iterator_tag>
	class RandomAccessIterator {
	public:
		typedef	RandomAccessIterator<T, T*, T&>				this_type;
		typedef RandomAccessIterator<T, const T*, const T&>	const_type;
		typedef Category									iterator_category;
		typedef T											value_type;
		typedef ptrdiff_t									difference_type;
		typedef Pointer										pointer;
		typedef Reference									reference;

	protected:
		pointer _val;

	public:
		RandomAccessIterator() : _val(NULL)
		{}

		explicit RandomAccessIterator(pointer val) : _val(val)
		{}

		RandomAccessIterator(const RandomAccessIterator<T, Pointer, Reference> &og)
		{
			*this = og;
		}

		virtual ~RandomAccessIterator() {}

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
			return !(*this == rhs);
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

		operator RandomAccessIterator<T, const T*, const T&>() const
		{
			return RandomAccessIterator<T, const T*, const T&>(this->_val);
		}

//		operator RandomAccessIterator<T, T*, T&>() const
//		{
//			return RandomAccessIterator<T, T*, T&>(this->_val);
//		}

		template<class T1>
		friend bool operator==(RandomAccessIterator<T1, T1*, T1&> lhs, RandomAccessIterator<T1, T1*, T1&> rhs);
		template<class T1>
		friend bool operator<(RandomAccessIterator<T1, T1*, T1&> lhs, RandomAccessIterator<T1, T1*, T1&> rhs);
		template<class T1, class T2>
		friend bool operator==(RandomAccessIterator<T1, T1*, T1&> lhs, RandomAccessIterator<T1, T2*, T2&> rhs);
		template<class T1, class T2>
		friend bool operator<(RandomAccessIterator<T1, T1*, T1&> lhs, RandomAccessIterator<T1, T2*, T2&> rhs);
	};

	template<class T>
	bool operator==(RandomAccessIterator<T, T*, T&> lhs, RandomAccessIterator<T, T*, T&> rhs)
	{
		return (lhs._val == rhs._val);
	}

	template<class T>
	bool operator!=(RandomAccessIterator<T, T*, T&> lhs, RandomAccessIterator<T, T*, T&> rhs)
	{
		return !(lhs == rhs);
	}

	template<class T>
	bool operator<(RandomAccessIterator<T, T*, T&> lhs, RandomAccessIterator<T, T*, T&> rhs)
	{
		return ((rhs - lhs) > 0);
	}

	template<class T>
	bool operator<=(RandomAccessIterator<T, T*, T&> lhs, RandomAccessIterator<T, T*, T&> rhs)
	{
		return !(rhs < lhs);
	}

	template<class T>
	bool operator>(RandomAccessIterator<T, T*, T&> lhs, RandomAccessIterator<T, T*, T&> rhs)
	{
		return (rhs < lhs);
	}

	template<class T>
	bool operator>=(RandomAccessIterator<T, T*, T&> lhs, RandomAccessIterator<T, T*, T&> rhs)
	{
		return !(lhs < rhs);
	}

	template<class T1, class T2>
	bool operator==(RandomAccessIterator<T1, T1*, T1&> lhs, RandomAccessIterator<T1, T2*, T2&> rhs)
	{
		return (lhs._val == rhs._val);
	}

	template<class T1, class T2>
	bool operator!=(RandomAccessIterator<T1, T1*, T1&> lhs, RandomAccessIterator<T1, T2*, T2&> rhs)
	{
		return !(lhs == rhs);
	}

	template<class T1, class T2>
	bool operator<(RandomAccessIterator<T1, T1*, T1&> lhs, RandomAccessIterator<T1, T2*, T2&> rhs)
	{
		return ((rhs - lhs) > 0);
	}

	template<class T1, class T2>
	bool operator<=(RandomAccessIterator<T1, T1*, T1&> lhs, RandomAccessIterator<T1, T2*, T2&> rhs)
	{
		return !(rhs < lhs);
	}

	template<class T1, class T2>
	bool operator>(RandomAccessIterator<T1, T1*, T1&> lhs, RandomAccessIterator<T1, T2*, T2&> rhs)
	{
		return (rhs < lhs);
	}

	template<class T1, class T2>
	bool operator>=(RandomAccessIterator<T1, T1*, T1&> lhs, RandomAccessIterator<T1, T2*, T2&> rhs)
	{
		return !(lhs < rhs);
	}


	template<class T>
	RandomAccessIterator<T, T*, T&>	operator+(typename RandomAccessIterator<T, T*, T&>::difference_type n,
												const RandomAccessIterator<T, T*, T&>& it)
	{
		return (it + n);
	}
}
#endif
