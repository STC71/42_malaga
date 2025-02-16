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

#include <cstdlib>
#include <iostream>
#include "AForm.hpp"
#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

using std::cerr; using std::cout; using std::endl;

int main() {

	AForm *a; AForm *b; AForm *c;							// Pointers to AForm objects

	cout << endl;											// Newline for readability

	Intern Musk;											// Create an Intern object
	cout << endl;											// Newline for readability

	a = Musk.makeForm("presidential pardon", "Donald");		// Create a PresidentialPardonForm object
	cout << endl;											// Newline for readability

	b = Musk.makeForm("robotomy request", "Donald");		// Create a RobotomyRequestForm object
	cout << endl;											// Newline for readability

	c = Musk.makeForm("shrubbery creation", "Donald");		// Create a ShrubberyCreationForm object
	cout << endl;											// Newline for readability
	
	Musk.makeForm("UP2U", "Donald");						// Create a PresidentialPardonForm object
	cout << endl;											// Newline for readability

	delete a; delete b; delete c;							// Delete the AForm objects

	return 0;
	
}
