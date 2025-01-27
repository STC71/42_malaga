/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-18 13:10:20 by sternero          #+#    #+#             */
/*   Updated: 2025-01-18 13:10:20 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : _value(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed() {
	std::cout << "Destructor Called" << std::endl;
}

Fixed::Fixed(const Fixed &src) {
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

Fixed	&Fixed::operator = (const Fixed &src_2) {
	std::cout << "Assignation operator called" << std::endl;
	_value = src_2.getRawBits();
	return *this;
}

int		Fixed::getRawBits(void) const {
	return _value;
}												// Returns the raw value of the fixed point value

void	Fixed::setRawBits(int const raw) {
	this->_value = raw;
}												// Sets the raw value of the fixed point value	

Fixed::Fixed(const int val_int) {
	std::cout << "Int constructor called" << std::endl;
	this-> setRawBits(val_int << Fixed::_fractional_bits);
}

Fixed::Fixed(const float val_float) {
	std::cout << "Float constructor called" << std::endl;
	this->setRawBits(roundf(val_float * (1 << Fixed::_fractional_bits)));
}

float	Fixed::toFloat(void) const {
	return ((float) this -> _value / (float) (1 << Fixed::_fractional_bits));
}												// Returns the floating point value of the fixed point value

int		Fixed::toInt(void) const {
	return (this -> _value >> Fixed::_fractional_bits);
}												// Returns the integer value of the fixed point value

std::ostream &operator << (std::ostream &out, Fixed const &src) {
	out << src.toFloat();
	return out;
}												// Allows to output Fixed values

bool	Fixed::operator >= (Fixed const &src) const {
	if (this -> _value >= src.getRawBits())
		return true;
	return false;
}												// Comparison operator >

bool	Fixed::operator <= (Fixed const &src) const {
	if (this -> _value <= src.getRawBits())
		return true;
	return false;
}												// Comparison operator <

bool	Fixed::operator == (Fixed const &src) const {
	if (this -> _value == src.getRawBits())
		return true;
	return false;
}												// Comparison operator >=

bool	Fixed::operator != (Fixed const &src) const {
	if (this -> _value != src.getRawBits())
		return true;
	return false;
}												// Comparison operator <=

Fixed	Fixed::operator + (Fixed const &src) {
	this -> _value += src.getRawBits();
	return *this;
}												// Arithmetic operator +

Fixed	Fixed::operator - (Fixed const &src) {
	this -> _value -= src.getRawBits();
	return *this;
}												// Arithmetic operator -

Fixed	Fixed::operator * (Fixed const &src) {
	this -> _value = (this -> _value * src.getRawBits()) >> Fixed::_fractional_bits;
	return *this;
}												// Arithmetic operator *

Fixed	Fixed::operator / (Fixed const &src) {
	this -> _value = (this -> _value << Fixed::_fractional_bits) / src.getRawBits();
	return *this;
}												// Arithmetic operator /

Fixed	Fixed::operator ++ () {
	this -> _value++;
	return *this;
}												// Pre-increment operator

Fixed	Fixed::operator ++ (int) {
	Fixed tmp(*this);
	++(*this);
	return tmp;
}												// Post-increment operator

Fixed	Fixed::operator -- () {
	this -> _value--;
	return *this;
}												// Pre-decrement operator

Fixed	Fixed::operator -- (int) {
	Fixed tmp(*this);
	--(*this);
	return tmp;
}												// Post-decrement operator

Fixed const &Fixed::min(Fixed const &a, Fixed const &b) {
	if (a.getRawBits() > b.getRawBits())
		return b;
	return a;
}												// Returns the min of a and b

Fixed const &Fixed::max(Fixed const &a, Fixed const &b) {
	if (a.getRawBits() < b.getRawBits())
		return b;
	return a;
}												// Returns the max of a and b

Fixed &Fixed::min(Fixed &a, Fixed &b) {
	if (a.getRawBits() > b.getRawBits())
		return b;
	return a;
}												// Returns the min of a and b

Fixed &Fixed::max(Fixed &a, Fixed &b) {
	if (a.getRawBits() < b.getRawBits())
		return b;
	return a;
}												// Returns the max of a and b
