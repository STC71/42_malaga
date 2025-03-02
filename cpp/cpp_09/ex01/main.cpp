/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 20:03:36 by sternero          #+#    #+#             */
/*   Updated: 2025-02-26 20:03:36 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

using std::cerr; using std::cout; using std::endl;

static int evil(const std::string &error) {
	cerr << RED << ERROR_MSG << " " << error << RESET << endl;		// print error message
	exit(EXIT_FAILURE);												// exit with failure status code 1
}

int main(int argc, char *argv[]) {

	if (argc != 2)									// if the number of arguments is different from 2
		return evil(ERROR_ARG);						// print error message and exit with failure status code 1

	if (!RPN::validExpression(argv[1]))				// if the expression is invalid
		return evil(ERROR_EXP);						// print error message and exit with failure status code 1

	cout << "\n" << BLUE;
	cout << "==================" << endl;
	cout << " |@@@@----@|--@@| " << endl;
	cout << " |@@@----@@|--@@| " << endl;
	cout << " |@@----@@@|--@@| " << endl;
	cout << " |@----@@@@|--@@| " << endl;
	cout << " |@@@@@----|@--@| " << endl;
    cout << " |@@@@----@|@--@| " << endl;
	cout << "==================\n" << RESET << endl;

	try {
		cout << "Result: " << GREEN << RPN::calculator(argv[1]) 
		<< RESET << endl << endl;					// print the result
	} catch (std::exception &e) {
		cerr << e.what() << endl << endl;			// print the exception message
	}

	return EXIT_SUCCESS;							// exit with success status code 0

}
