/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-22 16:49:33 by sternero          #+#    #+#             */
/*   Updated: 2025-02-22 16:49:33 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

using std::cerr; using std::cout; using std::endl;

int	main() {

	// Values to initialize vector
	int	ini = 0; int end = 10;

	std::vector<int> vec;

	cout << BLUE << "\nVector: { ";

	for (int i = ini; i < end; i++) {
		vec.push_back(i);
		cout << i << (i < 9 ? ", " : " }");
	}

	cout << RESET << endl;

	int j;

	cout << "\nSelect number to find in vector 🕵️‍♂️ : ";
	//std::cin >> j;
	while (!(std::cin >> j)) {		// Check for invalid input 
		std::cin.clear();				// Clear the error flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//
		cout << RED << "~Invalid input 🤬 " << RESET << "try to do better : ";
	}

	cout << endl;

	try {
		if (easyfind(vec, j))
			cout << GREEN << "Perfect! " << RESET << "Value " << j << " found in vector 👌" << endl;
	}	catch (const std::exception &e) {
		cerr << RED << e.what() << RESET << endl;
	}

	return 0;

}