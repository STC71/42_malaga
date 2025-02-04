/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 12:33:31 by sternero          #+#    #+#             */
/*   Updated: 2025-02-02 12:33:31 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICharacter.hpp"
#include "AMateria.hpp"

class Character : public ICharacter {

	public:

		Character(const std::string& _name);						// Default constructor
		Character(const Character& src);						// Copy constructor
		Character & operator=(const Character &src);			// Assignation operator
		~Character();											// Destructor
		const std::string& getName() const;						// Getter for name
		void equip(AMateria* m);								// Equip AMateria
		void unequip(int idx);									// Unequip AMateria
		void use(int idx, ICharacter& target);					// Use AMateria

	private:

		std::string _name;										// Name of Character
		AMateria* _inventory[4];								// Inventory of AMateria
		int _inventorySize;										// Size of inventory

};