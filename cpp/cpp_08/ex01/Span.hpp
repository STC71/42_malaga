/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-23 11:28:31 by sternero          #+#    #+#             */
/*   Updated: 2025-02-23 11:28:31 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>							// std::sort std::min std::max...
#include <cmath>								// std::abs std::pow...
#include <exception>							// std::exception std::runtime_error...
#include <iostream>								// std::cout std::endl...
#include <stdexcept>							// std::out_of_range std::overflow_error...
#include <stdint.h>								// uint32_t uint64_t...
#include <vector>								// std::vector std::deque...

#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

class Span {

	public:

		Span(uint32_t n);											// Constructor
		Span(Span const &src);										// Copy constructor
		Span &operator=(Span const &src);							// Copy assignment operator
		~Span();													// Destructor

		void addNumber(int n);										// Add a number to the list
		void addNumbers(std::vector<int>::iterator begin, std::vector<int>::iterator end);	// Add a range of numbers to the list
		void addRamNumber(uint32_t amount);							// Add a random number to the list
		int shortestSpan();											// Return the shortest span between two numbers
		int longestSpan();											// Return the longest span between two numbers

		void printNumbers();										// Print the list of numbers

		class notEnoughNumbersException : public std::exception {
			public:
				const char *what() const throw();					// Exception for not enough numbers
		};															// Exception for not enough numbers

		class MaxSizeException : public std::exception {
			public:
				const char *what() const throw();					// Exception for max size reached
		};															// Exception for max size reached

	private:

		uint32_t _maxSize;											// Maximum size of the list
		std::vector<int> _numbers;									// List of numbers
		Span();														// Default constructor. Not implemented.

};
