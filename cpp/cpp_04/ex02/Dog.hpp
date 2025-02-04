/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 09:26:47 by sternero          #+#    #+#             */
/*   Updated: 2025-01-31 09:26:47 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {

	public:

		Dog();										// default constructor
		Dog(const Dog& src);						// copy constructor
		Dog& operator=(const Dog& src);				// operator overload =
		Animal& operator=(const Animal& src);		// operator overload =
		~Dog();										// destructor

		void makeSound() const;						// function to make sound
		Brain *getBrain() const;					// function to get the brain

	private:

		Brain *_brain;								// private Brain *_brain

};