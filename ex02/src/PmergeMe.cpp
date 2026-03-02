/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 08:17:18 by ilsadi            #+#    #+#             */
/*   Updated: 2026/03/02 09:57:54 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

double PmergeMe::getTimeDeqUs() const
{
	return (_timeDeqUs);
}

double PmergeMe::getTimeVecUs() const
{
	return (_timeVecUs);
}

std::size_t PmergeMe::size() const
{
	return (_v.size());
}

bool PmergeMe::isDigits(const std::string &str) const
{
	if (str.empty())
		return (false);
	for (std::string::size_type i = 0; i < str.size(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
	}
	return (true);
}

int PmergeMe::toPositiveInt(const std::string &str) const
{
	if (isDigits(str) == false)
		throw std::runtime_error("Error");
	char *end;
	long val = std::strtol(str.c_str(), &end, 10);
	if (*end != '\0' || val <= 0 || val > INT_MAX)
		throw std::runtime_error("Error");
	return (static_cast<int>(val));
}


void PmergeMe::printBefore() const
{
	std::cout << "Before:";
	for (std::vector<int>::const_iterator it = _v.begin(); it != _v.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

void PmergeMe::printAfter() const
{
	std::cout << "After:";
	for (std::vector<int>::const_iterator it = _v.begin(); it != _v.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

void	PmergeMe::parse(int ac, char **av)
{
	_v.clear();
	_d.clear();
	for (int i = 1; i < ac; i++)
	{
		std::string s(av[i]);
		if (s.empty())
			continue;
		int x = toPositiveInt(s);
		_v.push_back(x);
		_d.push_back(x);
	}
}

std::vector<size_t> PmergeMe::generateJacobsthal(size_t n)
{
	std::vector<size_t> result;
	
	if (n == 0)
		return (result);
	size_t prev2 = 0;
	size_t prev1 = 1;
	while (prev1 <= n)
	{
		result.push_back(prev1);
		size_t current = prev1 + 2 * prev2;
		prev2 = prev1;
		prev1 = current;
	}
	return (result);
}


void	PmergeMe::fordJohnsonVector(std::vector<int> &v)
{
	if (v.size() <= 1)
		return;
	std::vector< std::pair<int, int> > pairs;
	for (std::vector<int>::size_type i = 0; i + 1 < v.size(); i += 2)
	{
		int a = v[i];
		int b = v[i + 1];
		if (a < b)
			pairs.push_back(std::pair<int, int>(a, b));
		else
			pairs.push_back(std::pair<int, int>(b, a));
	}
	bool hasStraggler = false;
	int straggler = 0;
	if (v.size() % 2 != 0)
	{
		hasStraggler = true;
		straggler = v[v.size() - 1];
	}
	std::vector<int> mainChain;
	std::vector<int> pend;
	for (std::vector< std::pair<int, int> >::size_type i = 0; i < pairs	.size(); i++)
	{
		mainChain.push_back(pairs[i].second);
		pend.push_back(pairs[i].first);
	}
	fordJohnsonVector(mainChain);
	std::vector<size_t> jac;
	if (pend.size() > 1)
		jac = generateJacobsthal(pend.size() - 1);
	std::vector<size_t> order;
	std::vector<bool> inserted(pend.size(), false);
	order.push_back(0);
	inserted[0] = true;
	for (size_t k = 0; k < jac.size(); k++)
	{
		size_t high = jac[k];
		size_t low = (k == 0) ? 1 : jac[k - 1] + 1;
		for (size_t idx = high; idx >= low && idx < pend.size(); idx--)
		{
			if (!inserted[idx])
			{
				order.push_back(idx);
				inserted[idx] = true;
			}
		}
	}
	for (size_t i = 0; i < pend.size(); i++)
	if (!inserted[i])
		order.push_back(i);
	v = mainChain;
	for (size_t k = 0; k < order.size(); k++)
	{
		size_t idx = order[k];
		int val = pend[idx];
		int maxAssociated = pairs[idx].second;
		std::vector<int>::iterator bound = std::upper_bound(v.begin(), v.end(), maxAssociated);
		std::vector<int>::iterator pos = std::lower_bound(v.begin(), bound, val);
		v.insert(pos, val);
	}
	if (hasStraggler)
	{
		std::vector<int>::iterator pos = std::lower_bound(v.begin(), v.end(), straggler);
		v.insert(pos, straggler);
	}
}

void	PmergeMe::fordJohnsonDeque(std::deque<int> &v)
{
	if (v.size() <= 1)
		return;
	std::deque< std::pair<int, int> > pairs;
	for (std::deque<int>::size_type i = 0; i + 1 < v.size(); i += 2)
	{
		int a = v[i];
		int b = v[i + 1];
		if (a < b)
			pairs.push_back(std::pair<int, int>(a, b));
		else
			pairs.push_back(std::pair<int, int>(b, a));
	}
	bool hasStraggler = false;
	int straggler = 0;
	if (v.size() % 2 != 0)
	{
		hasStraggler = true;
		straggler = v[v.size() - 1];
	}
	std::deque<int> mainChain;
	std::deque<int> pend;
	for (std::deque< std::pair<int, int> >::size_type i = 0; i < pairs	.size(); i++)
	{
		mainChain.push_back(pairs[i].second);
		pend.push_back(pairs[i].first);
	}
	fordJohnsonDeque(mainChain);
	std::vector<size_t> jac;
	if (pend.size() > 1)
		jac = generateJacobsthal(pend.size() - 1);
	std::vector<size_t> order;
	std::vector<bool> inserted(pend.size(), false);
	order.push_back(0);
	inserted[0] = true;
	for (size_t k = 0; k < jac.size(); k++)
	{
		size_t high = jac[k];
		size_t low = (k == 0) ? 1 : jac[k - 1] + 1;
		for (size_t idx = high; idx >= low && idx < pend.size(); idx--)
		{
			if (!inserted[idx])
			{
				order.push_back(idx);
				inserted[idx] = true;
			}
		}
	}
	for (size_t i = 0; i < pend.size(); i++)
	if (!inserted[i])
		order.push_back(i);
	v = mainChain;
	for (size_t k = 0; k < order.size(); k++)
	{
		size_t idx = order[k];
		int val = pend[idx];
		int maxAssociated = pairs[idx].second;
		std::deque<int>::iterator bound = std::upper_bound(v.begin(), v.end(), maxAssociated);
		std::deque<int>::iterator pos = std::lower_bound(v.begin(), bound, val);
		v.insert(pos, val);
	}
	if (hasStraggler)
	{
		std::deque<int>::iterator pos = std::lower_bound(v.begin(), v.end(), straggler);
		v.insert(pos, straggler);
	}
}

void	PmergeMe::sortVector()
{
	clock_t start = std::clock();
	fordJohnsonVector(_v);
	clock_t end = std::clock();
	_timeVecUs = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
}

void	PmergeMe::sortDeque()
{
	clock_t start = std::clock();
	fordJohnsonDeque(_d);
	clock_t end = std::clock();
	_timeDeqUs = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
}

