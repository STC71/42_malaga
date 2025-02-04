/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMateriaSource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 12:36:02 by sternero          #+#    #+#             */
/*   Updated: 2025-02-02 12:36:02 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AMateria.hpp"

class IMateriaSource {

	public:

		virtual AMateria* createMateria(const std::string& type) = 0;	// Create AMateria
		virtual void learnMateria(AMateria*) = 0;						// Learn AMateria
		virtual ~IMateriaSource() {}									// Destructor

};