/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-11 20:40:44 by sternero          #+#    #+#             */
/*   Updated: 2025-01-11 20:40:44 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <stdio.h>

int	main(void) {

	std::cout << std::endl;

	std::string str = "HI THIS IS BRAIN";
	std::string *ptr = &str;
	std::string &ref = str;

	std::cout << "🧠 Variable, pointer and reference initialized 🧠" << std::endl;

	std::cout << std::endl;
	std::cout << "🧠 Printing memory adress 🧠" << std::endl;
	std::cout << std::endl;

	std::cout << "Address of the string variable: " << &str << std::endl;
	std::cout << "Address held by the ptr pointer: " << ptr << std::endl; 
	std::cout << "Address held by the ref reference: " << &ref << std::endl;

	std::cout << std::endl;
	std::cout << "🧠 Printing values 🧠" << std::endl;
	std::cout << std::endl;

	std::cout << "Value of the string variable: " << str << std::endl;
	std::cout << "Value pointed to by the ptr pointer: " << *ptr << std::endl;
	std::cout << "Value pointed to by the ref reference: " << ref << std::endl;

	std::cout << std::endl;

	return (0);
}