/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 15:55:46 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 15:55:46 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "WrongAnimal.hpp"
// Include parent class to inherit from it and use its methods and attributes in this class

class WrongCat : public WrongAnimal {				// Inherit from WrongAnimal class

	public:
		WrongCat();									// Default constructor (set _type to "WrongCat")
		WrongCat(const WrongCat& src);				// Copy constructor (copy data from src to this)
		~WrongCat();								// Destructor

		using	WrongAnimal::operator=;				// Inherit operator= from WrongAnimal class
		void	makeSound() const;					// Make sound

};