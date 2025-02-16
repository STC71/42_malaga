/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:22:35 by sternero          #+#    #+#             */
/*   Updated: 2025-02-09 19:22:35 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"

class RobotomyRequestForm : public AForm {			// Inherits from AForm

	public:

		RobotomyRequestForm(std::string _target);
		RobotomyRequestForm(const RobotomyRequestForm& src);

		~RobotomyRequestForm();

		RobotomyRequestForm &operator=(const RobotomyRequestForm &assign);

		void executeSuperClassForm(Bureaucrat const &executor) const;

	private:

		RobotomyRequestForm();						// Default constructor

};