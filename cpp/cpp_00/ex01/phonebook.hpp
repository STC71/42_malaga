/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-03 11:49:29 by sternero          #+#    #+#             */
/*   Updated: 2025-01-03 11:49:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iomanip>
# include <iostream>
# include <limits>
# include <string>

class Contact
{
	public:
	std::string		name;
	std::string		Last_name;
	std::string		Nick_name;
	std::string		secret;
	std::string		phone;

	void	display(void)
	{
		std::cout << name;
		std::cout << " : ";
		std::cout << phone << std::endl;
	}
};

class PhoneBook
{
	public:
	Contact Inputs[8];
	int		num;
};

#endif

/*	This header file (phonebook.hpp) defines two classes: Contact and PhoneBook.
	The first lines (#ifndef, #define, #endif) are an include guard that prevents
	the header file from being included more than once in the same source file.
	Inclusion of libraries: iostream, iomanip, and string.
	iostream: for standard input/output.
	iomanip: for formatting output.
	string: for using the class and for using text strings.
	The Contact class represents a contact in the phone book and has five public
	attributes: name, Last_name, Nick_name, secret, and phone.
	The display() method prints the name and phone number of the contact.
	The PhoneBook class represents the phone book and has two public attributes:
	Cons (an array of Contact) and num (the number of contacts in the phone book).
	Cons is an array of 8 Contact and num is an integer that indicates the number
	of contacts in the phone book. */