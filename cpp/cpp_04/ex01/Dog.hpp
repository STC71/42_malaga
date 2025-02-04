/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 18:39:04 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 18:39:04 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {

	public:

		Dog();										// Default constructor
		Dog(const Dog& src);						// Copy constructor
		~Dog();										// Destructor

		Animal& operator=(const Animal& src);		// Assignment operator

		void makeSound() const;						// Make a sound
		Brain *getBrain() const;					// Get the brain

	private:

		Brain *brain;								// Pointer to the brain to store the ideas

};