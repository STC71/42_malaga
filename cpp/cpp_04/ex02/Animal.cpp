/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 09:25:42 by sternero          #+#    #+#             */
/*   Updated: 2025-01-31 09:25:42 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

using std::cout;
using std::endl;

const std::string& Animal::getType() const {
	return this->_type;
}													// const function to get the type

void Animal::setType(const std::string& _type) {
	this->_type = _type;
}													// function to set the type

Animal::~Animal() {
	cout << "Animal destructor called 🪓" << endl;
}													// virtual destructor

Animal& Animal::operator=(const Animal& src) {
	this->_type = src._type;						// copy the type
	return *this;
}													// virtual pure function to overload =