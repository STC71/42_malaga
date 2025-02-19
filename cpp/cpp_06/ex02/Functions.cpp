/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Functions.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-16 15:36:20 by sternero          #+#    #+#             */
/*   Updated: 2025-02-16 15:36:20 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>							// std::rand std::srand std::atoi ...
#include <iostream>							// std::cout ...

using std::cerr; using std::cout; using std::endl;

Base *generate() {

	srand(time(NULL));						// Seed the random number generator
	char s = "ABC"[rand() % 3];				// Generate a random character from the string "ABC".
	cout << "Type: " << s << ", aleatorily generated 🎰" << endl;
	switch (s) {
		case 'A':
			return new A;					// Return a pointer to a new instance of A
		case 'B':
			return new B;					// Return a pointer to a new instance of B
		case 'C':
			return new C;					// Return a pointer to a new instance of C
	}
	return NULL;							// Return NULL if the random character is not A, B, or C
}

void identify(Base* p) {

	bool casted;

	cout << "Identify with Base: *";

	casted = dynamic_cast<A *>(p);			// Cast the pointer to A
	if (casted) {
		cout << "A" << endl;				// If the cast is successful, display A
		return;
	}
	casted = dynamic_cast<B *>(p);			// Cast the pointer to B
	if (casted) {
		cout << "B" << endl;				// If the cast is successful, display B
		return;
	}
	casted = dynamic_cast<C *>(p);			// Cast the pointer to C
	if (casted) {
		cout << "C" << endl;				// If the cast is successful, display C
		return;
	}
	if (!casted) {
		cout << "Unknown" << endl;			// If the cast is not successful, display Unknown
	}
	
}

void identify(Base& p) {

	cout << "Identify with Base: &";

	try {
		A &a = dynamic_cast<A &>(p);		// Cast the reference to A
		(void)a;							// Avoid unused variable warning
		cout << "A" << endl;				// If the cast is successful, display A
	} catch (const std::exception &e) {
		try {
			B &b = dynamic_cast<B &>(p);	// Cast the reference to B
			(void)b;						// Avoid unused variable warning
			cout << "B" << endl;			// If the cast is successful, display B
		} catch (const std::exception &e) {
			try {
				C &c = dynamic_cast<C &>(p);// Cast the reference to C
				(void)c;					// Avoid unused variable warning
				cout << "C" << endl;		// If the cast is successful, display C
			} catch (const std::exception &e) {
				cout << "Unknown" << endl;	// If the cast is not successful, display Unknown
			}
		}
	}
}