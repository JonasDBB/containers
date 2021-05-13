/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vector.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 10:55:25 by jbennink      #+#    #+#                 */
/*   Updated: 2020/11/30 10:55:25 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP
# include <cstddef>
# include "RandomAccessIterator.hpp"
# include "type_traits.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T													value_type;
		typedef Alloc												allocator_type;
		typedef value_type&											reference;
		typedef const value_type&									const_reference;
		typedef value_type*											pointer;
		typedef const value_type*									const_pointer;
		typedef RandomAccessIterator<T, T*, T&>						iterator;
		typedef RandomAccessIterator<const T, const T*, const T&>	const_iterator;
		typedef RandomAccessIterator<T, T*, T&>						reverse_iterator;
		typedef RandomAccessIterator<const T, const T*, const T&>	const_reverse_iterator;
		typedef ptrdiff_t											difference_type;
		typedef size_t												size_type;

	private:
		size_type		_capacity;
		size_type		_size;
		pointer			_array;
		allocator_type	_alloc;

	public:
		// default constructor
		explicit vector(const allocator_type& alloc = allocator_type()) :
			_capacity(0),
			_size(0),
			_array(NULL),
			_alloc(alloc)
		{}

		// fill constructor
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
			_capacity(1),
			_size(n),
			_alloc(alloc)
		{
			while (this->_capacity < this->_size)
				this->_capacity << 1;
			this->_array = this->_alloc.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(this->_array[i], val);
		}

		// range constructor
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type()) :
			_capacity(0),
			_size(0),
			_array(NULL),
			_alloc(alloc)
		{
			assign(first, last);
		}

		// copy constructor
		vector(const vector& x) :
			_capacity(x._capacity),
			_size(x._size),
			_alloc(x._alloc)
		{
			delete[] this->_array;
			this->_array = NULL;
			if (!this->_capacity)
				return;
			this->_array = this->_alloc.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; i++)
				this->_array[i] = x._array[i];
		}

		// destructor
		~vector()
		{
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.destroy(&this->_array[i]);
			this->_alloc.deallocate(this->_array, this->_capacity);
		}

		// assignment operator
		vector&			operator=(const vector& x)
		{
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.destroy(&this->_array[i]);
			this->_alloc.deallocate(this->_array, this->_capacity);
			this->_array = NULL;
			this->_capacity = x._capacity;
			this->_size = x._size;
			if (!this->_capacity)
				return (*this);
			this->_array = this->_alloc.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(this->_array[i], x._array[i]);//this->_array[i] = x._array[i];
			return (*this);
		}

		/* ==ITERATOR FUNCTIONS== */
		iterator		begin()
		{
			return (iterator(this->_array));
		}

		const_iterator		begin() const
		{
			return (const_iterator(this->_array));
		}

		iterator		end()
		{
			return (iterator(&this->_array[this->_size]));
		}

		const_iterator		end() const
		{
			return (const_iterator(&this->_array[this->_size]));
		}



		// need rbegin and rend

		/* ==CAPACITY FUNCTIONS== */
		size_type		size() const
		{
			return (this->_size);
		}

		size_type		max_size() const
		{
			return (this->_alloc.max_size());
		}

		void			resize(size_type n, value_type val = value_type())
		{
			reserve(n);
			for (;this->_size < n; this->_size++)
				push_back(val);
			while (this->_size > n)
				this->_size--;
		}

		size_type		capacity() const
		{
			return (this->_capacity);
		}

		bool			empty() const
		{
			if (!this->_size)
				return (true);
			return (false);
		}

		void			reserve(size_type n)
		{
			if (this->_capacity >= n)
				return;
			if (n > this->max_size())
				throw std::length_error("ft::vector: length error");
			this->_capacity = n;
			pointer new_arr = this->_alloc.allocate(this->_capacity); //NOLINT
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(&new_arr[i], this->_array[i]);
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.destroy(&this->_array[i]);
			this->_alloc.deallocate(this->_array, this->_capacity);
			this->_array = new_arr;
		}

		/* ==ELEMENT ACCESS FUNCTIONS== */
		reference		operator[](size_type n)
		{
			return (this->_array[n]);
		}

		const_reference	operator[](size_type n) const
		{
			return (this->_array[n]);
		}

		reference		at(size_type n)
		{
			if (n < 0 || n >= this->_size)
				throw(std::out_of_range("ft::vector: index out of range"));
			return (this->_array[n]);
		}

		const_reference	at(size_type n) const
		{
			if (n < 0 || n >= this->_size)
				throw(std::out_of_range("ft::vector: index out of range"));
			return (this->_array[n]);
		}

		reference		front()
		{
			return (this->_array[0]);
		}

		const_reference	front() const
		{
			return (this->_array[0]);
		}

		reference		back()
		{
			return (this->_array[this->_size - 1]);
		}

		const_reference	back() const
		{
			return (this->_array[this->_size - 1]);
		}

		/* ==MODIFIER FUNCTIONS== */
		template <class InputIterator>
		void			assign(InputIterator first, InputIterator last,
				typename enable_if<is_iterator<typename InputIterator::iterator_category>::result, InputIterator>::type* = NULL)
		{
			clear();
			reserve(ft::distance(first, last));
			while (first != last)
			{
				this->push_back(*first);
				first++;
			}
		}

		void			assign(size_type n, const value_type& val)
		{
			clear();
			reserve(n);
			this->_size = n;
			for (size_type i = 0; i < n; i++)
				this->_alloc.construct(&this->_array[i], val);
		}

		void			push_back(const value_type& val)
		{
			if (this->_size == this->_capacity)
			{
				if (!this->_capacity)
					this->_capacity = 1;
				reserve(2 * this->_capacity);
			}
			this->_alloc.construct(&this->_array[this->_size], val);
			this->_size++;
		}

		void			pop_back()
		{
			if (!this->_size)
				return;
			this->_alloc.destroy(this->_array[this->_size - 1]);
			this->_size--;
		}

		iterator		insert(iterator position, const value_type& val)
		{
			resize(this->_size + 1);
			iterator tmp(end() - 1);
			while (tmp != position)
			{
				*tmp = *(tmp - 1);
				tmp--;
			}
			this->_alloc.construct(*position, val);
			return (position);
		}

		void			insert(iterator position, size_type n, const value_type& val)
		{
			resize(this->_size + n);
			iterator tmp(end() - 1);
			while (tmp - n != position)
			{
				*tmp = *(tmp - n);
				tmp--;
			}
			*tmp = *(tmp - n);
			for (size_type i = 0; i < n; i++)
			{
				this->_alloc.construct(*position, val);
				position++;
			}
		}

		template <class InputIterator>
		void			insert(iterator position, InputIterator first, InputIterator last)
		{
			difference_type	len = ft::distance(first, last);
			resize(this->_size + len);
			iterator tmp(end() - 1);
			while (tmp - len != position)
			{
				*tmp = *(tmp - len);
				tmp--;
			}
			*tmp = *(tmp - len);
			while (first != last)
			{
				this->_alloc.construct(*position, *first);
				position++;
				first++;
			}
		}

		iterator		erase(iterator position)
		{
			iterator	tmp(position);

			this->_alloc.destroy(*position);
			this->_size--;
			position++;
			while (position != end())
			{
				*(position - 1) = *position;
				position++;
			}
			return (tmp);
		}

		iterator		erase(iterator first, iterator last)
		{
			iterator		tmp(first);
			difference_type	len = ft::distance(first, last);

			for (iterator tmp1 = first; tmp1 != last; tmp1++)
				this->_alloc.destroy(*tmp);
			this->_size -= len;
			while (last != end())
			{
				*first = *last;
				first++;
				last++;
			}
			return (tmp);
		}

		void			swap(vector& x)
		{
			size_type tmp = this->_size;
			this->_size = x._size;
			x._size = tmp;
			tmp = this->_capacity;
			this->_capacity = x._capacity;
			x._capacity = tmp;
			pointer tmp_arr = this->_array;
			this->_array = x._array;
			x._array = tmp_arr;
		}

		void			clear()
		{
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.destroy(&this->_array[i]);
			this->_size = 0;
		}

		allocator_type	get_allocator() const
		{
			return (this->_alloc);
		}

	};

	/* ==NON-MEMBER FUNCTION OVERLOADS== */

	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (typename ft::vector<T>::size_type i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
	}

	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lhs == rhs);
	}

	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}
#endif
