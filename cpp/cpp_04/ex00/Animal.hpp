/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 15:54:36 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 15:54:36 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

class Animal {

	public:
		Animal();									// Default constructor
		Animal(const Animal& src);					// Copy constructor
		virtual ~Animal();							// Destructor

		Animal& operator=(const Animal& src);		// Assignment operator
		const std::string& getType() const;			// Getter for type
		void setType(const std::string& type);		// Setter for type
		virtual void makeSound() const;				// Make sound

	protected:
		std::string _type;							// Type of animal
		Animal(const std::string& type);			// Constructor with type

};