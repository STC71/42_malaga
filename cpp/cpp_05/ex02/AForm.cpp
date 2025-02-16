/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:22:00 by sternero          #+#    #+#             */
/*   Updated: 2025-02-09 19:22:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

using std::cout;
using std::endl;

AForm::AForm(std::string _name, std::string _target, int _gradeSign, int _gradeExec) 
: _name(_name), _target(_target), _gradeSign(_gradeSign), _gradeExec(_gradeExec), _signed(false) {
	if (_gradeSign < MAX_GRADE || _gradeExec < MAX_GRADE) {
		cout << "AForm Error: Grade too high" << endl;
		throw gradeTooHighException();
	}
	if (_gradeSign > MIN_GRADE || _gradeExec > MIN_GRADE) {
		cout << "AForm Error: Grade too low" << endl;
		throw gradeTooLowException();
	}
}

AForm::AForm(AForm& src) 
: _name(src.getName()), _target(src.getTarget()), _gradeSign(src.getGradeSign()), _gradeExec(src.getGradeExec()), _signed(src.getSigned()) {
	cout << "AForm: copy constructor called" << endl;
}

AForm &AForm::operator=(AForm &rhs) {
	cout << "AForm: assignment operator called" << endl;
	this->_signed = rhs.getSigned();
	return *this;
}

std::ostream &operator<<(std::ostream &stream, AForm &form) {
	stream << "Form: " << form.getName() << endl;
	cout << "    Target: " << form.getTarget() << endl;
	cout << "    Grade to sign: " << form.getGradeSign() << endl;
	cout << "    Grade to execute: " << form.getGradeExec() << endl;
	cout << "    Signed: " << form.getSigned() << endl;
	return stream;
}

const std::string& AForm::getName() const {
	return this->_name;
}												// Get the name of the form

const std::string& AForm::getTarget() const {
	return this->_target;
}												// Get the target of the form

int AForm::getGradeSign() const {
	return _gradeSign;
}												// Get the grade to sign the form

int AForm::getGradeExec() const {
	return _gradeExec;
}												// Get the grade to execute the form

bool AForm::getSigned() const {
	return _signed;
}												// Get the signed status of the form

void AForm::execute(Bureaucrat const &executor) const {
	this->executeSuperClassForm(executor);
}												// Execute the form

void AForm::beSigned(Bureaucrat &bureaucrat) {
	if (bureaucrat.getGrade() <= this->_gradeSign) {
		this->_signed = true;
		bureaucrat.signForm(this-> getName(), this->_signed);
	}
	else {
		bureaucrat.signForm(this-> getName(), this->_signed);
		throw gradeTooLowException();
	}
}												// Sign the form

const char *AForm::gradeTooHighException::what() const throw() {
	return "AForm Error: Grade too high";
}

const char *AForm::gradeTooLowException::what() const throw() {
	return "AForm Error: Grade too low";
}

AForm::~AForm() {
	cout << "AForm: destructor called" << endl;
}
