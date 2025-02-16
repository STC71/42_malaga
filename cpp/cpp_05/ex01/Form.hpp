/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 16:31:35 by sternero          #+#    #+#             */
/*   Updated: 2025-02-07 16:31:35 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Bureaucrat.hpp"
#include <cstdlib>								// std::rand
#include <exception>							// std::exception
#include <iostream>								// std::cout std::endl
#include <string>								// std::string

#define MAX_GRADE 1
#define MIN_GRADE 150

class Form {

	public:

		Form(std::string _name, int gradeToSign, int gradeToExecute);				// Parametric constructor
		Form(const Form &orign);				// Copy constructor
		Form &operator=(const Form &src);		// Assignation operator
		~Form();								// Destructor
		
		const std::string& getName() const;		// Get the name of the form
		
		int	getGradeToSign() const;				// Get the grade to sign the form
		int	getGradeToExecute() const;			// Get the grade to execute the form
		bool getSigned() const;					// Get the status of the form
		
		void beSigned(Bureaucrat &bureaucrat);	// Sign the form
		
		class GradeTooHighException : public std::exception {
			public:
			virtual const char *what() const throw();
		};										// Exception for grade too high
		
		class GradeTooLowException : public std::exception {
			public:
			virtual const char *what() const throw();
		};										// Exception for grade too low
		
	private:
		
		const std::string _name;
		const int _gradeToSign;
		const int _gradeToExecute;
		bool _signed;
		Form();									// Default constructor

};

std::ostream &operator<<(std::ostream &stream, Form &form);	// Overload of << operator