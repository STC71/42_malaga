/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 18:38:56 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 18:38:56 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

using std::cout;
using std::endl;

Dog::Dog() : Animal("Dog") {								// Default constructor
	cout << this->type << " default constructor called 👨‍💻" << endl;
	this->brain = new Brain();								// Create a new brain
}

Dog::Dog(const Dog& src) : Animal(src) {					// Copy constructor to copy the data
	cout << this->type << " copy constructor called 🙇" << endl;
	this->brain = new Brain(*src.brain);					// Create a new brain and copy the data
}

Dog::~Dog() {											// Destructor
	cout << this->type << " destructor called 🔫" << endl;
	delete this->brain;									// Delete the brain
}

Animal& Dog::operator=(const Animal& src) {				// Assignment operator '='
	const Dog *srcOther;
	srcOther = dynamic_cast < const Dog *> (&src);		// Cast the source to Dog
	if (srcOther) {										// Check if the cast is successful
		this->type = srcOther->getType();				// Copy the data of the type
		*this->brain = *srcOther->brain;				// Copy the data of the brain to the new brain
	}
	return *this;										// Return the instance
}

void Dog::makeSound() const {							// Make a sound
	cout << "Woof 🐶" << endl;							// Output the sound
}

Brain *Dog::getBrain() const {							// Get the brain
	return this->brain;									// Return the brain
}
