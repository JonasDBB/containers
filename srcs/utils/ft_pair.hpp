#ifndef FT_PAIR_HPP
# define FT_PAIR_HPP
#include <iostream>
#include "ANode.hpp"

namespace ft
{
	template<class Key, class T>
	class MapNode;

	template <class T1, class T2>
	struct pair
	{
	public:
		typedef	T1	first_type;
		typedef	T2	second_type;
		first_type	first;
		second_type	second;

		pair() : first(first_type()), second(second_type())
		{}

		template <class U, class V>
		pair(const pair<U, V>& pr) : first(pr.first), second(pr.second)
		{}

		pair(const first_type& a, const second_type& b) : first(a), second(b)
		{}

		explicit pair(const MapNode<const T1, T2>& nd) : first(nd.first), second(nd.second)
		{}

		pair&	operator=(const pair& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	pair<T1, T2>	make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template <class T1, class T2>
	std::ostream& operator<<(std::ostream& os, const pair<T1, T2>& pr)
	{
		os << "(" << pr.first << ", " << pr.second << ")";
		return (os);
	}
}

#endif
