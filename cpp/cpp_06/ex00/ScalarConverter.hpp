/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-16 15:31:34 by sternero          #+#    #+#             */
/*   Updated: 2025-02-16 15:31:34 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ScalarConverter.hpp"						// ScalarConverter
#include <cerrno>									// errno to check for errors
#include <cmath>									// std::isnan to check for NaN (Not a Number)
#include <cstdlib>									// std::strtod, std::strtoll, std::strtoull
#include <iomanip>									// std::fixed, std::setprecision
#include <iostream>									// std::cout, std::endl
#include <limits>									// std::numeric_limits
#include <sstream>									// std::stringstresam
#include <string>									// std::string

#define BLUE "\033[1;34m"							// BLUE
#define GREEN "\033[0;32m"							// DARK GREEN
#define RED "\033[1;31m"							// RED
#define RESET "\033[0m"								// RESET

class ScalarConverter {

	public:

		static void	convert(const std::string &input);

		/*	The function convert receives a string that contains a value to convert.
			It is able to convert the following data types: char, int, float and double.
			The function is static, so it is not necessary to instantiate an object of the
			ScalarConverter class in order to use it. It is static because it does not need
			to access any attribute of the class. */

	private:

		ScalarConverter();								// Constructor
		~ScalarConverter();								// Destructor
		ScalarConverter(const ScalarConverter &);		// Copy constructor
		ScalarConverter &operator=(const ScalarConverter &);	// Assignment operator

};
