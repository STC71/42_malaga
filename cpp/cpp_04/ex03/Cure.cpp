/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 12:33:49 by sternero          #+#    #+#             */
/*   Updated: 2025-02-02 12:33:49 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

using std::cout;
using std::endl;

Cure::Cure() : AMateria("cure") {}							// Default constructor

Cure::Cure(const Cure &src) : AMateria("cure") {			// Copy constructor
	*this = src;
}

Cure & Cure::operator=(const Cure &src) {					// Assignation operator
	this->_type = src._type;								// Copy type
	return *this;
}

Cure::~Cure() {}											// Destructor

AMateria* Cure::clone() const {								// Clone AMateria
	return new Cure(*this);									// Return new Cure
}

void Cure::use(ICharacter& target) {									// Use AMateria
	cout << "* heals " << target.getName() << "’s wounds *" << endl;	// Heal target
}