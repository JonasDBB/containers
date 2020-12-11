/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   type_traits.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jonasbb <jonasbb@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 16:45:31 by jonasbb       #+#    #+#                 */
/*   Updated: 2020/12/11 16:45:31 by jonasbb       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

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
		static const bool result = false;
	};

	template <>
	struct is_iterator<ft::random_access_iterator_tag>
	{
		static const bool result = true;
	};

	template <>
	struct is_iterator<ft::bidirectional_iterator_tag>
	{
		static const bool result = true;
	};

}
#endif
