/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 16:35:14 by sternero          #+#    #+#             */
/*   Updated: 2025-02-07 16:35:14 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

using std::cerr;
using std::cout;
using std::endl;

int main() {

	const std::string blue = "\033[1;34m";
	const std::string reset = "\033[0m";

	cout << "\n* * * *  📜 Welcome to the Bureaucrat and Form test 📜  * * * *" << endl;

	cout << blue <<"\nSomeone has had the happy idea of ​​creating a form that requires" << endl;
	cout << "a grade 0 signature.\n" << reset << endl; {
		try {
			Form f("AJ066", 0, 66);		// Create a form with grade to sign and execute 0
		} catch (std::exception &e) {
			cerr << e.what() << endl;	// Print the exception
		}
	}

	cout << blue <<"\nNow another enlightened one, has gone further with another form" << endl;
	cout << "that requires a degree of execution 0\n" << reset << endl; {
		try {
			Form f("BF007", 66, 0);		// Create a form with grade to sign and execute 0
		} catch (std::exception &e) {
			cerr << e.what() << endl;	// Print the exception
		}
	}

	cout << blue <<"\nTo correct the first error.. a new form has been published that" << endl;
	cout << "requires a grade 151 signature.\n" << reset << endl; {
		try {
			Form f("AJ066N", 151, 66);		// Create a form with grade to sign and execute 0
		} catch (std::exception &e) {
			cerr << e.what() << endl;	// Print the exception
		}
	}

	cout << blue <<"\nThis measure hasn't come alone, now the second measure requires" << endl;
	cout << "execution 151.\n" << reset << endl; {
		try {
			Form B("BF007N", 151, 0);		// Create a form with grade to sign and execute 0
		} catch (std::exception &e) {
			cerr << e.what() << endl;	// Print the exception
		}
	}

	cout << blue <<"\nIt seems that a form has been created with a correct grade: 50." << endl;
	cout << "It has been handed over to a grade 100 bureaucrat for signature.\n" << reset << endl; {
        try {
            Form f("CF123", 50, 50);		// Create a form with grade to sign and execute 50
            Bureaucrat b("John Doe", 100);	// Create a bureaucrat with grade 100
            cout << f << endl;
            cout << b << endl;
            f.beSigned(b);					// Attempt to sign the form
        } catch (std::exception &e) {
            cerr << e.what() << endl;	// Print the exception
        }
    }

	cout << blue <<"\nNow let's create a form that requires a grade 50 execution and" << endl;
	cout << "a bureaucrat with grade 100.\n" << reset << endl; {
        try {
            Form f("CF456", 50, 50);		// Create a form with grade to sign and execute 50
            Bureaucrat b("Jane Doe", 100);	// Create a bureaucrat with grade 100
            cout << f << endl;
            cout << b << endl;
            f.beSigned(b);					// Attempt to sign the form
            // Attempt to execute the form
            cout << "Attempting to execute the form..." << endl;
            if (b.getGrade() > f.getGradeToExecute()) {
                throw Form::GradeTooLowException();
            } else {
                cout << "Form executed successfully." << endl;
            }
        } catch (std::exception &e) {
            cerr << e.what() << endl;	// Print the exception
        }
    }

	return 0;

}