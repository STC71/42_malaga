/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serialization.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-16 15:32:38 by sternero          #+#    #+#             */
/*   Updated: 2025-02-16 15:32:38 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Data.hpp"

class Serialization {

	public:

		static uintptr_t serialize(Data* ptr);			// Serialize Data struct into a uintptr_t
		static Data* deserialize(uintptr_t converted);	// Deserialize uintptr_t into a Data struct
	
	private:

		Serialization();									// Default constructor
		~Serialization();									// Destructor
		Serialization(Serialization const &src);			// Copy constructor
		Serialization &operator=(Serialization const &src);	// Assignation operator

};
