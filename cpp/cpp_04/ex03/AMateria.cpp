/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 12:32:28 by sternero          #+#    #+#             */
/*   Updated: 2025-02-02 12:32:28 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(const std::string& _type) : _type(_type) {}	// Default constructor

const std::string & AMateria::getType() const { return _type; }	// Getter for type

AMateria::~AMateria() {}										// Destructor