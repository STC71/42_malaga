/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 09:26:33 by sternero          #+#    #+#             */
/*   Updated: 2025-01-31 09:26:33 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

using std::cout;
using std::endl;

Cat::Cat() {
	cout << "Cat constructor called 🐱" << endl;
	this->_type = "Cat";
	this->_brain = new Brain;
}														// default constructor

Cat::Cat(const Cat& src) {
	cout << "Cat copy constructor called of: " << this->_type << endl;
	this->_type = src._type;							// copy the type
}														// copy constructor

Cat& Cat::operator=(const Cat& src) {
		this->_type = src._type;						// copy the type
		*(this->_brain) = *(src._brain);				// copy the brain
	return *this;
}														// operator overload =

Animal& Cat::operator=(const Animal& src) {
	const Cat	*catOther;
	catOther = dynamic_cast<const Cat *>(&src);
	if (catOther) {
		this->_type = catOther->_type;					// copy the type
		*this->_brain = *catOther->_brain;				// copy the brain
	}
	return *this;
}														// operator overload =

Brain *Cat::getBrain() const {
	return this->_brain;
}														// function to get the brain

void Cat::makeSound() const {
	cout << "Meow 🐱" << endl;
}														// function to make sound

Cat::~Cat() {
	cout << this->_type << " has been destroyed 🪓" << endl;
	delete this->_brain;
}														// destructor
