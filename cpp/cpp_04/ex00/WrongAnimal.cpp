/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 15:55:25 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 15:55:25 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

using std::cout;
using std::endl;

WrongAnimal::WrongAnimal() {
	cout << "WrongAnimal default constructor called 🧑‍🔧" << endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& src) {
	cout << "WrongAnimal copy constructor called 🖨️" << endl;
	*this = src;
}

WrongAnimal::WrongAnimal(const std::string& type) : _type(type) {
	cout << "WrongAnimal type constructor called 🤖" << endl;
}

WrongAnimal::~WrongAnimal() {
	cout << "WrongAnimal destructor called 🙀" << endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& src) {
	cout << "WrongAnimal assignation operator called 🧮" << endl;
	if (this != &src)										// Prevent self-assignment
		this->_type = src._type;							// Copy data from src to this
	else
		cout << "Self-assignment detected 🧨" << endl;
	return *this;											// Return ref for multiple assignment
}

const std::string& WrongAnimal::getType() const {			// Getter for type of animal
	return _type;
}

void WrongAnimal::setType(const std::string& type) {		// Setter for type of animal
	this->_type = type;
}

void WrongAnimal::makeSound() const {						// Make sound
	cout << "WrongAnimal sound 🐓" << endl;
}