/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-19 14:33:19 by sternero          #+#    #+#             */
/*   Updated: 2025-01-19 14:33:19 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once					// This is the same as #ifndef, #define, #endif

#include "Fixed.hpp"

class Point {
	private:
		const Fixed	x;					// x value to the position in the plane
		const Fixed	y;					// y value to the position in the plane
	public:
		Point(void);								// Default constructor
		Point(const Point&);						// Copy constructor
		Point(const float x, const float y);		// Constructor with parameters
		~Point();									// Destructor

		Point&	operator=(const Point& other);		// Assignment operator

		const Fixed&	getX(void) const;		// Get the x value
		const Fixed&	getY(void) const;		// Get the y value
};
