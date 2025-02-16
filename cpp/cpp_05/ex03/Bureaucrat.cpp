/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:22:10 by sternero          #+#    #+#             */
/*   Updated: 2025-02-09 19:22:10 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

using std::cerr;						// std::cerr is used to output errors
using std::cout;
using std::endl;

Bureaucrat::Bureaucrat() {
	cout << "Bureaucrat: default => constructor called" << endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &src) {
	if (this != &src) {
		cout << "Bureaucrat: " << this-> getName() << " => copy constructor called" << endl;
		*this = src;
	}
}

Bureaucrat::Bureaucrat(std::string _name, int _grade) : _name(_name) {
	cout << "Bureaucrat: " << this->getName() << " => parametric constructor called" << endl;
	if (_grade < MAX_GRADE) {
		cerr << "Bureaucrat " << this->getName() << " => Error: Grade too high" << endl;
		throw GradeTooHighException();
	}
	else if (_grade > MIN_GRADE) {
		cerr << "Bureaucrat " << this->getName() << " => Error: Grade too low" << endl;
		throw GradeTooLowException();
	}
	else
		this->_grade = _grade;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &rhs) {
	cout << "Bureaucrat: " << this->getName() << " => assignment operator called" << endl;
	const_cast<std::string &>(this->_name) = rhs._name;			// const_cast is used to remove the constness of the object
	this->_grade = rhs._grade;
	return *this;
}

std::ostream &operator<<(std::ostream &stream, Bureaucrat &bureaucrat) {
	stream << "Bureaucrat: " << bureaucrat.getName() << " => grade " << bureaucrat.getGrade() << endl;
	return stream;
}

const std::string& Bureaucrat::getName() const {
	return this->_name;
}																// Get the name of the bureaucrat

const char* Bureaucrat::GradeTooHighException::what() const throw() {
	return "Bureaucrat: Grade too high";
}																// Return the exception message

const char* Bureaucrat::GradeTooLowException::what() const throw() {
	return "Bureaucrat: Grade too low";
}																// Return the exception message

int Bureaucrat::getGrade() const {
	return this->_grade;
}																// Get the grade of the bureaucrat

void Bureaucrat::incrementGrade() {
	if (_grade -1 < MAX_GRADE)									// Increment the grade of the bureaucrat
		throw Bureaucrat::GradeTooHighException();
	else
		this->_grade--;
}

void Bureaucrat::decrementGrade() {
	if (_grade +1 > MIN_GRADE)									// Decrement the grade of the bureaucrat
		throw Bureaucrat::GradeTooLowException();
	else
		this->_grade++;
}																// Decrement the grade of the bureaucrat

void Bureaucrat::setGrade(int _grade) {
	if (_grade < MAX_GRADE) {
		cerr << "Bureaucrat " << this->getName() << " => Error: Grade too high" << endl;
		throw GradeTooHighException();
	}
	else if (_grade > MIN_GRADE) {
		cerr << "Bureaucrat " << this->getName() << " => Error: Grade too low" << endl;
		throw GradeTooLowException();
	}
	else
		this->_grade = _grade;
}																// Set the grade of the bureaucrat

void Bureaucrat::signForm(std::string formName, bool wasSigned) {
	if (wasSigned)
		cout << "Bureaucrat " << this->getName() << " => signed form " << formName << endl;
	else
		cout << "Bureaucrat " << this->getName() << " => cannot sign form " << formName << endl;
}																// Sign the form

void Bureaucrat::executeForm(AForm const &form) {
	form.execute(*this);
}																// Execute a form

Bureaucrat::~Bureaucrat() {
	cout << "Bureaucrat: " << this->getName() << " => destructor called" << endl;
}
