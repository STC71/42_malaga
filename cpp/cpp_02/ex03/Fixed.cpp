/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-19 15:21:04 by sternero          #+#    #+#             */
/*   Updated: 2025-01-19 15:21:04 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

// ---- Constructors -------------------------------------------------------- //

Fixed::Fixed(){
	this->value = 0;					// Default constructor. Initializes to 0
}

Fixed::Fixed(const Fixed& other){
	*this = other; 								// Calls the operator overload
}

Fixed::Fixed(const float val){
	this->value = (int)roundf(val * (1 << Fixed::fractBits));	// Rounds the value
}

Fixed::Fixed(const int val){
	this->value = (val << Fixed::fractBits);	// Shifts the value to the left by fractBits
}

// ---- Destructor ---------------------------------------------------------- //

Fixed::~Fixed() {}								// Destructor to free the memory

// ---- Assignment Operator ------------------------------------------------- //

Fixed&	Fixed::operator=(const Fixed& other){
	this->setRawBits(other.getRawBits());
	return (*this);				// Returns the object itself after the assignment
}

bool	Fixed::operator>(const Fixed& other) const{
	return (this->getRawBits() > other.getRawBits());
}								
// Compares the raw bits of the objects to check if one is greater than the other

bool	Fixed::operator<(const Fixed& other) const{
	return (this->getRawBits() < other.getRawBits());
}
// Compares the raw bits of the objects to check if ...

bool	Fixed::operator>=(const Fixed& other) const{
	return (this->getRawBits() >= other.getRawBits());
}
// Compares the raw bits of the objects to check if ...

bool	Fixed::operator<=(const Fixed& other) const{
	return (this->getRawBits() <= other.getRawBits());
}
// Compares the raw bits of the objects to check if ...

bool	Fixed::operator==(const Fixed& other) const{
	return (this->getRawBits() == other.getRawBits());
}
// Compares the raw bits of the objects to check if ...

bool	Fixed::operator!=(const Fixed& other) const{
	return (this->getRawBits() != other.getRawBits());
}
// Compares the raw bits of the objects to check if ...

Fixed	Fixed::operator+(const Fixed& other) const{
	Fixed	result;
	result.setRawBits(this->getRawBits() + other.getRawBits());
	return (result);
}
// Adds the raw bits of the objects and returns the result

Fixed	Fixed::operator-(const Fixed& other) const{
	Fixed	result;
	result.setRawBits(this->getRawBits() - other.getRawBits());
	return (result);
}
// Subtracts the raw bits of the objects and returns the result

Fixed	Fixed::operator*(const Fixed& other) const{
	Fixed	result;
	result.setRawBits((this->getRawBits() * other.getRawBits()) >> Fixed::fractBits);
	return (result);
}
// Multiplies the raw bits of the objects and returns the result

Fixed	Fixed::operator/(const Fixed& other) const{
	if (other.getRawBits() == 0)
		throw std::logic_error("Division by zero!");
	return (Fixed(this->toFloat() / other.toFloat()));
}
// Split the raw bits of the objects and returns the result

Fixed&	Fixed::operator++(void){
	this->setRawBits(this->getRawBits() + 1);		// Preincrement
	return (*this);
}

Fixed	Fixed::operator++(int){
	Fixed	curr(*this);
	this->setRawBits(this->getRawBits() + 1);		// Postincrement
	return (curr);
}

Fixed&	Fixed::operator--(void){
	this->setRawBits(this->getRawBits() - 1);		// Pre-decrement
	return (*this);
}

Fixed	Fixed::operator--(int){
	Fixed	curr(*this);
	this->setRawBits(this->getRawBits() - 1);		// Post-decrement
	return (curr);
}

// ---- Output Stream Operator Overload ------------------------------------- //

std::ostream&	operator<<(std::ostream& out, const Fixed& fixed){
	out << fixed.toFloat();
	return (out);
}
// Overloads the output stream operator to print the value of the object.

// ---- Access and Modify Methods ------------------------------------------- //

int		Fixed::getRawBits() const{
	return (this->value);				// Returns the raw bits of the object
}

void	Fixed::setRawBits(const int raw){
	this->value = raw;					// Sets the raw bits of the object
}

int 	Fixed::toInt() const{
	return (this->value >> Fixed::fractBits);
}										// Returns the integer value of the object

float	Fixed::toFloat() const{
	return ((float)this->value / (float)(1 << Fixed::fractBits));
}										// Returns the float value of the object	

// ---- Functions to compare min and max values ----------------------------- //

Fixed&	Fixed::min(Fixed& x, Fixed& y){
	if (x < y)
		return (x);
	return (y);
}
/* 	Compares the raw bits of the objects to check which is the smallest.
	Fixed& is used to return the reference of the object. */

Fixed&	Fixed::max(Fixed& x, Fixed& y){
	if (x > y)
		return (x);
	return (y);
}

const Fixed&	Fixed::min(const Fixed& x, const Fixed& y){
	if (x < y)
		return (x);
	return (y);
} 
// const is used to 

const Fixed&	Fixed::max(const Fixed& x, const Fixed& y){
	if (x > y)
		return (x);
	return (y);
}
