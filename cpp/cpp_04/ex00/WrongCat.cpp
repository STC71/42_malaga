/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 15:55:38 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 15:55:38 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

using std::cout;
using std::endl;

WrongCat::WrongCat() : WrongAnimal("WrongCat") {
	cout << this->_type << " default constructor called 🐅" << endl; 
}

WrongCat::WrongCat(const WrongCat&) : WrongAnimal("WrongCat") {
	cout << this->_type << " copy constructor called 🐯" << endl;
}

void WrongCat::makeSound() const {
	cout << this->_type << " does: Meow meow 🐣" << endl;
}

WrongCat::~WrongCat() {
	cout << this->_type << " destructor called 🪓" << endl;
}