/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 18:38:48 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 18:38:48 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

using std::cout;
using std::endl;

Cat::Cat() : Animal("Cat") {								// Default constructor
	cout << this->type << " default constructor called 👨‍💻" << endl;
	this->brain = new Brain();							// Create a new brain
}

Cat::Cat(const Cat& src) : Animal(src) {					// Copy constructor to copy the data
	cout << this->type << " copy constructor called 🙇" << endl;
	this->brain = new Brain(*src.brain);					// Create a new brain and copy the data
}

Cat::~Cat() {											// Destructor
	cout << this->type << " destructor called 🔫" << endl;
	delete this->brain;									// Delete the brain
}

Animal& Cat::operator=(const Animal& src) {				// Assignment operator '='
	const Cat *srcOther;
	srcOther = dynamic_cast < const Cat *> (&src);		// Cast the source to Cat
	if (srcOther) {										// Check if the cast is successful
		this->type = srcOther->getType();				// Copy the data of the type
		*this->brain = *srcOther->brain;				// Copy the data of the brain to the new brain
	}
	return *this;										// Return the instance
}

void Cat::makeSound() const {							// Make a sound
	cout << "Meow 🐱" << endl;							// Output the sound
}

Brain *Cat::getBrain() const {							// Get the brain
	return this->brain;									// Return the brain
}
