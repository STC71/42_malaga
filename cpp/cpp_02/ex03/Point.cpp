/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-19 14:34:53 by sternero          #+#    #+#             */
/*   Updated: 2025-01-19 14:34:53 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point(void) : x(Fixed(0)), y(Fixed(0)) { }	// Default constructor

Point::Point(const float x, const float y)
	: x(Fixed(x)), y(Fixed(y)) 
{ }

Point::Point(const Point& other) {
	*this = other;								// Calls the operator overload
}

Point::~Point() {}								// Destructor	

Point&	Point::operator=(const Point&){
	return (*this);								// Returns the object itself
}

const Fixed&	Point::getX(void) const{
	return (this->x);							// Returns the x value
}

const Fixed&	Point::getY(void) const{
	return (this->y);							// Returns the y value
}
