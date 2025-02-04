/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 09:27:00 by sternero          #+#    #+#             */
/*   Updated: 2025-01-31 09:27:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

using std::cout;
using std::endl;

Dog::Dog() {
	cout << "Dog constructor called 🐶" << endl;
	this->_type = "Dog";
	this->_brain = new Brain;
}														// default constructor

Dog::Dog(const Dog& src) {
	cout << "Dog copy constructor called 🐕" << endl;
	*this = src;
}														// copy constructor

Dog& Dog::operator=(const Dog& src) {
	this->_type = src._type;						// copy the type
	*(this->_brain) = *(src._brain);				// copy the brain
	return *this;
}														// operator overload =

Animal& Dog::operator=(const Animal& src) {
	const Dog	*dogOther;
	dogOther = dynamic_cast<const Dog*>(&src);
	if (dogOther) {
		this->_type = dogOther->_type;					// copy the type
		*this->_brain = *dogOther->_brain;				// copy the brain
	}
	return *this;
}														// operator overload =

Brain *Dog::getBrain() const {
	return this->_brain;
}														// function to get the brain

void Dog::makeSound() const {
	cout << "Woof 🐶" << endl;
}														// function to make sound

Dog::~Dog() {
	cout << "Dog destructor called 🪓" << endl;
	delete this->_brain;
}														// destructor