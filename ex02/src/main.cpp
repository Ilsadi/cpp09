/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 08:17:47 by ilsadi            #+#    #+#             */
/*   Updated: 2026/02/28 09:15:06 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	PmergeMe pm;
	try
	{
		pm.parse(ac, av);
		pm.printBefore();
		pm.sortVector();
		pm.sortDeque();
		pm.printAfter();
		std::cout << "Time to process a range of "
			<< pm.size()
			<< " elements with std::vector : "
			<< pm.getTimeVecUs()
			<< " us" << std::endl;

		std::cout << "Time to process a range of "
			<< pm.size()
			<< " elements with std::deque : "
			<< pm.getTimeDeqUs()
			<< " us" << std::endl;
	}
	catch (...)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	return (0);
}