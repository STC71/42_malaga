/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 15:54:09 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 15:54:09 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

using std::cout;
using std::endl;

Animal::Animal() {
	cout << "Animal default constructor called 🧑‍🔧" << endl;
}

Animal::Animal(const Animal& src) {
	cout << "Animal copy constructor called 🖨️" << endl;
	*this = src;
}

Animal::Animal(const std::string& type) : _type(type) {
	cout << "Animal type constructor called 🤖" << endl;
}

Animal::~Animal() {
	cout << "Animal destructor called 🔥" << endl;
}

Animal& Animal::operator=(const Animal& src) {
	cout << "Animal assignation operator called 🧮" << endl;
	if (this != &src)									// Prevent self-assignment
		this->_type = src._type;						// Copy data from src to this
	else
		cout << "Self-assignment detected 🧨" << endl;
	return *this;										// Return ref for multiple assignment
}

const std::string& Animal::getType() const {			// Getter for type of animal
	return _type;
}

void Animal::setType(const std::string& type) {			// Setter for type of animal
	this->_type = type;
}

void Animal::makeSound() const {						// Make sound
	cout << "Animal sound 🔊" << endl;
}