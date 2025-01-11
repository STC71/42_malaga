/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-02 11:09:11 by sternero          #+#    #+#             */
/*   Updated: 2025-01-02 11:09:11 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

int main(int argc, char **argv)
{
    if (argc == 1)
	{
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
        return 0;
    }
	else
	{
		for (int i = 1; i < argc; ++i)
		{
			for (size_t j = 0; argv[i][j]; ++j)
			{
				std::cout << static_cast<char>(toupper(argv[i][j]));
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}
    return 0;
}

/*	Compiling with make and run with ./megaphone

	The program include two headers, iostream and cctype, to use the input/output
	stream and the function toupper respectively.

	The main function takes two arguments, the first one is the number of arguments
	passed to the program and the second one is an array of strings that contains
	the arguments.

	The first if statement checks if the number of arguments is equal to 1, if so,
	it prints the message "* LOUD AND UNBEARABLE FEEDBACK NOISE *" and returns 0.

	The else statement is executed if the number of arguments is greater than 1.
	It iterates over the arguments starting from the second one (index 1) and for
	each argument, it iterates over the characters of the string and prints the
	uppercase version of each character using the toupper function. After printing
	all the characters of the string, it prints a space character. Finally, it
	prints a newline character.

	std::cout is used to print the messages to the standard output stream.
	<< is the stream insertion operator used to insert the message into the stream.

	static_cast<char>(...)

		static_cast: This is an explicit type conversion. What it does here is
		take the result of the expression inside the parentheses and convert it to
		the char data type. This is necessary because the toupper function returns
		a value of type int.
		Why is it necessary to convert to char? Because std::cout expects a character
		to print it on the screen. By doing this conversion, we are ensuring that
		the value that is printed is a valid character.
		std::cout << " ";: Prints a space character after each word.

	std::endl is used to insert a newline character and flush the stream. */