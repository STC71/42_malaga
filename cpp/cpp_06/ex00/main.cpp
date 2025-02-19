/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-16 15:19:32 by sternero          #+#    #+#             */
/*   Updated: 2025-02-16 15:19:32 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"							// ScalarConverter

using std::cerr; using std::cout; using std::endl;

int main(int argc, char **argv) {						// Main function
	if (argc != 2 || !argv[1][0]) {						// If the number of arguments is not 2 or the argument is empty
		cerr << RED << "Error" << RESET << ": Invalid arguments" << endl;	// Print the error message
		cerr << GREEN << "Usage" << RESET": ./convert [value]" << endl;		// Print the usage message
		return 1;										// Return 1
	}

	cout << BLUE << "\n* * * Scalar Converter * * *" << RESET << endl;	// Print the title
	cout << "   _____________________" << endl;			// Print the calculator
	cout << "  |  _________________  |" << endl;
	cout << "  | | STC         42. | |" << endl;
	cout << "  | |_________________| |" << endl;
	cout << "  |  ___ ___ ___   ___  |" << endl;
	cout << "  | | 7 | 8 | 9 | | + | |" << endl;
	cout << "  | |___|___|___| |___| |" << endl;
	cout << "  | | 4 | 5 | 6 | | - | |" << endl;
	cout << "  | |___|___|___| |___| |" << endl;
	cout << "  | | 1 | 2 | 3 | | x | |" << endl;
	cout << "  | |___|___|___| |___| |" << endl;
	cout << "  | | . | 0 | = | | / | |" << endl;
	cout << "  | |___|___|___| |___| |" << endl;
	cout << "  |_____________________|\n" << RESET << endl;

	ScalarConverter::convert(argv[1]);					// Convert the value

	cout << BLUE << "\n* * * * your results * * * *\n" << RESET << endl;	// Print the subtitle

	return 0;											// Return 0
}
