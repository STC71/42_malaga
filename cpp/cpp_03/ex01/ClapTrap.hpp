/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-27 18:17:40 by sternero          #+#    #+#             */
/*   Updated: 2025-01-27 18:17:40 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

class ClapTrap{

	public:

		ClapTrap();								// Default constructor
		ClapTrap(const ClapTrap& newClapTrap);	// Copy constructor
		ClapTrap(std::string name);				// Parameterized constructor
		~ClapTrap();							// Destructor

		ClapTrap& operator = (const ClapTrap& newClapTrap);	// Assignment operator

		const std::string& getName() const;			// Get the name of the ClapTrap

		void attack(const std::string& target);				// Attack method
		void beRepaired(unsigned int amount);				// Be repaired method
		void takeDamage(unsigned int amount);				// Take damage method
		void setAttackDamage(unsigned int attackDamage);	// Set the attack damage of the ClapTrap
		void setEnergyPoints(unsigned int energyPoints);	// Set the energy points of the ClapTrap
		void setHitPoints(unsigned int hitPoints);			// Set the hit points of the ClapTrap
		void setName(const std::string& name);				// Set the name of the ClapTrap

		unsigned int getHitPoints() const;			// Get the hit points of the ClapTrap
		unsigned int getEnergyPoints() const;		// Get the energy points of the ClapTrap
		unsigned int getAttackDamage() const;		// Get the attack damage of the ClapTrap

	protected:							/* Protected members can be accessed by derived classes 
										   (classes that inherit from this class) but not by other
										   users of the class. Them are usually used to store data 
										   that should not be changed from outside the class.	*/

		std::string _name;						// Name of the ClapTrap

		unsigned int _attackDamage;				// Attack damage of the ClapTrap
		unsigned int _energyPoints;				// Energy points of the ClapTrap
		unsigned int _hitPoints;				// Hit points of the ClapTrap

};