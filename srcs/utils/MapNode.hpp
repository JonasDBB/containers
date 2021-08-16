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
		Key&	first;
		T&		second;
		MapNode *_begin;
		MapNode *_end;

		MapNode() : A_type(value_type()), _parent(NULL), _left(NULL), _right(NULL), _height(1), first(this->_val.first), second(this->_val.second),
		_begin(NULL), _end(NULL)
		{}

		explicit MapNode(const value_type& val) : A_type(val),
		_parent(NULL), _left(NULL), _right(NULL), _height(1), first(this->_val.first), second(this->_val.second),
		_begin(NULL), _end(NULL)
		{
		}

		MapNode(const MapNode& x) : first(x.first), second(x.second)
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

		virtual MapNode*	previous() const
		{
			MapNode* ret;

			if (this == this->_end)
			{
				ret = this->_parent;
				while (ret->_right)
					ret = ret->_right;
				return (ret);
			}
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
						return (this->_begin);
					return (ret->_parent);
				}
			}
		}

		virtual MapNode*	next() const
		{
			MapNode* ret;

			if (this == this->_begin)
			{
				ret = this->_parent;
				while (ret->_left)
					ret = ret->_left;
				return (ret);
			}
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
					while (ret->_parent && ret == ret->_parent->_right)
						ret = ret->_parent;
					if (!ret->_parent)
						return (this->_end);
					return (ret->_parent);
				}
			}
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

		operator ft::pair<key_type, mapped_type>() const
		{
			return (ft::make_pair(this->first, this->second));
		}

//		operator MapNode<Key, T>() const
//		{
//			return MapNode<Key, T>(this->_val);
//		}

//		operator ft::pair<Key, T>() const
//		{
//			return ft::pair<Key, T>(this->_val.first, this->_val.second);
//		}

//		operator const ft::pair<const Key, T>() const
//		{
//			return ft::pair<Key, T>(this->_val.first, this->_val.second);
//		}

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
}

#endif
