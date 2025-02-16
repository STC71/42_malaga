/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:22:39 by sternero          #+#    #+#             */
/*   Updated: 2025-02-09 19:22:39 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>							// std::ofstream to write to file
#include <iostream>
#include "ShrubberyCreationForm.hpp"

using std::cerr; using std::cout; using std::endl;

ShrubberyCreationForm::ShrubberyCreationForm(std::string _target) 
: AForm("ShrubberyCreationForm", _target, 145, 137) {
	cout << "ShrubberyCreationForm: parametric constructor called" << endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& src) 
: AForm(src.getName(), src.getTarget(), src.getGradeSign(), src.getGradeExec()) {
	cout << "ShrubberyCreationForm: copy constructor called" << endl;
	//*this = src;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &assign) {
	cout << "ShrubberyCreationForm: assignation operator called" << endl;
	if (this == &assign)
		return *this;
	return *this;
}

void ShrubberyCreationForm::executeSuperClassForm(Bureaucrat const &executor) const {
	if (executor.getGrade() > this->getGradeExec())
		throw Bureaucrat::GradeTooHighException();
	else if (this->getSigned() == false)
		cerr << executor.getName() << " cannot execute " << this->getName() << " because the form is not signed" << endl;
	else {
		std::ofstream out;
		
		out.open((this->getTarget() + "_shrubbery").c_str(), std::ofstream::in | std::ofstream::trunc);

		out << "\n"
			<< "       # #### #### ##           " << "\n"
			<< "     ### \\/#|###|/####         " << "\n"
			<< "    ##\\/#/ \\||/##/_/##/#      " << "\n"
			<< "  ###  \\/###|/ \\/ # #####     " << "\n"
			<< " ##_\\_#\\_\\##|#/###_/_####    " << "\n"
			<< "## #### # \\ #|/#### ##/##      " << "\n"
			<< " __#_--###` |{,###---###~       " << "\n"
			<< "          \\ }{                 " << "\n"
			<< "           }}{                  " << "\n"
			<< "           }}{                  " << "\n"
			<< "          {{{}}                 " << "\n"
			<< "     ,_-=-~{ .-^- _:)           " << endl;
	}
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	cout << "ShrubberyCreationForm: destructor called" << endl;
}
