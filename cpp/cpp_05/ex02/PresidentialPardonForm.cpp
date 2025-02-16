/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:22:22 by sternero          #+#    #+#             */
/*   Updated: 2025-02-09 19:22:22 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PresidentialPardonForm.hpp"

using std::cerr; using std::cout; using std::endl;

PresidentialPardonForm::PresidentialPardonForm(std::string _target) 
: AForm("PresidentialPardonForm", _target, 25, 5)  {
	cout << "PresidentialPardonForm: parametric constructor called" << endl;
	
}						// 25, 5 are the grades to sign and execute the form

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& src) 
: AForm(src.getName(), src.getTarget(), src.getGradeSign(), src.getGradeExec()) {
	cout << "PresidentialPardonForm: copy constructor called" << endl;
	*this = src;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &assign) {
	cout << "PresidentialPardonForm: assignation operator called" << endl;
	if (this == &assign)
		return *this;
	return *this;
}

void PresidentialPardonForm::executeSuperClassForm(Bureaucrat const &executor) const {
	if (executor.getGrade() > this->getGradeExec())
		throw Bureaucrat::GradeTooLowException();
	else if (this->getSigned() == false)
		cerr << executor.getName() << " cannot execute " << this->getName() << " because the form is not signed" << endl;
	else
		cout << this->getTarget() << " has been pardoned by Zafod Beeblebrox" << endl;
}

PresidentialPardonForm::~PresidentialPardonForm() {
	cout << "PresidentialPardonForm: destructor called" << endl;
}
