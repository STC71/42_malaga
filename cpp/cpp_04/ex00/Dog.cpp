/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 15:55:09 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 15:55:09 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

using std::cout;
using std::endl;

Dog::Dog() : Animal("Dog") {
	cout << this->_type << " default constructor called 🐕" << endl;
}

Dog::Dog(const Dog&) : Animal("Dog") {
	cout << this->_type << " copy constructor called 🐶‍" << endl;
}

void Dog::makeSound() const {
	cout << this->_type << " does: Woof woof 🔊" << endl;
}

Dog::~Dog() {
	cout << this->_type << " destructor called 🦖" << endl;
}
