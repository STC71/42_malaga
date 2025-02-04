/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 15:54:51 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 15:54:51 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

using std::cout;
using std::endl;

Cat::Cat() : Animal("Cat") {
	cout << this->_type << " default constructor called 🐈" << endl; 
}

Cat::Cat(const Cat&) : Animal("Cat") {
	cout << this->_type << " copy constructor called 🐱" << endl;
}

void Cat::makeSound() const {
	cout << this->_type << " does: Meow meow 🔊" << endl;
}

Cat::~Cat() {
	cout << this->_type << " destructor called 🐍" << endl;
}