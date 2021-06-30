#ifndef BIDIRECTIONALITERATOR_HPP
# define BIDIRECTIONALITERATOR_HPP
# include "../utils/type_traits.hpp"

namespace ft
{
	template <class T, class Pointer, class Reference,
	        class Category = ft::bidirectional_iterator_tag>
	class BidirectionalIterator {
	public:
		typedef	BidirectionalIterator<T, T*, T&>				this_type;
		typedef BidirectionalIterator<T, const T*, const T&>	const_type;
		typedef Category										iterator_category;
		typedef T												value_type;
		typedef ptrdiff_t										difference_type;
		typedef Pointer											pointer;
		typedef Reference										reference;

	protected:
		pointer _val;

	public:
		explicit BidirectionalIterator() : _val(NULL)
		{}

		explicit BidirectionalIterator(pointer val) : _val(val)
		{}

		BidirectionalIterator(const BidirectionalIterator<T, Pointer, Reference> &og)
		{
			*this = og;
		}

		virtual ~BidirectionalIterator() {}

		BidirectionalIterator &
		operator=(const BidirectionalIterator<T, Pointer, Reference> &x)
		{
			this->_val = x._val;
			return (*this);
		}

		reference operator*() const
		{
			return (*this->_val);
		}

		pointer operator->() const
		{
			return &(*this->_val);
		}

		BidirectionalIterator operator++(int)
		{
			BidirectionalIterator<T, Pointer, Reference> tmp(*this);
			this->_val++;
			return (tmp);
		}

		BidirectionalIterator operator--(int)
		{
			BidirectionalIterator<T, Pointer, Reference> tmp(*this);
			this->_val--;
			return (tmp);
		}

		virtual BidirectionalIterator &operator++()
		{
			this->_val++;
			return (*this);
		}

		virtual BidirectionalIterator &operator--()
		{
			this->_val--;
			return (*this);
		}

		bool operator==(BidirectionalIterator<T, Pointer, Reference> rhs)
		{
			return (this->_val == rhs._val);
		}

		bool operator!=(BidirectionalIterator<T, Pointer, Reference> rhs)
		{
			return !(*this == rhs);
		}

//		virtual operator BidirectionalIterator<T, const T*, const T&>() const
//		{
//			return BidirectionalIterator<T, const T*, const T&>(this->_val);
//		}

//		virtual operator BidirectionalIterator<T, T*, T&>() const
//		{
//			return BidirectionalIterator<T, T*, T&>(this->_val);
//		}

		template <class T1>
		friend bool operator==(BidirectionalIterator<T1, T1*, T1&> lhs, BidirectionalIterator<T1, T1*, T1&> rhs);

	};

	template <class T>
	bool operator==(BidirectionalIterator<T, T*, T&> lhs, BidirectionalIterator<T, T*, T&> rhs)
	{
		return (lhs._val == rhs._val);
	}

	template <class T>
	bool operator!=(BidirectionalIterator<T, T*, T&> lhs, BidirectionalIterator<T, T*, T&> rhs)
	{
		return !(lhs == rhs);
	}
}
#endif
//NodeIterator<[2 * ...], const ft::list<int, std::__1::allocator<int> >::node *, const ft::list<int, std::__1::allocator<int> >::node &>
//const NodeIterator<[2 * ...], ft::NodeIterator<int, ft::ListNode<int>, ft::ListNode<int> *, ft::ListNode<int> &, ft::bidirectional_iterator_tag>::node *, ft::NodeIterator<int, ft::ListNode<int>, ft::ListNode<int> *, ft::ListNode<int> &, ft::bidirectional_iterator_tag>::node &>