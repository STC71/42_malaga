/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 15:55:02 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 15:55:02 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Animal.hpp"

// Include parent class to inherit from it and use its methods and attributes in this class

class Cat : public Animal {						// Inherit from Animal class

	public:
		Cat();									// Default constructor (set _type to "Cat")
		Cat(const Cat& src);					// Copy constructor (copy data from src to this)
		virtual ~Cat();							// Destructor

		using	Animal::operator=;				// Inherit operator= from Animal class
		void	makeSound() const;					// Make sound

};