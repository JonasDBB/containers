#ifndef MAPNODE_HPP
# define MAPNODE_HPP
# include "ANode.hpp"
# include "ft_pair.hpp"
#include <map>

namespace ft
{
	template<class Key, class T>
	class MapNode : public ANode<pair<Key, T> >
	{
	public:
		typedef	Key									key_type;
		typedef	T									mapped_type;
		typedef pair<const key_type , mapped_type>	value_type;
		typedef value_type&							reference;
		typedef	value_type*							pointer;
		typedef MapNode								this_type;

		MapNode(const )
	};
}

#endif
