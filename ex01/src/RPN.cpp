/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 08:16:34 by ilsadi            #+#    #+#             */
/*   Updated: 2026/02/25 08:50:56 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static bool	isDigitToken(const std::string &tok)
{
	if (tok.size() != 1)
		return (false);
	if (tok[0] < '0' || tok[0] > '9')
		return (false);
	return (true);
}

static bool	isOperatorToken(const std::string &tok)
{
	if (tok.size() != 1)
		return (false);
	if (tok[0] == '*' || tok[0] == '+' || tok[0] == '-' || tok[0] == '/')
		return (true);
	return (false);
}

int RPN::evaluate(const std::string &str)
{
	std::stack<int, std::list<int> > st;
	std::istringstream iss(str);
	std::string tok;

	while (iss >> tok)
	{
		if (isDigitToken(tok))
		{
			int	value = tok[0] - '0';
			st.push(value);
		}
		else if (isOperatorToken(tok))
		{
			if (st.size() < 2)
				throw std::runtime_error("Error");
			int	b = st.top();
			st.pop();
			int	a = st.top();
			st.pop();
			if (tok[0] == '+')
				st.push(a + b);
			else if (tok[0] == '-')
				st.push(a - b);
			else if (tok[0] == '*')
				st.push(a * b);
			else if (tok[0] == '/')
			{
				if (b == 0)
					throw std::runtime_error("Error");
				st.push(a / b);
			}
		}
		else
			throw std::runtime_error("Error");
	}
	if (st.size() != 1)
		throw std::runtime_error("Error");
	return (st.top());
}