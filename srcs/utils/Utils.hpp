#ifndef FT_UTILS_HPP
# define FT_UTILS_HPP
# include "type_traits.hpp"
# include "../ft_vector.hpp"
# include <vector>

namespace ft
{

	template<typename T>
	void	swap(T& first, T& second)
	{
		T tmp = first;
		first = second;
		second = tmp;
	}

	template<typename RandomAccessIterator>
	typename iterator_traits<RandomAccessIterator>::difference_type
	distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
	{
		return (last - first);
	}

	template<typename InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last, input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type ret(0);
		while (first != last)
		{
			first++;
			ret++;
		}
		return (ret);
	}

	template<typename Iterator>
	typename iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last)
	{
		return (distance(first, last, typename iterator_traits<Iterator>::iterator_category()));
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
