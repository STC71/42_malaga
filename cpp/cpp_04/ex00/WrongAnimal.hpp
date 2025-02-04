/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 15:55:32 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 15:55:32 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

class WrongAnimal {

	public:
		WrongAnimal();									// Default constructor
		WrongAnimal(const WrongAnimal& src);			// Copy constructor
		virtual ~WrongAnimal();							// Destructor

		WrongAnimal& operator=(const WrongAnimal& src);	// Assignment operator
		const std::string& getType() const;				// Getter for type
		void setType(const std::string& type);			// Setter for type
		void makeSound() const;							// Make sound

	protected:
		std::string _type;								// Type of animal
		WrongAnimal(const std::string& type);			// Constructor with type

};