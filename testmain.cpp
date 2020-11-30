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

int	main(void)
{
	std::vector<int> vc;

	vc.push_back(5);
	std::cout << vc[1];
	return (0);
}