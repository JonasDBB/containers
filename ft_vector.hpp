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

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T					value_type;
		typedef Alloc				allocator_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		// iterators
		typedef ptrdiff_t			difference_type;
		typedef size_t				size_type;

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
			this->_array = new value_type[this->_capacity];
			for (size_type i = 0; i < this->_size; i++)
				this->_array[i] = val;
		}

		// range constructor
//		template <class InputIterator>
//		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) :

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
			this->_array = new value_type[this->_capacity];
			for (size_type i = 0; i < this->_size; i++)
				this->_array[i] = x._array[i];
		}

		// destructor
		~vector()
		{
			delete[] this->_array;
		}

		// assignment operator
		vector&		operator=(const vector& x)
		{
			delete[] this->_array;
			this->_array = NULL;
			this->_capacity = x._capacity;
			this->_size = x._size;
			if (!this->_capacity)
				return (*this);
			this->_array = new value_type[this->_capacity];
			for (size_type i = 0; i < this->_size; i++)
				this->_array[i] = x._array[i];
		}

		/* ==ITERATOR FUNCTIONS== */

		/* ==CAPACITY FUNCTIONS== */
		size_type	size() const
		{
			return (this->_size);
		}

		size_type	max_size() const
		{
			return (this->_alloc.max_size());
		}

		void		resize(size_type n, value_type val = value_type())
		{
			this->reserve(n);
			for (;this->_size < n; this->_size++)
				// addback val
			while (this->_size > n)
				this->_size--;
		}

		size_type	capacity() const
		{
			return (this->_capacity);
		}

		bool		empty() const
		{
			if (!this->_size)
				return (true);
			return (false);
		}

		void		reserve(size_type n)
		{
			if (this->_capacity >= n)
				return;
			if (!this->_capacity)
				this->_capacity = 1;
			while (this->_capacity < n)
				this->_capacity *= 2;
			pointer new_arr = new value_type [this->_capacity];
			for (size_type i = 0; i < this->_size; i++)
				new_arr[i] = this->_array[i];
			delete[] this->_array;
			this->_array = new_arr;
		}

		/* ==ELEMENT ACCESS FUNCTIONS== */

		/* ==MODIFIER FUNCTIONS== */
//		template <class InputIterator>
//		void		assign(InputIterator first, InputIterator last)
//		{}

		void		assign(size_type n, const value_type& val)
		{
			clear();
			reserve(n);
			this->_size = n;
			for (size_type i = 0; i < n; i++)
				this->_array[i] = val;
		}

		void		push_back(const value_type& val)
		{
			reserve(this->_size + 1);
			this->_array[this->_size] = val;
			this->_size++;
		}

		void		pop_back()
		{
			if (this->_size)
				this->_size--;
		}

		// insert

		// erase

		void		swap(vector& x)
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

		void		clear()
		{
			this->_size = 0;
		}
	};


	template <class T, class Alloc>
		void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			x.swap(y);
		}
}
#endif
