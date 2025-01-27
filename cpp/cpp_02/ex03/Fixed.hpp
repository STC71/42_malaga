/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-19 14:33:05 by sternero          #+#    #+#             */
/*   Updated: 2025-01-19 14:33:05 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once				// This is the same as #ifndef, #define, #endif

#include <iostream>
#include <cmath>

class Fixed {
	private:
		int 				value;
		static const int	fractBits = 8;
	public:
		Fixed(void);					// Default constructor
		Fixed(const Fixed& other);		// Copy constructor
		Fixed(const float val);			// Constructor with float parameter
		Fixed(const int val);			// Constructor with int parameter
		~Fixed(void);					// Destructor	

		/* 	The next functions are the operator overloads, used to compare,
			assign, and perform operations with the Fixed class. */
		
		Fixed&			operator=(const Fixed& other);
		bool			operator>(const Fixed& other) const;
		bool			operator<(const Fixed& other) const;
		bool			operator>=(const Fixed& other) const;
		bool			operator<=(const Fixed& other) const;
		bool			operator==(const Fixed& other) const;
		bool			operator!=(const Fixed& other) const;
		Fixed			operator+(const Fixed& other) const;
		Fixed			operator-(const Fixed& other) const;
		Fixed			operator*(const Fixed& other) const;
		Fixed			operator/(const Fixed& other) const;
		Fixed&			operator++(void);
		Fixed			operator++(int);
		Fixed&			operator--(void);
		Fixed			operator--(int);

		// -- The next functions are used to access and modify the methods -- //

		int 			getRawBits(void) const;		// Returns the raw bits of the object
		void			setRawBits(const int raw);	// Sets the raw bits of the object
		int 			toInt(void) const;			// Returns the integer value of the object
		float			toFloat(void) const;		// Returns the float value of the object

		// ---- The next functions are used to compare min and max values --- //

		static Fixed&		min(Fixed& x, Fixed& y);
		static Fixed&		max(Fixed& x, Fixed& y);
		static const Fixed&	min(const Fixed& x, const Fixed& y);
		static const Fixed&	max(const Fixed& x, const Fixed& y);

};

std::ostream&	operator<<(std::ostream& out, const Fixed& fixed);
// ostream& is used to overload the output stream operator to print the value of the object.
