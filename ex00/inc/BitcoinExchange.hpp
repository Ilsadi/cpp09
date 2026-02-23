/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:12:41 by ilsadi            #+#    #+#             */
/*   Updated: 2026/02/01 17:42:38 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <cstdlib>

class BitcoinExchange
{
	public:
		void	loadDatabase(std::string const &filename);
		void	processInput(std::string const &filename) const;
		double	getRateForDate(std::string const &date) const;

	private:
		std::map<std::string, double> _rates;
};