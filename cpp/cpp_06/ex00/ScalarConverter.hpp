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
#include <iomanip>									// std::fixed, std::setprecision
#include <iostream>									// std::cout, std::endl
#include <limits>									// std::numeric_limits
#include <sstream>									// std::stringstresam
#include <string>									// std::string

class ScalarConverter {

	public:

		static void	convert(const std::string &input);

		/*	The function convert receives a string that contains a value to convert.
			It is able to convert the following data types: char, int, float and double.
			The function is static, so it is not necessary to instantiate an object of the
			ScalarConverter class in order to use it. It is static because it does not need
			to access any attribute of the class. */

};
