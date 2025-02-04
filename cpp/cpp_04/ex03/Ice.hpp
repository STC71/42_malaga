/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 12:36:35 by sternero          #+#    #+#             */
/*   Updated: 2025-02-02 12:36:35 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AMateria.hpp"

class Ice : public AMateria {

	public:

		Ice();										// Default constructor
		Ice(const Ice &src);						// Copy constructor
		Ice & operator=(const Ice &src);			// Assignation operator
		~Ice();										// Destructor
		AMateria* clone() const;					// Clone AMateria
		void use(ICharacter& target);				// Use AMateria

};