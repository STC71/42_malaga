/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-27 18:18:02 by sternero          #+#    #+#             */
/*   Updated: 2025-01-27 18:18:02 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

using std::endl;
using std::cin;
using std::cout;

// Constructor, Copy Constructor, Parameterized Constructor, and Destructor

ClapTrap::ClapTrap() {
	cout << "ClapTrap default constructor called" << endl;
	this-> _attackDamage = 0;
	this-> _energyPoints = 10;
	this-> _hitPoints = 10;
}	// make a default constructor to initialize the values

ClapTrap::ClapTrap(const ClapTrap& newClapTrap) {
	cout << "ClapTrap copy constructor called, and cloned " << newClapTrap.getName() << endl;
	*this = newClapTrap;
}	// make a copy constructor to clone the object passed as an argument

ClapTrap::ClapTrap(std::string name) {
	cout << "ClapTrap parameterized constructor called, and named: " << name << endl;
	this-> _name = name;
	this-> _attackDamage = 0;
	this-> _energyPoints = 10;
	this-> _hitPoints = 10;
}	// make a parameterized constructor to set the name of the object

ClapTrap::~ClapTrap() {
	cout << "ClapTrap destructor called, and destroyed: " << this->_name << endl;
}	// make a destructor to destroy the object

// Assignment Operator Overload

ClapTrap& ClapTrap::operator = (const ClapTrap& newClapTrap) {
	cout << "ClapTrap assignment operator called, and assigned: " << newClapTrap.getName() << endl;
	this-> setName(newClapTrap.getName());
	this-> setAttackDamage(newClapTrap.getAttackDamage());
	this-> setEnergyPoints(newClapTrap.getEnergyPoints());
	this-> setHitPoints(newClapTrap.getHitPoints());
	return *this;
}	// make an assignment operator overload to assign the values of the object passed as an argument

// Getters & Setters	

const std::string& ClapTrap::getName() const {
	return this-> _name;
}	// make a getter to get the name of the object

unsigned int ClapTrap::getHitPoints() const {
	return this-> _hitPoints;
}	// make a getter to get the hit points of the object

unsigned int ClapTrap::getEnergyPoints() const {
	return this-> _energyPoints;
}	// make a getter to get the energy points of the object

unsigned int ClapTrap::getAttackDamage() const {
	return this-> _attackDamage;
}	// make a getter to get the attack damage of the object

void ClapTrap::setName(const std::string& name) {
	this-> _name = name;
}	// make a setter to set the name of the object

void ClapTrap::setHitPoints(unsigned int hitPoints) {
	this-> _hitPoints = hitPoints;
}	// make a setter to set the hit points of the object

void ClapTrap::setEnergyPoints(unsigned int energyPoints) {
	this-> _energyPoints = energyPoints;
}	// make a setter to set the energy points of the object

void ClapTrap::setAttackDamage(unsigned int attackDamage) {
	this-> _attackDamage = attackDamage;
}	// make a setter to set the attack damage of the object

// Member Functions

void ClapTrap::attack(const std::string& target) {
	
	if (this-> _energyPoints < 2) {
		//cout << "ClapTrap " << this-> _name << " is out of energy points and cannot attack" << endl;
		cout << "ClapTrap " << this-> _name << " is trying to attack " << target << ", but is out of energy points!" << endl;
		return;
	}

	else if (this-> _hitPoints <= 0) {
		cout << "ClapTrap " << this-> _name << " is trying to attack " << target << ", but is out of hit points... is dead!" << endl;
		return;
	}

	else {
		cout << "ClapTrap " << this-> _name << " attacks " << target << ", causing " << this-> _attackDamage << " points of damage!" << endl;
		this-> _energyPoints -= 2;
	}
}	// make an attack method to attack the target

void ClapTrap::takeDamage(unsigned int amount) {
	
	if (amount > this-> _hitPoints) {
		cout << "ClapTrap " << this-> _name << " takes " << this-> _hitPoints << " points of damage!" << endl;
		this-> _hitPoints = 0;
	}

	else {
		cout << "ClapTrap " << this-> _name << " takes " << amount << " points of damage!" << endl;
		this-> _hitPoints -= amount;
	}
}	// make a take damage method to take damage from an attack

void ClapTrap::beRepaired(unsigned int amount) {
	
	this-> _hitPoints += amount;
	cout << "ClapTrap " << this-> _name << " is repaired for " << amount << " points!" << endl;
}	// make a be repaired method to repair the object