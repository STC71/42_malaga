/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 16:34:45 by sternero          #+#    #+#             */
/*   Updated: 2025-02-07 16:34:45 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

using std::cout;
using std::endl;

Form::Form(const Form &orign) : _name(orign._name), _gradeToSign(orign._gradeToSign), _gradeToExecute(orign._gradeToExecute), _signed(orign._signed) {
	cout<<"Calling to copy constructor 🧙"<<endl;
	cout<<"The form "<< this->getName() <<" has been copied."<<endl;
}

Form::Form(std::string _name, int _gradeToSign, int _gradeToExecute) : _name(_name), 
	_gradeToSign(_gradeToSign), _gradeToExecute(_gradeToExecute), _signed(false) {
	cout<<"Parametric constructor called 👨‍🔧"<<endl;
	if (_gradeToSign < MAX_GRADE || _gradeToExecute < MAX_GRADE)
		throw Form::GradeTooHighException();
	else if (_gradeToSign > MIN_GRADE || _gradeToExecute > MIN_GRADE)
		throw Form::GradeTooLowException();
	cout<<"Form 📝 "<< this->getName() <<" created with grade to sign "
	<< this->getGradeToSign() <<" and grade to execute "<< this->getGradeToExecute() <<endl;
	this->_signed = false;
	cout<<"The form "<< this->getName() <<" has been created."<<endl;
}

Form &Form::operator=(const Form &src) {
	if (this != &src) {
		this->_signed = src._signed;
	}
	return *this;
}


const char *Form::GradeTooLowException::what() const throw() {
	return "Error: Grade is too low 📉";
}

const char *Form::GradeTooHighException::what() const throw() {
	return "Error: Grade is too high 📈";
}

void Form::beSigned(Bureaucrat &bureaucrat) {
	if (bureaucrat.getGrade() <= this->getGradeToSign()) {
		this->_signed = true;
		bureaucrat.signForm(this->getName(), this->_signed);
		cout<<"The form "<< this->getName() <<" has been signed by "<< bureaucrat.getName() <<endl;
	}
	else {
		cout<<"The form "<< this->getName() <<" has not been signed by "<< bureaucrat.getName() <<endl;
		throw Form::GradeTooLowException();
	}
}

const std::string& Form::getName() const {
	return this->_name;
}										// Get the name of the form

int Form::getGradeToSign() const {
	return this->_gradeToSign;
}										// Get the grade to sign the form

int Form::getGradeToExecute() const {
	return this->_gradeToExecute;
}										// Get the grade to execute the form

bool Form::getSigned() const {
	return this->_signed;
}										// Get the status of the form

std::ostream &operator<<(std::ostream &stream, Form &form) {
	stream << "Form " << form.getName() << " with grade to sign " << form.getGradeToSign() 
	<< " and grade to execute " << form.getGradeToExecute() << " is ";
	if (form.getSigned())
		stream << "signed 📝";
	else
		stream << "not signed 🚫";
	return stream;
}

Form::~Form() {
	cout<<"Destructor called to "<< this->getName() <<" 🧟"<<endl;
}