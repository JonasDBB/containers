#ifndef FT_UTILS_HPP
# define FT_UTILS_HPP
# include "type_traits.hpp"

namespace ft
{
	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef	Arg1	first_argument_type;
		typedef	Arg2	second_argument_type;
		typedef	Result	result_type;
	};

	template <class T>
	struct less : binary_function<T, T, bool>
	{ bool operator()(const T& x, const T& y) const { return x < y; } };

	template<class T>
	void	swap(T& first, T& second)
	{
		T tmp = first;
		first = second;
		second = tmp;
	}

	template<class T>
	T	max(const T& first, const T& second)
	{
		return (first > second ? first : second);
	}

	template<class RandomAccessIterator>
	typename iterator_traits<RandomAccessIterator>::difference_type
	distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
	{
		return (last - first);
	}

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last, input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type ret(0);
		for (; first != last; ++first)
			++ret;
		return (ret);
	}

	template<typename Iterator>
	typename iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last)
	{
		return (distance(first, last, typename iterator_traits<Iterator>::iterator_category()));
	}

	template <class InputIterator, class Distance>
	void advance(InputIterator& it, Distance n, random_access_iterator_tag)
	{
		it += n;
	}

	template <class InputIterator, class Distance>
	void advance(InputIterator& it, Distance n, input_iterator_tag)
	{
		if (n >= 0)
		{
			for (; n > 0; --n)
				++it;
		}
		else
		{
			for (; n < 0; ++n)
				--it;
		}
	}

	template <class iterator, class Distance>
	void	advance(iterator& it, Distance n)
	{
		ft::advance(it, n, typename iterator_traits<iterator>::iterator_category());
	}

	template <typename InputIterator1, typename InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}



}
#endif
