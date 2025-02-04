/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 09:26:21 by sternero          #+#    #+#             */
/*   Updated: 2025-01-31 09:26:21 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {

	public:

		Cat();										// default constructor
		Cat(const Cat& src);						// copy constructor
		Cat& operator=(const Cat& src);				// operator overload =
		Animal& operator=(const Animal& src);		// operator overload =
		~Cat();										// destructor

		void makeSound() const;						// function to make sound
		Brain *getBrain() const;					// function to get the brain

	private:

		Brain *_brain;								// private Brain *_brain

};