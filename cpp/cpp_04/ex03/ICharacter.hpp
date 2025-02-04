/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICharacter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 12:35:43 by sternero          #+#    #+#             */
/*   Updated: 2025-02-02 12:35:43 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include "AMateria.hpp"

class AMateria;

class ICharacter {

	public:

		virtual const std::string& getName() const = 0;			// Getter for name
		virtual void equip(AMateria* m) = 0;					// Equip AMateria
		virtual void unequip(int idx) = 0;						// Unequip AMateria
		virtual void use(int idx, ICharacter& target) = 0;		// Use AMateria
		virtual ~ICharacter() {}								// Destructor

};