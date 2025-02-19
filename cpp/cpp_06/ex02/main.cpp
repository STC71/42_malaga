/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-16 15:21:53 by sternero          #+#    #+#             */
/*   Updated: 2025-02-16 15:21:53 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <cstdlib>						// std::rand std::srand std::atoi ...
#include <iostream>						// std::cout ...

using std::cout; using std::endl;

Base *generate();			// Declare a function that returns a pointer to a Base instance
void identify(Base* p);		// Declare a function that takes a pointer to a Base instance as a parameter
void identify(Base& p);		// Declare a function that takes a reference to a Base instance as a parameter

int	main() {

	Base	*ptr;			// Declare a pointer to a Base instance

	cout << "\n* * * Executing Test * * *\n" << endl;

	ptr = generate();		// Generate a random Base instance

	cout << "\n";
	identify(ptr);			// Identify the Base instance with a pointer to it
	identify(*ptr);			// Identify the Base instance with a reference to it

	delete ptr;				// Free the memory allocated for the Base instance

	cout << "\n* * *  Ending  Test  * * *\n" << endl;

	return 0;

}	