/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 18:38:07 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 18:38:07 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Brain.hpp"
#include <iostream>
#include <string>

class Animal {

	public:

		Animal();							// Default constructor
		Animal(const Animal& src);			// Copy constructor
		virtual ~Animal();					

		virtual Animal& operator=(const Animal& src);			// Assignment operator

		const std::string& getType() const;			// Get the data (type) to identify the animal
		virtual void makeSound() const;				// Make a sound (virtual function) of the animal
		virtual Brain *getBrain() const = 0;		// Get the brain (pure virtual function) of the animal
		void setType(const std::string &type);		// Set the data (type) to identify the animal

	protected:
	
		Animal(const std::string& type);		// Constructor with parameter to set the data (type) to identify the animal
		std::string type;						// Data to identify the animal (type) to identify the animal

};