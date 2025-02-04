/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 18:38:19 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 18:38:19 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

using std::cout;
using std::endl;

Brain::Brain() {										// Default constructor
	cout << "Brain default constructor called 👨‍💻" << endl;	
}

Brain::Brain(const Brain& src) {						// Copy constructor to copy the data
	cout << "Brain copy constructor called 🙇" << endl;
	*this = src;										// Copy the data
}

Brain::~Brain() {										// Destructor
	cout << "Brain destructor called 🔫" << endl;
}

Brain& Brain::operator=(const Brain& src) {				// Assignment operator '='
	for (int i = 0; i < 100; i++)						// Loop through the data
		this->ideas[i] = src.ideas[i];					// Copy the data
	this->count = src.count;							// Copy the data
	return *this;										// Return the instance
}

const std::string& Brain::getIdea(unsigned int index) const {	// Get the data
	return this->ideas[index];									// Return the data
}

void Brain::addIdea(const std::string& idea) {		// Set the data
	if (count == 100) {								// Check if the data is full
		cout << "Brain is full 🧠" << endl;			// Output the message
		return;										// Return
	}
	this->ideas[count++] = idea;					// Set the data and increment the count
}