/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-16 15:20:05 by sternero          #+#    #+#             */
/*   Updated: 2025-02-16 15:20:05 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serialization.hpp"

using std::cerr; using std::cout; using std::endl; 

int	main() {

	Data	*ptr;							// Declare a pointer to a Data struct
	Data	*ptrNew = NULL;					// Declare a pointer to a Data struct and initialize it to NULL

	ptr = new Data;							// Allocate memory for a Data struct
	ptr->str = "Up2u 🤗";					// Assign a value to the string member of the Data struct

	cout << "\n";
	cout << GREEN << "* * * Executing Serialization * * *\n" << RESET << endl;

	cout << "    Original ptr string: " << ptr->str << endl;	// Display the original string

	cout << "\n";

	cout << "     Original ptr : " << RED << ptr << RESET <<endl;		// Display the original pointer
	uintptr_t converted = serialize(ptr);								// Serialize the Data struct into a uintptr_t
	cout << "       Serielized : " << converted << endl;				// Display the converted value
	ptrNew = deserialize(converted);									// Deserialize the uintptr_t into a Data struct
	cout << "     Deserialized : " << RED << ptrNew << RESET << endl;	// Display the deserialized value
	cout << "\n";

	cout << "    And, new ptr string: " << ptrNew->str << endl;	// Display the new string

	cout << "\n";
	cout << GREEN << "* * *  Ending  Serialization  * * *\n" << RESET << endl;

	delete ptr;								// Free the memory allocated for the Data struct

}