#ifndef FT_QUEUE_HPP
# define FT_QUEUE_HPP
# include <deque>

namespace ft
{
	template<class T, class Container = std::deque<T> >
	class queue {
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	protected:
		container_type _c;

	public:
		explicit queue(const container_type &ctnr = container_type()) : _c(ctnr)
		{}

		bool empty() const					{ return (this->_c.empty()); }

		size_type	size() const			{ return (this->_c.size()); }

		value_type	&front()				{ return (this->_c.front()); }

		const value_type &front() const		{ return (this->_c.front()); }

		value_type	&back()					{ return (this->_c.back()); }

		const value_type &back() const		{ return (this->_c.back()); }

		void push(const value_type &val)	{ this->_c.push_back(val); }

		void pop()							{ this->_c.pop_front(); }

		template<class T1, class Container1>
		friend bool	operator==(const queue<T1, Container1>& lhs, const queue<T1, Container1>& rhs);
		template<class T1, class Container1>
		friend bool operator<(const queue<T1, Container1>& lhs, const queue<T1, Container1>& rhs);
	};

	template<class T, class Container>
	bool	operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs)	{ return (lhs._c == rhs._c); }

	template <class T, class Container>
	bool operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)		{ return !(lhs == rhs); }

	template <class T, class Container>
	bool operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs)		{ return (lhs._c < rhs._c); }

	template <class T, class Container>
	bool operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)		{ return !(rhs < lhs); }

	template <class T, class Container>
	bool operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs)		{ return (rhs < lhs); }

	template <class T, class Container>
	bool operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)		{ return !(lhs < rhs); }
}

#endif
