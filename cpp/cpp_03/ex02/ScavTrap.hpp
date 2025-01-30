/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-28 16:16:59 by sternero          #+#    #+#             */
/*   Updated: 2025-01-28 16:16:59 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {		// ScavTrap class inherits from ClapTrap class

	public:

		ScavTrap();									// Default constructor
		ScavTrap(const std::string& name);			// Parameterized constructor
		ScavTrap(const ScavTrap& newScavTrap);		// Copy constructor
		~ScavTrap();								// Destructor

		using ClapTrap::operator =;		// Using the operator = from the ClapTrap class

		void attack(const std::string& target);		// Attack method
		void guardGate() const;						// Guard gate method

};
