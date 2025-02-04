/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 18:38:28 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 18:38:28 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

class Brain {

	public:

		Brain();								// Default constructor
		Brain(const Brain& src);				// Copy constructor
		~Brain();								// Destructor

		Brain& operator=(const Brain& src);		// Assignment operator

		const std::string& getIdea(unsigned int index) const;	// Get the data
		void addIdea(const std::string& idea);					// Set the data

	private:

		std::string ideas[100];					// Array to store the ideas
		unsigned int count;						// Count of the ideas

};
