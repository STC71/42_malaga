/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 11:07:29 by sternero          #+#    #+#             */
/*   Updated: 2025-02-28 11:07:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

using std::cerr; using std::cout; using std::endl;

// default constructor
RPN::RPN() {}

// copy constructor
RPN::RPN(const RPN &src) {
	*this = src;				// assign src to this
}

// assignment operator
RPN &RPN::operator=(const RPN &src) {
	(void)src;					// avoid unused parameter warning
	return *this;				// return this
}

// check if the expression is valid
bool RPN::validExpression(const std::string &expr) {
	std::stringstream ss(expr);					// create a stringstream object
	std::string tk;								// create a string object
	int numCount = 0, opCount = 0;				// numCount: number count, opCount: operator count

	while (ss >> tk) {							// while there is a token in the expression
		if (tk.find_first_not_of("0123456789") == std::string::npos)	// if the token is a number
			numCount++;							// increment the number count
		else if (tk == "+" || tk == "-" 
		|| tk == "*" || tk == "/") {			// if the token is an operator
			opCount++;							// increment the operator count
			if (numCount < 2)					// if the number count is less than 2
				return false;					// return false
			numCount--;							// decrement the number count
		}
		else
			return false;						// return false
	}
	return numCount == 1 && opCount > 0;		// return true if the number count is 1 and the operator count is greater than 0
}

// convert string to int
static int ft_stoi(const std::string &str) {
	int n;						// int variable
	std::stringstream ss(str);	// create a stringstream object
	ss >> n;					// convert string to int
	return n;					// return int
}

// exception message for invalid expression
const char *RPN::invalidExpression::what() const throw() {
	return RED "Error: invalid expression, no result." RESET;
}

// exception message for zero division
const char *RPN::zeroDivision::what() const throw() {
	return RED "Error: try to divide by zero." RESET;
}

// calculate the expression
long long RPN::calculator(const std::string &expr) {

	int i = 0, d = 0, res = 0;							// i: left, d: right, res: result

	std::stack<int> tmp;								// create a stack object named tmp
	std::stringstream nextOne(expr);					// create a stringstream object
	std::string tk;										// create a string object

	while (nextOne >> tk) {								// while there is a token in the expression
		if (tk == "+" || tk == "-" 
		|| tk == "*" || tk == "/") {					// if the token is an valid operator
		
			if (tmp.size() < 2) {						// if the stack is empty
				throw invalidExpression();				// throw an exception
			}

			d = tmp.top();								// get the top element of the stack
			tmp.pop();									// remove the top element of the stack
			i = tmp.top();								// get the top element of the stack
			tmp.pop();									// remove the top element of the stack

			switch (tk[0]) {							// switch case for the operator

				case '+':								// if the operator is '+'
					res = i + d;						// add the two elements
					break;								// break, end of the switch case

				case '-':								// if the operator is '-'
					res = i - d;						// subtract the two elements
					break;								// break, end of the switch case

				case '*':								// if the operator is '*'
					res = i * d;						// multiply the two elements
					break;								// break, end of the switch case

				case '/':								// if the operator is '/'
					if (d == 0)							// if the right element is 0
						throw zeroDivision();			// throw an exception
					res = i / d;						// divide the two elements
					break;								// break, end of the switch case
				
				default:								// if the operator is invalid
					throw invalidExpression();			// throw an exception

			}
			tmp.push(res);								// push the result to the stack
		}
		else
			tmp.push(ft_stoi(tk));						// push the token to the stack
	}

	if (tmp.size() != 1)								// if the stack size is different from 1
		throw invalidExpression();						// throw an exception

	return tmp.top();									// return the top element of the stack
}

// destructor
RPN::~RPN() {}
