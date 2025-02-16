/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-05 12:41:35 by sternero          #+#    #+#             */
/*   Updated: 2025-02-05 12:41:35 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

using std::cout;			// cout to print
using std::endl;			// endl to print new line
using std::cerr;			// cerr to print errors

int main() {

	cout << "\n* * * * * * *  General Data  * * * * * * *\n" << endl; {

		Bureaucrat	a("Alice", 91);				// Constructor of Allice with grade 91
		Bureaucrat	b(a);						// Copy constructor of Allice to b
		Bureaucrat	c = b;						// Copy assignation operator of b to c

		cout << endl;

		cout << "a: " << a;						// Print a
		cout << "b: " << b;						// Print b
		cout << "c: " << c;						// Print c

		cout << endl;
	}

	cout << "\n* * * * * * Grade low and high * * * * * *\n" << endl; {

		try {
			Bureaucrat a("A", MIN_GRADE + 1);	// Value of grade is too low now
		} catch (std::exception &e) {
			cerr << e.what() << endl;			// Print the exception
		}

		try {
			Bureaucrat b("B", MAX_GRADE - 1);	// Value of grade is too high now
			cout << b;							// Print the bureaucrat
		} catch (std::exception &e) {
			cerr << e.what() << endl;			// Print the exception
		}

	}

	cout << "* * *  Bad Increment and Decrement   * * *\n" << endl; {

		try {
			Bureaucrat c("Chief", MAX_GRADE);	// Create a bureaucrat with the maximum grade
			cout << "Trying to increment the grade of " << c.getName() << endl;
			c.incrementGrade();					// Increment the grade of the bureaucrat
			cout << c;							// Print the bureaucrat
		} catch (std::exception &e) {
			cerr << e.what() << endl;			// Print the exception
		}

		try {
			Bureaucrat d("Dodo", MIN_GRADE);	// Create a bureaucrat with the minimum grade
			cout << "Trying to decrement the grade of " << d.getName() << endl;
			d.decrementGrade();					// Decrement the grade of the bureaucrat
			cout << d;							// Print the bureaucrat
		} catch (std::exception &e) {
			cerr << e.what() << endl;			// Print the exception
		}
	
	}

	cout << "* * * Possible operation with grade  * * *\n\n"; {

		try {
			Bureaucrat Donald("Donald", 9);		// Create a bureaucrat with the maximum grade
			Donald.incrementGrade();			// Increment the grade of the bureaucrat
			cout << "After increment 📈 ... " << Donald;
		} catch (std::exception &e) {
			cerr << e.what() << endl;			// Print the exception
		}

		cout << endl;

		try {
			Bureaucrat Joe("Joe", 149);			// Create a bureaucrat with the minimum grade
			Joe.decrementGrade();				// Decrement the grade of the bureaucrat
			cout << "After decrement 📉 ... " << Joe;
		} catch (std::exception &e) {
			cerr << e.what() << endl;			// Print the exception
		}
	
	}

	cout << "\n* * * * * * End of the program * * * * * *\n";

	return 0;

}