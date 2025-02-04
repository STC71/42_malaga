/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 12:34:00 by sternero          #+#    #+#             */
/*   Updated: 2025-02-02 12:34:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AMateria.hpp"

class Cure : public AMateria {

	public:

		Cure();										// Default constructor
		Cure(const Cure &src);						// Copy constructor
		Cure & operator=(const Cure &src);			// Assignation operator
		~Cure();									// Destructor
		AMateria* clone() const;					// Clone AMateria
		void use(ICharacter& target);				// Use AMateria

};