/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 12:37:25 by sternero          #+#    #+#             */
/*   Updated: 2025-02-02 12:37:25 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

using std::cout;
using std::endl;

MateriaSource::MateriaSource() : _materiasSize(0) {			// Default constructor
	for (int i = 0; i < 4; i++)								// Loop through array
		this->_materias[i] = NULL;							// Set each element to NULL
}

MateriaSource::MateriaSource(const MateriaSource &src) {	// Copy constructor
	*this = src;											// Assign src to this
}

MateriaSource& MateriaSource::operator=(const MateriaSource &src) {		// Assignation operator
		this->_materiasSize = src._materiasSize;						// Copy size
		for (int i = 0; i < 4; i++) {									// Loop through array
			if (this->_materias[i])										// If element is not NULL
				delete this->_materias[i];								// Delete element
			this->_materias[i] = src._materias[i];						// Clone src element
		}
	return *this;														// Return instance
}

MateriaSource::~MateriaSource() {									// Destructor
	for (int i = 0; i < 4; i++)										// Loop through array
		if (this->_materias[i])										// If element is not NULL
			delete this->_materias[i];								// Delete element
}

void MateriaSource::learnMateria(AMateria* m) {						// Learn AMateria
	if (this-> _materiasSize >= 4)									// If size is greater than 4
		cout << "Impossible to learn more than 4 materias" << endl;	// Print error message
	else {
		this->_materias[_materiasSize] = m;							// Set materia to array
		_materiasSize++;											// Increment size
	}
}

AMateria* MateriaSource::createMateria(const std::string& type) {	// Create AMateria
	for (int i = 0; i < 4 && this->_materias[i]; i++) {				// Loop through array
		if (type == this->_materias[i]->getType())					// If type is equal to type
			return this->_materias[i]->clone();						// Return clone of materia
	}
	return NULL;													// Return NULL
}

void MateriaSource::printMaterias() const {								// Print AMateria
	for (int i = 0; i < 4; i++)	{
		if (this->_materias[i])											// If element is not NULL
			cout << i << ": " << this->_materias[i]->getType() << endl;	// Print type
		else
			cout << i << " is empty" << endl;							// Print empty
	}
}