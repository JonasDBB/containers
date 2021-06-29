#ifndef FT_MAP_HPP
# define FT_MAP_HPP
# include "../iterators/NodeIterator.hpp"
# include "../iterators/ReverseIterator.hpp"
# include "../utils/type_traits.hpp"
# include "../utils/Utils.hpp"
# include "../utils/ft_pair.hpp"
# include <memory>

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<T> >
	class map
	{
	public:
		typedef	Key															key_type;
		typedef	T															mapped_type;
		typedef	pair<const key_type, mapped_type>							value_type;
		typedef	Compare														key_compare;
		typedef	Alloc														allocator_type;
		typedef	value_type&													reference;
		typedef	const value_type&											const_reference;
		typedef	value_type*													pointer;
		typedef	const value_type*											const_pointer;
		typedef MapNode<value_type>											node;
		typedef NodeIterator<value_type, node, node*, node&>				iterator;
		typedef NodeIterator<value_type, node, const node*, const node&>	const_iterator;
		typedef ReverseIterator<iterator>									reverse_iterator;
		typedef ReverseIterator<const_iterator>								const_reverse_iterator;
		typedef ptrdiff_t													difference_type;
		typedef size_t														size_type;



		class value_compare : public binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			key_compare	comp;
			value_compare(key_compare c) : comp(c) {}
		public:
			bool operator()(const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};
	};
}

#endif
