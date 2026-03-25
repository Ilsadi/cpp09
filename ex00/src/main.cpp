/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:14:35 by ilsadi            #+#    #+#             */
/*   Updated: 2026/03/25 01:40:40 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: wrong number of arguments." << std::endl;
		return (1);
	}
	BitcoinExchange btc;
	btc.loadDatabase("data.csv");
	btc.processInput(av[1]);
	return (0);
}