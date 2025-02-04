/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 09:25:21 by sternero          #+#    #+#             */
/*   Updated: 2025-01-31 09:25:21 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include "Brain.hpp"

class Animal {

	public:

		virtual Animal& operator=(const Animal& src) = 0;		// virtual pure function to overload =
		virtual ~Animal();										// virtual destructor
		const std::string& getType() const;						// const function to get the type
		void setType(const std::string& _type);					// function to set the type
		virtual void makeSound() const = 0;						// virtual pure function to make sound
		virtual Brain *getBrain() const = 0;					// virtual pure function to get the brain

	protected:

		std::string _type;										// protected string _type

};
