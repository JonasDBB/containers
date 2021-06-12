#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP
# include <cstddef>

namespace ft
{
	struct input_iterator_tag {};

	struct output_iterator_tag {};

	struct forward_iterator_tag : public input_iterator_tag {};

	struct bidirectional_iterator_tag : public forward_iterator_tag {};

	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<bool value, typename T = void>
	struct enable_if {};

	template<typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <typename T>
	struct is_iterator
	{
	private:
		typedef char	true_type;
		typedef int		false_type;

		template <typename U>
		static true_type test(typename U::iterator_category* = 0);
		template <typename U>
		static false_type test(...);

	public:
		static const bool result = (sizeof(true_type) == sizeof(test<T>(0)));
	};

	template <typename T>
	struct iterator_traits : public enable_if<is_iterator<T>::result, T>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef bidirectional_iterator_tag	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef bidirectional_iterator_tag	iterator_category;

		typedef bidirectional_iterator_tag	type;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef bidirectional_iterator_tag	iterator_category;

		typedef random_access_iterator_tag	type;
	};



}
#endif
