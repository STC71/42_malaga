/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-05 12:40:44 by sternero          #+#    #+#             */
/*   Updated: 2025-02-05 12:40:44 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

#define MAX_GRADE 1
#define MIN_GRADE 150

class Bureaucrat {

	public:

		Bureaucrat();									// Default constructor
		Bureaucrat(std::string _name, int _grade);		// Parametric constructor
		Bureaucrat(const Bureaucrat &orign);			// Copy constructor
		Bureaucrat &operator=(const Bureaucrat &src);	// Assignation operator
		~Bureaucrat();									// Destructor

		const std::string getName() const;				// Get the name of the bureaucrat
		int getGrade() const;							// Get the grade of the bureaucrat

		void incrementGrade();							// Increment the grade of the bureaucrat
		void decrementGrade();							// Decrement the grade of the bureaucrat
		void setGrade(int _grade);						// Set the grade of the bureaucrat

		class GradeTooHighException : public std::exception {
			public:
				virtual const char *what() const throw();
		};												// Exception for grade too high

		class GradeTooLowException : public std::exception {
			public:
				virtual const char *what() const throw();
		};												// Exception for grade too low

	private:
		std::string const _name;
		int _grade;

};

std::ostream &operator<<(std::ostream &stream, Bureaucrat &Bureaucrat);	// Overload of << operator	
