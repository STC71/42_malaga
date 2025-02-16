/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-05 12:41:11 by sternero          #+#    #+#             */
/*   Updated: 2025-02-05 12:41:11 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

using std::cout;
using std::endl;

Bureaucrat::Bureaucrat() : _name("Default"), _grade(150) {
	cout << "Default constructor called 👷‍♂️" << endl;
}

Bureaucrat::Bureaucrat(std::string _name, int _grade) : _name(_name) {
	cout << "Parametric constructor called 👨‍🔧" << endl;
	if (_grade < MAX_GRADE)
		throw Bureaucrat::GradeTooHighException();						// throw exception if grade is too high
	else if (_grade > MIN_GRADE)
		throw Bureaucrat::GradeTooLowException();
	else
		this->_grade = _grade;
	cout << "Bureaucrat " << this->getName() << " 🤹 created with grade " << this->_grade << endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat& origin) {
	cout << "Calling to copy constructor 🧙" << endl;
	if (this != &origin)
		*this = origin;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& src) {
	const_cast<std::string&>(this->_name) = src._name;
	this->_grade = src._grade;
	cout << "Bureaucrat: " << this->getName() << " -> Copy assignation operator called 🧑‍🔧" << endl;
	return *this;
}

Bureaucrat::~Bureaucrat() {
	cout << "Destructor called to " << this->getName() << " 🧟\n";
}

const std::string Bureaucrat::getName() const {
	return this->_name;
}

int Bureaucrat::getGrade() const {
	return this->_grade;
}

void Bureaucrat::setGrade(int _grade) {
	if (_grade < MAX_GRADE)
		throw Bureaucrat::GradeTooHighException();
	else if (_grade > MIN_GRADE)
		throw Bureaucrat::GradeTooLowException();
	else
		this->_grade = _grade;
}

void Bureaucrat::decrementGrade() {
	if (_grade + 1 > MIN_GRADE)
		throw Bureaucrat::GradeTooLowException();
	else
		this->_grade++;
}

void Bureaucrat::incrementGrade() {
	if (_grade - 1 < MAX_GRADE)
		throw Bureaucrat::GradeTooHighException();
	else
		this->_grade--;
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
	return "Error: Grade is too high 📈\n";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
	return "Error: Grade is too low 📉\n";
}

std::ostream& operator<<(std::ostream& stream, Bureaucrat& bureaucrat) {
	stream << bureaucrat.getName() << " 🤹 has grade " << bureaucrat.getGrade() << endl;
	return stream;
}