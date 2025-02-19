/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-16 15:31:53 by sternero          #+#    #+#             */
/*   Updated: 2025-02-16 15:31:53 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

using std::cout; using std::endl; using std::cerr;

static int ft_atoi(const std::string &str) {		// Function to convert a string to an integer
	char *end;										// Initialize a pointer to store the end of the string
	errno = 0;										// Initialize errno to 0
	long i = std::strtol(str.c_str(), &end, 10);	// Convert the string to an integer
	if (*end != '\0' || errno == ERANGE || i < std::numeric_limits<int>::min() 
	|| i > std::numeric_limits<int>::max()) {
		cerr << RED << "Error" << RESET << ": out of range !!!" << endl;	// Print an error message
		exit (1);									// If the conversion failed, exit the program
		//return 0;									// If the conversion failed, return 0
	}
	return static_cast<int>(i);						// Return the integer	
}

static float ft_atof(const std::string &str) {		// Function to convert a string to a float
	char *end;										// Initialize a pointer to store the end of the string
	errno = 0;										// Initialize errno to 0
	float f = std::strtof(str.c_str(), &end);		// Convert the string to a float
	if (*end != 'f' || errno == ERANGE) {
		cerr << RED << "Error" << RESET << ": out of range !!!" << endl;	// Print an error message
		return 0.0f;								// If the conversion failed, return 0.0f
	}
	return f;										// Return the float
}

static double ft_atod(const std::string &str) {		// Function to convert a string to a double
	char *end;										// Initialize a pointer to store the end of the string
	errno = 0;										// Initialize errno to 0
	double d = std::strtod(str.c_str(), &end);		// Convert the string to a double
	if (*end != '\0' || errno == ERANGE ) {
		cerr << RED << "Error" << RESET << ": out of range !!!" << endl;	// Print an error message
		return 0.0;									// If the conversion failed, return 0.0
	}
	return d;										// Return the double
}

enum Type { 
	ERROR,											// The value is not a valid type. For example, a string that is not a number.
	PSEUDO,											// The value is a pseudo value. For example, a string that is a number but not a valid type.
	CHAR, 											// The value is a char. For example, 'a'.
	INT, 											// The value is an integer. For example, 42.
	FLOAT, 											// The value is a float. For example, 42.42f.
	DOUBLE,											// The value is a double. For example, 42.42.
};													// Enumeration to store the type of the value to convert

static bool isChar(const std::string &input) {		// Function to check if the string is a char
	if (input.length() != 1)						// If the string has more than one character
		return false;								// Return false
	if (input.at(0) < std::numeric_limits<char>::min() 
	|| input.at(0) > std::numeric_limits<char>::max()
	|| isdigit(input.at(0)))
		return false;								// If the character is not in the range of a char
	return true;									// Return true if the string is a char
}

static bool isInt(const std::string &input) {		// Function to check if the string is an integer
	for (size_t i = input.at(0) == '-' 
	? 1 : 0; i < input.length(); i++) {				// Iterate over the string
		if (!isdigit(input.at(i)))					// If a character is not a digit
			return false;							// Return false
	}
	return true;									// Return true if the string is an integer
}

static bool isFloat(const std::string &input) {			// Function to check if the string is a float
	bool point = false;									// Initialize a boolean to store if the point has been found
	if (input == "-inff" || input == "+inff" || input == "nanf")
		return true;									// Return true if the string is a pseudo float
	if (input.at(input.length() - 1) != 'f')			// If the last character is not 'f'
		return false;									// Return false
	for (size_t i = 0; i < input.length() - 1; i++) {	// Iterate over the string
		if (input.at(i) == '.' && point)				// If a point is found and it is not the first one
			return false;								// Return false
		else if (input.at(i) == '.') {
			point = true;								// Set the point to true
			continue;									// Continue to the next iteration
		}
		if (!isdigit(input.at(i)) && input.at(i) != '-' && input.at(i) != '+')	// If a character is not a digit, a minus or a plus
			return false;								// Return false
	}
	return true;										// Return true if the string is a float
}

static bool isDouble(const std::string &input) {		// Function to check if the string is a double
	bool point = false;									// Initialize a boolean to store if the point has been found
	if (input == "-inf" || input == "+inf" || input == "nan")
		return true;									// Return true if the string is a pseudo double
	for (size_t i = 0; i < input.length(); i++) {		// Iterate over the string
		if (input.at(i) == '.' && point)				// If a point is found and it is not the first one
			return false;								// Return false
		else if (input.at(i) == '.') {
			point = true;								// Set the point to true
			continue;									// Continue to the next iteration
		}
		if (!isdigit(input.at(i)) && input.at(i) != '-' && input.at(i) != '+')	// If a character is not a digit, a minus or a plus
			return false;								// Return false
	}
	return true;										// Return true if the string is a double
}

static bool isPseudo(const std::string &input) {		// Function to check if the string is a pseudo value
	return (input == "-inff" || input == "+inff" || input == "nanf"
	|| input == "-inf" || input == "+inf" || input == "nan");	// Return true if the string is a pseudo value
}

static Type getType(const std::string &input) {						// Function to get the type of the value
	if (isChar(input))												// If the string is a char
		return CHAR;												// Return the type char
	if (isInt(input))												// If the string is an integer
		return INT;													// Return the type int
	if (isFloat(input))												// If the string is a float
		return FLOAT;												// Return the type float
	if (isDouble(input))											// If the string is a double
		return DOUBLE;												// Return the type double
	return ERROR;													// Return the type error
}

static void printChar(char c) {										// Function to print a char
	cout << "char: '" << c << "'" << endl;							// Print the char
	cout << "int: " << static_cast<int>(c) << endl;					// Print the int
	cout << "float: " << static_cast<float>(c) << ".0f" << endl;	// Print the float
	cout << "double: " << static_cast<double>(c) << ".0" << endl;	// Print the double
}

static void printInt(int i) {
	if (i >= std::numeric_limits<char>::min() && i <= std::numeric_limits<char>::max()
	&& isprint(static_cast<unsigned char>(i)))						// If the int is printable
		cout << "char: '" << static_cast<char>(i) << "'" << endl;	// Print the char
	//if (isprint(static_cast<unsigned char>(i)))						// If the int is printable
	//	cout << "char: '" << static_cast<char>(i) << "'" << endl;	// Print the char
	else
		cout << "char: Non displayable" << endl;					// Print that the char is not displayable
	cout << "int: " << i << endl;									// Print the int
	cout << "float: " << static_cast<float>(i) << ".0f" << endl;	// Print the float
	cout << "double: " << static_cast<double>(i) << ".0" << endl;	// Print the double
}

static void printFloat(float f) {									// Function to print a float
	if (f <= std::numeric_limits<char>::min()
	|| f >= std::numeric_limits<char>::max()) {
		cerr << RED << "Error" << RESET << ": out of range !!!" << endl;	// Print an error message
		exit (1);															
	}
	else {
		if (isprint(f))													// If the float is printable
			cout << "char: '" << static_cast<char>(f) << "'" << endl;	// Print the char
		else
			cout << "char: Non displayable" << endl;					// Print that the char is not displayable
		cout << "int: " << static_cast<int>(f) << endl;					// Print the int
		cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << endl;	// Print the float
		cout << "double: " << static_cast<double>(f) << endl;			// Print the double
	}
}

static void printDouble(double d) {											// Function to print a double
	if (d <= std::numeric_limits<char>::min() 
	|| d >= std::numeric_limits<char>::max()) {
		cerr << RED << "Error" << RESET << ": out of range !!!" << endl;	// Print an error message
		exit (1);
	}
	else {
		if (isprint(d))													// If the double is printable
			cout << "char: '" << static_cast<char>(d) << "'" << endl;	// Print the char
		else
			cout << "char: Non displayable" << endl;					// Print that the char is not displayable
		cout << "int: " << static_cast<int>(d) << endl;					// Print the int
		cout << "float: " << static_cast<float>(d) << std::setprecision(1) << "f" << endl;		// Print the float
		cout << "double: " << std::fixed << std::setprecision(1) << d << endl;		// Print the double
	}
}

static void pseudo(Type destType, const std::string &pseudoInput) {			// Function to convert a pseudo value
	cout << "char: impossible" << endl;										// Print that it is impossible to convert to char
	cout << "int: impossible" << endl;										// Print that it is impossible to convert to int
	if (destType == FLOAT) {												// If the destination type is float
		cout << "float: " << pseudoInput << endl;							// Print the float
		cout << "double: " << pseudoInput.substr(0, pseudoInput.length() - 1) << endl;	// Print the double
	}
	else if (destType == DOUBLE) {											// If the destination type is double
		cout << "float: " << pseudoInput << "f" << endl;					// Print the float
		cout << "double: " << pseudoInput << endl;							// Print the double
	}
}

void ScalarConverter::convert(const std::string &input) {			// Function to convert a value
	switch (getType(input)) {										// Switch the type of the value
		case CHAR:													// If the value is a char
			printChar(input.at(0));									// Print the char
			break;
		case INT:													// If the value is an int
			printInt(ft_atoi(input));								// Print the int
			break;
		case FLOAT:													// If the value is a float
			if (isPseudo(input))									// If the value is a pseudo float
				pseudo(FLOAT, input);								// Convert the pseudo float
			else
				printFloat(ft_atof(input));							// Print the float
			break;
		case DOUBLE:												// If the value is a double
			if (isPseudo(input))									// If the value is a pseudo double
				pseudo(DOUBLE, input);								// Convert the pseudo double
			else
				printDouble(ft_atod(input));						// Print the double
			break;
		default:
			cout << RED << "Error" << RESET << ": invalid input" << endl;		// Print an error message
			break;
	}
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) {	// Assignment operator (does nothing)
	return *this;
}

ScalarConverter::~ScalarConverter() {}									// Destructor (does nothing)
