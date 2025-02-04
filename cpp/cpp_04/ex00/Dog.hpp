/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 15:55:16 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 15:55:16 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Animal.hpp"
// Include parent class to inherit from it and use its methods and attributes in this class

class Dog : public Animal {						// Inherit from Animal class

	public:
		Dog();									// Default constructor (set _type to "Dog")
		Dog(const Dog&);						// Copy constructor (copy data from src to this)
		virtual ~Dog();							// Destructor

		using	Animal::operator=;				// Inherit operator= from Animal class
		void	makeSound() const;				// Make sound

};