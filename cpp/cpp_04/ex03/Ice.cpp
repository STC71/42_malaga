/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 12:36:22 by sternero          #+#    #+#             */
/*   Updated: 2025-02-02 12:36:22 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

using std::cout;
using std::endl;

Ice::Ice() : AMateria("ice") {}							// Default constructor

Ice::Ice(const Ice &src) : AMateria("ice") {			// Copy constructor
	*this = src;
}

Ice & Ice::operator=(const Ice &src) {					// Assignation operator
	this->_type = src._type;							// Copy type
	return *this;
}

Ice::~Ice() {}											// Destructor

AMateria* Ice::clone() const {							// Clone AMateria
	return new Ice(*this);								// Return new Ice
}

void Ice::use(ICharacter& target) {											// Use AMateria
	cout << "* shoots an ice bolt at " << target.getName() << " *" << endl;	// Shoot ice bolt
}