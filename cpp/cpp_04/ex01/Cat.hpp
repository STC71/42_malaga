/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 18:38:42 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 18:38:42 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {

	public:

		Cat();										// Default constructor
		Cat(const Cat& src);						// Copy constructor
		virtual ~Cat();								// Destructor

		Animal& operator=(const Animal& src);		// Assignment operator

		void makeSound() const;						// Make a sound
		Brain *getBrain() const;					// Get the brain

	private:

		Brain *brain;								// Pointer to the brain to store the ideas

};