/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-29 10:30:18 by sternero          #+#    #+#             */
/*   Updated: 2025-01-29 10:30:18 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {			// FragTrap class inherits from ClapTrap class

	public:

		FragTrap();									// default constructor
		FragTrap(const std::string& name);			// parameterized constructor
		FragTrap(const FragTrap& newFragTrap);		// copy constructor
		~FragTrap();								// destructor

		using 	ClapTrap::operator =;				// using the operator = of the ClapTrap class
		void	highFivesGuys(void) const;			// high fives method

};