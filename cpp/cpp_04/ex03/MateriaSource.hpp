/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 12:37:39 by sternero          #+#    #+#             */
/*   Updated: 2025-02-02 12:37:39 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class MateriaSource : public IMateriaSource {

	public:

		MateriaSource();											// Default constructor
		MateriaSource(const MateriaSource &src);					// Copy constructor
		MateriaSource &operator=(const MateriaSource &src);			// Assignation operator
		~MateriaSource();											// Destructor
		virtual void learnMateria(AMateria* m);						// Learn AMateria
		virtual AMateria* createMateria(const std::string& type);	// Create AMateria
		void	printMaterias() const;								// Print AMateria

	private:

		AMateria*	_materias[4];					// Array of AMateria
		int			_materiasSize;					// Size of array

};
