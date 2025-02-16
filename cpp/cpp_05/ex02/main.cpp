/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:22:18 by sternero          #+#    #+#             */
/*   Updated: 2025-02-09 19:22:18 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>								// time() to seed srand() for random numbers
#include <iostream>
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

using std::cerr; using std::cout; using std::endl;

int main() {

	cout << endl;								// Newline for readability

	cout << BLUE << "Creating bureaucrats: \n" << RESET << endl;

	Bureaucrat Donald("Donald", MAX_GRADE);		// Bureaucrat with grade 1 (max)
	Bureaucrat Sam("Sam", 42);					// Bureaucrat with grade 42 (middle)
	Bureaucrat Joe("Joe", MIN_GRADE);			// Bureaucrat with grade 150 (min)

	cout << endl;								// Newline for readability

	cout << BLUE << "Creating forms: \n" << RESET << endl;

	ShrubberyCreationForm JB007("Donald");		// ShrubberyCreationForm with random values to test
	PresidentialPardonForm C3R41("Donald");		// PresidentialPardonForm with random values to test
	RobotomyRequestForm MA042("Donald");			// RobotomyRequestForm with random values to test

	cout << endl;								// Newline for readability

	cout << BLUE << "Signing and executing forms: \n" << RESET << endl;

	Donald.executeForm(JB007);					// Donald executes the form
	JB007.beSigned(Donald);						// Donald signs the form
	Donald.executeForm(JB007);					// Donald executes the form

	cout << endl;								// Newline for readability

	Donald.executeForm(C3R41);					// Donald executes the form
	C3R41.beSigned(Donald);						// Sam executes the form
	Donald.executeForm(C3R41);						// Joe executes the form

	cout << endl;								// Newline for readability

	Donald.executeForm(MA042);					// Donald executes the form
	MA042.beSigned(Donald);						// Donald signs the form
	Donald.executeForm(MA042);					// Donald executes the form

	cout << endl;								// Newline for readability

	cout << BLUE << "Trying to execute forms with wrong grades: \n" << RESET << endl;

	try {
		Joe.executeForm(JB007);					// Joe try to execute the form (grade too low)
	} catch (std::exception &e) {
		cerr << RED << e.what() << RESET << endl;
	}

	cout << endl;								// Newline for readability

	cout << BLUE << "* * * * * * * END OF TESTS * * * * * * *\n" << RESET << endl;

	return 0;

}
