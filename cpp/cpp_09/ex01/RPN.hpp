/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 11:07:42 by sternero          #+#    #+#             */
/*   Updated: 2025-02-28 11:07:42 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>						// to use exception
#include <cstdlib>							// to use exit, EXIT_FAILURE, EXIT_SUCCESS
#include <iostream>							// to use cout, cin, cerr
#include <sstream>							// to use stringstream to convert string to double
#include <stack>							// to use stack container
#include <string>							// to use string

#define BLUE "\033[0;34m"					// blue color
#define GREEN "\033[0;32m"					// dark green color
#define PURPLE "\033[0;35m"					// purple color
#define RED "\033[0;31m"					// red color
#define RESET "\033[0m"						// reset color

#define ERROR_ARG "Invalid number of arguments."
#define ERROR_EXP "Invalid expression."
#define ERROR_MSG "Error:"

class RPN {

	public:

		RPN();										// default constructor
		RPN(const RPN &src);						// copy constructor
		RPN &operator=(const RPN &src);				// assignment operator
		~RPN();										// destructor

		static bool validExpression(const std::string &expr);	// check if the expression is valid
		static long long calculator(const std::string &expr);	// calculate the expression

		class invalidExpression : public std::exception {		// InvalidExpression class
			public:
				virtual const char *what() const throw();		// return the error message
		};

		class zeroDivision : public std::exception {			// ZeroDivision class
			public:
				virtual const char *what() const throw();		// return the error message
		};

};