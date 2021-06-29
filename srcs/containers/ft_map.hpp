#ifndef FT_MAP_HPP
# define FT_MAP_HPP
# include "../iterators/NodeIterator.hpp"
# include "../iterators/ReverseIterator.hpp"
# include "../utils/type_traits.hpp"
# include "../utils/Utils.hpp"
# include "../utils/ft_pair.hpp"
# include <memory>
#include <functional>

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<T> >
	class map
	{

	};
}

#endif
