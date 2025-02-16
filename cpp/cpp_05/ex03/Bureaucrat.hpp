/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:22:13 by sternero          #+#    #+#             */
/*   Updated: 2025-02-09 19:22:13 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>
#include <iostream>
#include <string>
#include "AForm.hpp"

class AForm;											// Forward declaration to avoid circular dependency

class Bureaucrat {

	public:

		Bureaucrat();									// Default constructor
		Bureaucrat(const Bureaucrat &src);				// Copy constructor
		Bureaucrat(std::string _name, int _grade);		// Parametric constructor
		~Bureaucrat();									// Destructor

		Bureaucrat &operator=(const Bureaucrat &rhs);	// Assignment operator

		const std::string &getName() const;				// Get the name of the bureaucrat
		int getGrade() const;							// Get the grade of the bureaucrat

		void setGrade(int _grade);						// Set the grade of the bureaucrat
		void incrementGrade();							// Increment the grade of the bureaucrat
		void decrementGrade();							// Decrement the grade of the bureaucrat
		void signForm(std::string formName, bool wasSigned);	// Sign the form

		void executeForm(AForm const &form) ;			// Execute a form

		class GradeTooHighException : public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class GradeTooLowException : public std::exception {
			public:
				virtual const char *what() const throw();
		};

	private:

		int _grade;										// Grade of the bureaucrat
		const std::string _name;						// Name of the bureaucrat

};

std::ostream &operator<<(std::ostream &stream, Bureaucrat const &bureaucrat);	// Output operator
