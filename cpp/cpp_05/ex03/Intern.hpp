/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-12 20:39:33 by sternero          #+#    #+#             */
/*   Updated: 2025-02-12 20:39:33 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"
#include <string>

class Intern {

	public:

		Intern();								// Default constructor
		Intern(const Intern &src);				// Copy constructor
		~Intern();								// Destructor

		Intern &operator=(const Intern &rhs);	// Assignment operator

		AForm *makeForm(std::string formName, std::string target);

};