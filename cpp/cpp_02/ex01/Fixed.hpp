/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-16 18:44:23 by sternero          #+#    #+#             */
/*   Updated: 2025-01-16 18:44:23 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <cstdlib>
#include <iostream>
#include <cmath>

class Fixed {
	public:

		Fixed(void);								// Default constructor
		Fixed(const int inInt);						// Parametric constructor
		Fixed(const float inFloat);			
		Fixed(const Fixed &to_copy);				// Copy constructor	
		Fixed &operator=(const Fixed &original);	// Assignation operator overload
		~Fixed(void);								// Destructor

		int getRawBits(void) const;					// Get the raw value of the fixed point value
		void setRawBits(int const raw);				// Set the raw value of the fixed point value

		float toFloat(void) const;					// Convert the fixed point value to a floating point value
		int toInt(void) const;						// Convert the fixed point value to an integer value

	private:
		int value;									// The raw value of the fixed point value
		static const int bits = 8;					// The number of fractional bits
};

std::ostream &operator<<(std::ostream &stream, const Fixed &nbr);	// Output stream operator overload

#endif