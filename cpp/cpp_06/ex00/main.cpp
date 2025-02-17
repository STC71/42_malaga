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

using std::cerr; using std::endl;						// std::cerr, std::endl

int main(int argc, char **argv) {						// Main function
	if (argc != 2 || !argv[1][0]) {						// If the number of arguments is not 2 or the argument is empty
		cerr << RED << "Error" << RESET << ": Invalid arguments" << endl;	// Print the error message
		cerr << GREEN << "Usage" << RESET": ./convert [value]" << endl;		// Print the usage message
		return 1;										// Return 1
	}

	ScalarConverter::convert(argv[1]);					// Convert the value
	return 0;											// Return 0
}
