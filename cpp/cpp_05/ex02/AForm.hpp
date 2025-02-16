/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:22:06 by sternero          #+#    #+#             */
/*   Updated: 2025-02-09 19:22:06 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Bureaucrat.hpp"
#include <exception>
#include <iostream>
#include <string>

#define MAX_GRADE 1
#define MIN_GRADE 150

#define BLUE "\033[0;34m"
#define RED "\033[1;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

class Bureaucrat;				// Forward declaration to avoid circular dependency

class AForm {

	public:

		AForm(std::string _name, std::string _target, int _gradeSign, int _gradeExec);
		AForm(AForm& src);

		virtual ~AForm();

		AForm &operator=(AForm &rhs);

		const std::string& getName() const;
		const std::string& getTarget() const;
		bool getSigned() const;
		int getGradeSign() const;
		int getGradeExec() const;

		void beSigned(Bureaucrat &bureaucrat);
		void execute(Bureaucrat const &executor) const;

		class gradeTooHighException : public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class gradeTooLowException : public std::exception {
			public:
				virtual const char *what() const throw();
		};

	private:

		AForm();

		const std::string _name;				// Name of the form
		const std::string _target;				// Target of the form
		const int _gradeSign;					// Grade to sign the form
		const int _gradeExec;					// Grade to execute the form
		bool _signed;							// Signed status of the form
		virtual void executeSuperClassForm(Bureaucrat const &executor) const = 0;

};

std::ostream &operator<<(std::ostream &stream, AForm &aForm);
