/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 12:33:16 by sternero          #+#    #+#             */
/*   Updated: 2025-02-02 12:33:16 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

using std::cout;
using std::endl;

Character::Character(const std::string& _name) : _name(_name) {	// Default constructor
	for (int i = 0; i < 4; i++)
		this->_inventory[i] = NULL;
}

Character::Character(const Character& src) {					// Copy constructor
	*this = src;
}

Character& Character::operator=(const Character& src) {			// Assignation operator
	this->_name = src.getName();								// Copy name
	this->_inventorySize = 0;									// Reset inventory size
	for (int i = 0; i < 4; i++) {								// Copy inventory
		if (this->_inventory[i])
			delete this->_inventory[i];							// Delete AMateria
		this->_inventory[i] = src._inventory[i];				// Copy AMateria
		if (src._inventory[i])
			this->_inventorySize++;								// Increment inventory size
	}
	return *this;
}

Character::~Character() {										// Destructor
	for (int i = 0; i < 4; i++) {								// Delete inventory
		if (this->_inventory[i])
			delete this->_inventory[i];							// Delete AMateria
	}
}

const std::string& Character::getName() const {					// Getter for name
	return this->_name;
}

void Character::equip(AMateria* m) {							// Equip AMateria
	if (this-> _inventorySize < 4)								// Check if inventory is full
		this->_inventory[_inventorySize++] = m;					// Equip AMateria
	else
		cout << "Inventory is full. No more space in " << m->getType() << endl;	// Inventory is full
}

void Character::unequip(int idx) {								// Unequip AMateria
	if (idx >= 0 && idx < this->_inventorySize) {				// Check if index is valid
		idx++;
		for (int i = idx; i < this->_inventorySize; i++)		// Shift AMateria
			this->_inventory[i - 1] = this->_inventory[i];		// Shift AMateria
		this->_inventorySize--;									// Decrement inventory size
	}
}

void Character::use(int idx, ICharacter& target) {				// Use AMateria
	if (idx >= 0 && idx < this->_inventorySize)					// Check if index is valid
		this->_inventory[idx]->use(target);						// Use AMateria
}
