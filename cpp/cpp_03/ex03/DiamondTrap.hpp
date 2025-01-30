/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-29 12:09:32 by sternero          #+#    #+#             */
/*   Updated: 2025-01-29 12:09:32 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap {
	
	public:

		DiamondTrap();									// default constructor
		DiamondTrap(const std::string& name);			// parameterized constructor
		DiamondTrap(const DiamondTrap& newDiamondTrap);	// copy constructor
		~DiamondTrap();									// destructor

		using 	ClapTrap::operator =;					// using the operator = of the ClapTrap class
		using	ScavTrap::attack;						// using the attack method of the ScavTrap class
		void	whoAmI(void) const;						// who am I method

	private:

		std::string _name;								// name of the DiamondTrap object

};
