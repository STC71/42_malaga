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

		AForm(std::string _name, std::string _target, int _gradeSign, int _gradeExec);		// Constructor
		AForm(AForm& src);																	// Copy constructor

		virtual ~AForm();																	// Destructor

		AForm &operator=(AForm &rhs);														// Assignation operator

		const std::string& getName() const;													// Getters for the name of the form
		const std::string& getTarget() const;												// Getters for the target of the form
		bool getSigned() const;																// If the form is signed or not (true or false)
		int getGradeSign() const;															// Getters for the grade to sign the form
		int getGradeExec() const;															// Getters for the grade to execute the form

		void beSigned(Bureaucrat &bureaucrat);												// Function to sign the form
		void execute(Bureaucrat const &executor) const;										// Function to execute the form

		class gradeTooHighException : public std::exception {
			public:
				virtual const char *what() const throw();
		};																					// Exception for grade too high

		class gradeTooLowException : public std::exception {
			public:
				virtual const char *what() const throw();
		};																					// Exception for grade too low

	private:

		AForm();								// Default constructor

		const std::string _name;				// Name of the form
		const std::string _target;				// Target of the form
		const int _gradeSign;					// Grade to sign the form
		const int _gradeExec;					// Grade to execute the form
		bool _signed;							// Signed status of the form
		virtual void executeSuperClassForm(Bureaucrat const &executor) const = 0;	// Pure virtual function to execute the form

};

std::ostream &operator<<(std::ostream &stream, AForm &aForm);			// Overload of the << operator necessary to print the form
