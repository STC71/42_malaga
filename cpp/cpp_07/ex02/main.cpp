/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-21 14:58:21 by sternero          #+#    #+#             */
/*   Updated: 2025-02-21 14:58:21 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

using std::cerr; using std::cout; using std::endl;

int	main() {

	cout << BLUE << "\nCreating two arrays of different sizes... \n" << RESET << endl;

	// Creating two arrays of different sizes...

	Array <int> a(3);
	Array <int> b(5);

	cout << BLUE << "\nShowing the values of the arrays... \n" << RESET << endl;
	for (size_t i = 0; i < a.size(); i++) {
		cout << "a[" << i << "] = " << a[i] << endl;
	}
	for (size_t i = 0; i < b.size(); i++) {
		cout << "b[" << i << "] = " << b[i] << endl;
	}
	
	// Assigning values to the arrays...

	a[0] = 1;
	a[1] = 1;
	a[2] = 1;

	cout << BLUE << "\nAfter filling a with 1...\n" << RESET << endl;

	for (size_t i = 0; i < a.size(); i++) {
		cout << "a[" << i << "] = " << a[i] << endl;
	}
	for (size_t i = 0; i < b.size(); i++) {
		cout << "b[" << i << "] = " << b[i] << endl;
	}

	cout << BLUE << "\nAfter b = a ..." << RESET << endl;
	b = a;
	cout << "\n";

	for (size_t i = 0; i < a.size(); i++) {
		cout << "a[" << i << "] = " << a[i] << endl;
	}
	for (size_t i = 0; i < b.size(); i++) {
		cout << "b[" << i << "] = " << b[i] << endl;
	}

	cout << BLUE << "\nTry to access to empty array ...\n" << RESET << endl;

	Array<int> c;
	try {
		cout << a[a.size() + 1] << endl;
	} catch (std::exception &e) {
		cerr << RED << e.what() << RESET << endl;
	}

	return 0;

}