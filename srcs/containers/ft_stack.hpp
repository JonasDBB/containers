#ifndef STACK_HPP
# define STACK_HPP
# include <deque>

namespace ft
{
	template<class T, class Container = std::deque<T> >
	class stack {
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	private:
		container_type _c;

	public:
		explicit stack(const container_type &ctnr = container_type()) : _c(ctnr)
		{}

		bool empty() const					{ return (this->_c.empty()); }

		size_type size() const				{ return (this->_c.size()); }

		value_type &top()					{ return (this->_c.back()); }

		const value_type &top() const		{ return (this->_c.back()); }

		void push(const value_type &val)	{ this->_c.push_back(val); }

		void pop()							{ this->_c.pop_back(); }

		friend bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)	{ return (lhs._c == rhs._c); }
		friend bool operator<(const stack<T, Container>& lhs, const stack<T, Container>&  rhs)	{ return (lhs._c < rhs._c); }
	};

//	template<class T, class Container>
//	bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)	{ return (lhs._c == rhs._c); }

	template <class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)		{ return !(lhs == rhs); }

//	template <class T, class Container>
//	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)		{ return (lhs._c < rhs._c); }

	template <class T, class Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)		{ return !(rhs < lhs); }

	template <class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)		{ return (rhs < lhs); }

	template <class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)		{ return !(lhs < rhs); }
}
#endif
