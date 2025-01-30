/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-29 12:09:49 by sternero          #+#    #+#             */
/*   Updated: 2025-01-29 12:09:49 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

using std::cout;
using std::endl;

DiamondTrap::DiamondTrap() : ClapTrap(), FragTrap(), ScavTrap(){
	cout << "DiamondTrap default constructor called." << endl;
	this-> _attackDamage = 30;
	this-> _energyPoints = 50;
	this-> _hitPoints = 100;
}

DiamondTrap::DiamondTrap(const std::string& name) 
	: ClapTrap(name + "_clone"), FragTrap(name + "_clone"), ScavTrap(name + "_clone"), _name(name) {
	cout << "DiamondTrap " << name << " has been created." << endl;
	this-> _attackDamage = 30;
	this-> _energyPoints = 50;
	this-> _hitPoints = 100;
}

DiamondTrap::DiamondTrap(const DiamondTrap& newDiamondTrap) 
	: ClapTrap(newDiamondTrap), FragTrap(newDiamondTrap), ScavTrap(newDiamondTrap) {
	cout << "DiamondTrap copy constructor called." << endl;
	this-> _name = newDiamondTrap._name;
	this-> _attackDamage = FragTrap::getAttackDamage();
	this-> _energyPoints = FragTrap::getEnergyPoints();
	this-> _hitPoints = FragTrap::getHitPoints();
}

void DiamondTrap::whoAmI(void) const{
	cout << "DiamondTrap " << this-> _name << " is also known as " << DiamondTrap::getName() << endl;
	cout << "DiamondTrap " << this-> _name << " is also known as " << ClapTrap::getName() << endl;
}

DiamondTrap::~DiamondTrap(){
	cout << "DiamondTrap " << this-> _name << " has been destroyed. 💥" << endl;
}