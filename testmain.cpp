/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testmain.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 10:56:31 by jbennink      #+#    #+#                 */
/*   Updated: 2020/11/30 10:56:31 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "ft_vector.hpp"

int	main(void)
{
	std::vector<int> vc;
	ft::vector<int> ftvc;

	vc.push_back(5);
	ftvc.push_back(4);
	std::cout << vc[0];
//	std::cout << vc[1];
	return (0);
}