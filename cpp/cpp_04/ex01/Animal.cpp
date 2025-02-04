/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 18:37:55 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 18:37:55 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

using std::cout;
using std::endl;

Animal::Animal() {										// Default constructor
	cout << "Animal default constructor called 👨‍💻" << endl;	
}

Animal::Animal(const std::string& type) {				// Constructor with parameter to set the data
	cout << "Type Animal constructor called 🙇‍♂️" << endl;
	this->type = type;
}

Animal::Animal(const Animal& src) {						// Copy constructor to copy the data
	cout << "Animal copy constructor called 🙇" << endl;
	*this = src;									// Copy the data
}

Animal::~Animal() {										// Destructor
	cout << "Animal destructor called 🔫" << endl;
}

Animal& Animal::operator=(const Animal& src) {			// Assignment operator '='
	cout << "Animal assignment operator called 🧮" << endl;
	this->type = src.getType();							// Copy the data
	return *this;										// Return the instance		
}

const std::string& Animal::getType() const {			// Get the data
	return this->type;									// Return the data
}

void Animal::setType(const std::string& type) {			// Set the data
	this->type = type;									// Set the data
}

void Animal::makeSound() const {						// Make a sound
	cout << "Animal sound 🐾" << endl;					// Output the sound
}

