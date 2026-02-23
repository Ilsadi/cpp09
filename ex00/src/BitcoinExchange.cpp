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
static std::string trim(const std::string &s)
{
	size_t start = 0;
	while (start < s.size() && (s[start] == ' ' || s[start] == '\t'))
		start++;
	size_t end = s.size();
	while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'))
		end--;
	return s.substr(start, end - start);
}

static bool isNumber(const std::string &s)
{
	size_t i = 0;
	bool hasDigit = false;
	bool hasDot = false;

	if (s.empty())
		return (false);
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (; i < s.size(); i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
			hasDigit = true;
		else if (s[i] == '.')
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
		std::cout << "date=[" << date << "] valueStr=[" << valueStr << "] value=" << value << std::endl;
	}
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
