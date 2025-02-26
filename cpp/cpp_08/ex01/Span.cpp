/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-23 11:28:58 by sternero          #+#    #+#             */
/*   Updated: 2025-02-23 11:28:58 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

using std::cout; using std::endl;

Span::Span(uint32_t n) : _maxSize(n), _numbers() {};	// Constructor

Span::Span(const Span &src) {							// Copy constructor
	*this = src;										// Call the = operator
}

Span &Span::operator=(const Span &src) {				// Copy assignment operator
	this->_maxSize = src._maxSize;						// Copy the max size
	this->_numbers = src._numbers;						// Copy the list of numbers
	return *this;										// Return the instance of the object
}

void Span::addNumber(int n) {							// Add a number to the list
	if (this->_numbers.size() >= this->_maxSize)		// If the list is full
		throw Span::MaxSizeException();					// Throw an exception
	this->_numbers.push_back(n);						// Add the number to the list
}

void Span::addNumbers(std::vector<int>::iterator begin, std::vector<int>::iterator end) {	// Add a range of numbers to the list
	if (this->_numbers.size() + std::distance(begin, end) > this->_maxSize)	// If the list is full
		throw Span::MaxSizeException();					// Throw an exception
	this->_numbers.insert(this->_numbers.end(), begin, end);	// Add the range of numbers to the list
}

void Span::addRamNumber(uint32_t amount) {				// Add a random number to the list
	srand(time(NULL));									// Seed the random number generator
	try {												// Try to add the random numbers
		for (uint32_t i = 0; i < amount; i++)			// Loop through the amount of numbers
			this->addNumber(rand());					// Add a random number to the list
	} 	catch (std::exception &e) {						// Catch any exception
		cout << RED << e.what() << RESET << endl;		// Print the error message
	}
}

int	Span::shortestSpan() {								// Return the shortest span between two numbers
	std::vector<int> vec = this->_numbers;				// Copy the list of numbers
	if (vec.size() < 2)									// If there are less than 2 numbers
		throw Span::notEnoughNumbersException();		// Throw an exception
	std::sort(vec.begin(), vec.end());					// Sort the list of numbers
	int min = vec[1] - vec[0];							// Set the minimum to the difference between the first two numbers
	std::vector<int>::iterator it;						// Create an iterator
	for (it = vec.begin(); it != vec.end() - 1; it++) {	// Loop through the list of numbers
		if (abs(*(it + 1) - *it) < min)					// If the difference between the two numbers is less than the minimum
			min = abs(*(it + 1) - *it);					// Set the minimum to the difference
	}
	return min;											// Return the minimum
}

int	Span::longestSpan() {								// Return the longest span between two numbers
	std::vector<int> vec = this->_numbers;				// Copy the list of numbers
	if (vec.size() < 2)									// If there are less than 2 numbers
		throw Span::notEnoughNumbersException();			// Throw an exception
	int min = *std::min_element(vec.begin(), vec.end());	// Set the minimum to the smallest number
	int max = *std::max_element(vec.begin(), vec.end());	// Set the maximum to the largest number
	return max - min;									// Return the difference between the largest and smallest number
}

void Span::printNumbers() {								// Print the list of numbers
	std::vector<int> vec = this->_numbers;				// Copy the list of numbers
	std::vector<int>::iterator it;						// Create an iterator
	cout << "Numbers: ";								// Print the header
	for (it = vec.begin(); it != vec.end(); it++)		// Loop through the list of numbers
		cout << *it << " ";								// Print the number
	cout << endl;										// Print a newline
}

const char *Span::notEnoughNumbersException::what() const throw() {	// Exception for not enough numbers
	return "Not enough numbers in the list";			// Return the error message
}

const char *Span::MaxSizeException::what() const throw() {	// Exception for max size reached
	return "Max size reached";							// Return the error message
}
	
Span::~Span() {};										// Destructor