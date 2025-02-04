/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 12:32:52 by sternero          #+#    #+#             */
/*   Updated: 2025-02-02 12:32:52 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include "ICharacter.hpp"

class ICharacter;

class AMateria {

	public:

		AMateria(std::string const & _type);					// Default constructor
		AMateria(const AMateria &src);						// Copy constructor
		virtual ~AMateria();								// Destructor
		virtual const std::string & getType() const;		// Getter for type
		virtual AMateria* clone() const = 0;				// Virtual function to clone AMateria
		virtual void use(ICharacter& target) = 0;			// Virtual function to use AMateria

	protected:

		std::string _type;									// Type of AMateria

};