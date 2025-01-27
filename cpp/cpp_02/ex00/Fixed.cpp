/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-16 14:36:23 by sternero          #+#    #+#             */
/*   Updated: 2025-01-16 14:36:23 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : _rawBits(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &fix1) {
	std::cout << "Copy constructor called" << std::endl;
	this->setRawBits(fix1.getRawBits());
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

Fixed	&Fixed::operator=(const Fixed &fix2) {
	std::cout << "Copy assignation operator called" << std::endl;
	this->setRawBits(fix2.getRawBits());
	return *this;
}

int		Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << std::endl;
	return _rawBits;
}

void	Fixed::setRawBits(int const raw) {
	this->_rawBits = raw;
}
