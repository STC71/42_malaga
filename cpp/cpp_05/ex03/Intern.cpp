/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-12 20:39:52 by sternero          #+#    #+#             */
/*   Updated: 2025-02-12 20:39:52 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

using std::cerr; using std::cout; using std::endl;

Intern::Intern() {
	cout << "Intern: " << BLUE << "default constructor" << RESET << " called" << endl;
}

Intern::Intern(const Intern &src) {
	cout << "Intern: " << BLUE << "copy constructor" << RESET << " called" << endl;
	*this = src;
}

Intern &Intern::operator=(const Intern &rhs) {
	cout << "Intern: " << BLUE << "assignation operator" << RESET << " called" << endl;
	if (this == &rhs)
		return *this;
	return *this;
}

Intern::~Intern() {
	cout << "Intern: " << RED << "destructor" << RESET << " called" << endl;
}

static AForm *createPresidentialPardonForm(const std::string target) {
	return new PresidentialPardonForm(target);
}									// Create a PresidentialPardonForm

static AForm *createRobotomyRequestForm(const std::string target) {
	return new RobotomyRequestForm(target);
}									// Create a RobotomyRequestForm

static AForm *createShrubberyCreationForm(const std::string target) {
	return new ShrubberyCreationForm(target);
}									// Create a ShrubberyCreationForm

typedef AForm *(*formCreationFunction)(const std::string target);	// Typedef for the function pointer

AForm *Intern::makeForm(std::string formName, std::string target) {

	AForm *form = NULL;						// Initialize the form to NULL

	const std::string formNames[] = {
		"presidential pardon", 
		"robotomy request", 
		"shrubbery creation" 
	};

	formCreationFunction formCreation[3] = {
		createPresidentialPardonForm, 
		createRobotomyRequestForm, 
		createShrubberyCreationForm
	};

	for (int i = 0; i < 3; i++) {
		if (formName == formNames[i]) {
			cout << "Intern creates " << GREEN << formName << RESET << " form" << endl;
			form = formCreation[i](target);
			break;
		}
	}
	if (form == NULL)
		cerr << "Intern cannot create " << RED << formName << RESET << " form" << endl;
	return form;

}