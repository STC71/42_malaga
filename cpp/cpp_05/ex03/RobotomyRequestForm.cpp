/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:22:31 by sternero          #+#    #+#             */
/*   Updated: 2025-02-09 19:22:31 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>							// std::time to seed srand
#include <cstdlib>							// std::rand to generate random number
#include <iostream>
#include "RobotomyRequestForm.hpp"

using std::cerr; using std::cout; using std::endl;

RobotomyRequestForm::RobotomyRequestForm(std::string _target) 
: AForm("RobotomyRequestForm", _target, 72, 45) {
	cout << "RobotomyRequestForm: parametric constructor called" << endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& src)
: AForm(src.getName(), src.getTarget(), src.getGradeSign(), src.getGradeExec()) {
	cout << "RobotomyRequestForm: copy constructor called" << endl;
	//*this = src;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &assign) {
	cout << "RobotomyRequestForm: assignation operator called" << endl;
	if (this == &assign)
		return *this;
	return *this;
}

void RobotomyRequestForm::executeSuperClassForm(Bureaucrat const &executor) const {
	if (executor.getGrade() > this->getGradeExec())
		throw Bureaucrat::GradeTooLowException();
	else if (!this->getSigned() == false)
		cerr << executor.getName() << " cannot execute " << this->getName() << " because the form is not signed" << endl;
	else {
		std::srand(std::time(NULL));
		cout << GREEN <<"\n* * * * * * * drilling noises * * * * * * *\n" << RESET << endl;
		if (random() % 2 == 0)
			cout << this->getTarget() << " has been robotomized successfully" << endl;
		else
			cout << this->getTarget() << " has not been robotomized successfully" << endl;
	}
}

RobotomyRequestForm::~RobotomyRequestForm() {
	cout << "RobotomyRequestForm: destructor called" << endl;
}