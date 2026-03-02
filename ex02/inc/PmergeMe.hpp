/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 08:17:33 by ilsadi            #+#    #+#             */
/*   Updated: 2026/03/02 09:50:22 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <climits>
#include <cstdlib>
#include <stdexcept>
#include <ctime>
#include <algorithm>
#include <utility>


class PmergeMe
{
	public:
		void	parse(int ac, char **av);
		void	printBefore() const;
		void	printAfter() const;
		void	sortVector();
		void	sortDeque();
		double	getTimeVecUs() const;
		double	getTimeDeqUs() const;
		std::size_t size() const;

	private:
		std::vector<int> _v;
		std::deque<int> _d;
		double	_timeVecUs;
		double	_timeDeqUs;
		bool isDigits(const std::string &str) const;
		int	toPositiveInt(const std::string &str) const;
		void fordJohnsonVector(std::vector<int>& v);
		void fordJohnsonDeque(std::deque<int> &v);
		std::vector<size_t> generateJacobsthal(size_t n);
};