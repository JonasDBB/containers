#ifndef MAPNODE_HPP
# define MAPNODE_HPP
# include "ANode.hpp"
# include "ft_pair.hpp"
# include "../utils/Utils.hpp"

namespace ft
{
	template<class Key, class T>
	class MapNode : public ANode<pair<Key, T> >
	{
	public:
		typedef	Key									key_type;
		typedef	T									mapped_type;
		typedef pair<const key_type, mapped_type>	value_type;
		typedef value_type&							reference;
		typedef	value_type*							pointer;
		typedef MapNode								this_type;
		typedef	ANode<pair<Key, T> >				A_type;

		MapNode	*_parent;
		MapNode	*_left;
		MapNode	*_right;
		int		_height;

		explicit MapNode(const value_type& val) : A_type(val),
		_parent(NULL), _left(NULL), _right(NULL), _height(1)
		{}

		MapNode(const MapNode& x)
		{
			*this = x;
		}

		~MapNode()
		{

		}

		MapNode&	operator=(const MapNode& x)
		{
			this->_parent = x._parent;
			this->_left = x._left;
			this->_right = x._right;
			this->_height = x._height;
			this->_val = x._val;
			return (*this);
		}

		MapNode*	previous() const
		{
			MapNode* ret;

			if (this->_left)
			{
				ret = this->_left;
				while (ret->_right)
					ret = ret->_right;
				return (ret);
			}
			else
			{
				ret = this->_parent;
				if (this == ret->_right)
					return (ret);
				else
				{
					while (ret == ret->_parent->_left && ret->_parent)
						ret = ret->_parent;
					if (!ret->_parent)
						// lowest node
					return (ret);
				}
				return (ret);
			}
		}

		MapNode*	next() const
		{
			MapNode* ret;

			if (this->_right)
			{
				ret = this->_right;
				while (ret->_left)
					ret = ret->_left;
				return (ret);
			}
			else
			{
				ret = this->_parent;
				if (this == ret->_left)
					return (ret);
				else
				{
					while (ret == ret->_parent->_right && ret->_parent)
						ret = ret->_parent;
					if (!ret->_parent)
						// highest node
					return (ret);
				}
				return (ret);
			}
		}

		const key_type&	key() const
		{
			return (this->_val.first);
		}

		const mapped_type& value() const
		{
			return (this->_val.second);
		}

		int		getBalance() const
		{
			if (!this->_left && !this->_right)
				return (0);
			if (!this->_left)
				return (-1 * this->_right->_height);
			if (!this->_right)
				return (this->_left->_height);
			return (this->_left->_height - this->_right->_height);
		}

		void	updateHeight()
		{
			if (!this->_left && !this->_right)
				this->_height = 1;
			else if (!this->_left)
				this->_height = this->_right->_height + 1;
			else if (!this->_right)
				this->_height = this->_left->_height + 1;
			else
				this->_height = ft::max(this->_left->_height, this->_right->_height) + 1;
		}

		void	rightRotate()
		{
			MapNode<Key, T> *leftChild = this->_left;
			MapNode<Key, T> *leftRightChild = this->_left->_right;

			leftChild->_right = this;
			this->_left = leftRightChild;
			if (leftRightChild)
				leftRightChild->_parent = this;
			leftChild->_parent = this->_parent;
			this->_parent = leftChild;
			if (leftChild->_parent)
			{
				if (this == leftChild->_parent->_left)
					leftChild->_parent->_left = leftChild;
				else
					leftChild->_parent->_right = leftChild;
			}

			this->updateHeight();
			leftChild->updateHeight();
		}

		void	leftRotate()
		{
			MapNode<Key, T> *rightChild = this->_right;
			MapNode<Key, T> *rightLeftChild = this->_right->_left;

			rightChild->_left = this;
			this->_right = rightLeftChild;
			if (rightLeftChild)
				rightLeftChild->_parent = this;
			rightChild->_parent = this->_parent;
			this->_parent = rightChild;
			if (rightChild->_parent)
			{
				if (this == rightChild->_parent->_right)
					rightChild->_parent->_right = rightChild;
				else
					rightChild->_parent->_left = rightChild;
			}

			this->updateHeight();
			rightChild->updateHeight();
		}

		operator MapNode<Key, T>() const
		{
			return MapNode<Key, T>(this->_val);
		}

//		operator value_type() const
//		{
//			return (this->_val);
//		}

		operator ft::pair<Key, T>() const
		{
			return ft::pair<Key, T>(this->_val.first, this->_val.second);
		}

		MapNode&	operator=(const value_type& val)
		{
			this->_val = val;
			return (*this);
		}

		void abstr() {}

		bool	operator==(const MapNode<Key, T> &rhs) const
		{
			return (this->_val == rhs._val);
		}

		bool	operator!=(const MapNode<Key, T> &rhs) const
		{
			return (this->_val != rhs._val);
		}

		bool	operator<(const MapNode<Key, T> &rhs) const
		{
			return (this->_val < rhs._val);
		}

		bool	operator>(const MapNode<Key, T> &rhs) const
		{
			return (this->_val > rhs._val);
		}

		bool	operator<=(const MapNode<Key, T> &rhs) const
		{
			return (this->_val <= rhs._val);
		}

		bool	operator>=(const MapNode<Key, T> &rhs) const
		{
			return (this->_val >= rhs._val);
		}

		bool	operator==(const value_type &rhs) const	{ return (this->_val == rhs); }

		bool	operator!=(const value_type &rhs) const	{ return (this->_val != rhs); }

		bool	operator<(const value_type &rhs) const	{ return (this->_val < rhs); }

		bool	operator>(const value_type &rhs) const	{ return (this->_val > rhs); }

		bool	operator<=(const value_type &rhs) const	{ return (this->_val <= rhs); }

		bool	operator>=(const value_type &rhs) const	{ return (this->_val >= rhs); }

		template <class Key1, class T1>
		friend 	bool	operator==(const T1 &lhs, const MapNode<Key1, T1> &rhs);
		template <class Key1, class T1>
		friend 	bool	operator<(const T1 &lhs, const MapNode<Key1, T1> &rhs);

	};

	template <class Key, class T>
	bool	operator==(const ft::pair<Key, T> &lhs, const MapNode<Key, T> &rhs)	{ return (lhs == rhs._val); }

	template <class Key, class T>
	bool	operator!=(const ft::pair<Key, T> &lhs, const MapNode<Key, T> &rhs)	{ return !(lhs == rhs); }

	template <class Key, class T>
	bool	operator<(const ft::pair<Key, T> &lhs, const MapNode<Key, T> &rhs)	{ return (lhs < rhs._val); }

	template <class Key, class T>
	bool	operator>(const ft::pair<Key, T> &lhs, const MapNode<Key, T> &rhs)	{ return !(rhs > lhs); }

	template <class Key, class T>
	bool	operator<=(const ft::pair<Key, T> &lhs, const MapNode<Key, T> &rhs)	{ return !(rhs < lhs); }

	template <class Key, class T>
	bool	operator>=(const ft::pair<Key, T> &lhs, const MapNode<Key, T> &rhs)	{ return !(lhs < rhs); }

	template<class Key, class T>
	std::ostream& operator<<(std::ostream& os, const MapNode<Key, T> &node)
	{
		os << node._val << ":" << node._height;
		return (os);
	}

//	template<class Key, class T>
//	class SentinelMapNode : public MapNode<Key, T>
//	{
//	public:
//		typedef	MapNode<Key, T>		map_node;
//		typedef pair<const Key, T>	value_type;
//
//		map_node	*_first;
//		map_node	*_last;
//
//	};
}

#endif
