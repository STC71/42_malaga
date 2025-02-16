/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:22:26 by sternero          #+#    #+#             */
/*   Updated: 2025-02-09 19:22:26 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm {			// Inherits from AForm

	public:

		PresidentialPardonForm(std::string _target); //
		PresidentialPardonForm(const PresidentialPardonForm& src);

		~PresidentialPardonForm();

		PresidentialPardonForm&operator=(const PresidentialPardonForm &assign);

		void executeSuperClassForm(Bureaucrat const &executor) const;

	private:

		PresidentialPardonForm();						// Default constructor

};