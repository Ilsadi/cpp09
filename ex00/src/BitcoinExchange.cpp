/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:24:48 by ilsadi            #+#    #+#             */
/*   Updated: 2026/02/19 16:06:14 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void BitcoinExchange::loadDatabase(std::string const &filename)
{
	std::ifstream file(filename.c_str());
	std::string line;

	if (!file)
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return ;
	}
	std::getline(file, line);

	while (std::getline(file, line))
	{
		size_t pos = line.find(',');
		if (pos == std::string::npos)
			continue;
		std::string date = line.substr(0, pos);
		std::string rateStr = line.substr(pos + 1);
		double rate = std::atof(rateStr.c_str());
		_rates[date] = rate;
	}
}
static std::string trim(const std::string &str)
{
	size_t start = 0;
	while (start < str.size() && (str[start] == ' ' || str[start] == '\t'))
		start++;
	size_t end = str.size();
	while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t'))
		end--;
	return str.substr(start, end - start);
}

static bool isNumber(const std::string &str)
{
	size_t i = 0;
	bool hasDigit = false;
	bool hasDot = false;

	if (str.empty())
		return (false);
	if (str[i] == '+' || str[i] == '-')
		i++;
	for (; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			hasDigit = true;
		else if (str[i] == '.')
		{
			if (hasDot)
				return (false);
			hasDot = true;
		}
		else
			return (false);
	}
	return (hasDigit);
}

double BitcoinExchange::getRateForDate(std::string const &date) const
{
	std::map<std::string, double>::const_iterator it = _rates.lower_bound(date);
	
	if (it != _rates.end() && it->first == date)
		return (it->second);
	if (it == _rates.begin())
		return (-1.0);
	--it;
	return (it->second);
}

static bool	isValidDate(const std::string &date)
{
	if (date.size() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	for (size_t i = 0; i < date.size(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (date[i] < '0' || date[i] > '9')
			return (false);
	}
	return (true);
}

void BitcoinExchange::processInput(std::string const &filename) const
{
	std::ifstream file(filename.c_str());
	std::string line;

	if (!file)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return ;
	}
	std::getline(file, line);
	while (std::getline(file, line))
	{
		
		size_t pos = line.find(" | ");
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::string date = line.substr(0, pos);
		std::string valueStr = line.substr(pos + 3);
		date = trim(date);
		valueStr = trim(valueStr);
		if (!isNumber(valueStr))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		double value = ::atof(valueStr.c_str());
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}
		double rate = getRateForDate(date);
		if (rate < 0)
		{
			std::cerr << "Error: no data available for this date." << std::endl;
			continue;
		}
		std::cout << date << " => " << value << " = " << value * rate << std::endl;
	}
}

