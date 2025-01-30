/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-28 16:17:22 by sternero          #+#    #+#             */
/*   Updated: 2025-01-28 16:17:22 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

using std::cout;
using std::endl;

ScavTrap::ScavTrap() : ClapTrap(){
	cout << "ScavTrap default constructor called." << endl;
}

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name){
	cout << "ScavTrap " << name << " has been created." << endl;
}

ScavTrap::ScavTrap(const ScavTrap& newScavTrap) : ClapTrap(newScavTrap){
	cout << "ScavTrap copy constructor called." << endl;
}

void ScavTrap::attack(const std::string& target){
	
	if (this->_energyPoints < 5){
		cout << "ScavTrap " << this->getName() << " has no energy points left." << endl;
		return;
	}

	else {
		this->_energyPoints -= 5;
		cout << "ScavTrap " << this->getName() << " attacks " << target << ","; 
		cout << " causing : " << this->_attackDamage << " points of damage!" << endl;
		cout << "\tNow " << this->getName() << " has " << this->_energyPoints << " energy points left.\n";
	}
}

void ScavTrap::guardGate() const{
	cout << "ScavTrap " << this->getName() << " has entered in Gate Keeper Mode." << endl;
}

ScavTrap::~ScavTrap(){
	cout << "ScavTrap " << this->getName() << " has been destroyed." << endl;
}