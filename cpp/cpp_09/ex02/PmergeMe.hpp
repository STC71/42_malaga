/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 21:07:45 by sternero          #+#    #+#             */
/*   Updated: 2025-02-28 21:07:45 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>								// std::sort std::merge
#include <cstdlib>									// std::exit std::rand
#include <ctime>									// std::time std::clock
#include <exception>								// std::exception
#include <iostream>									// std::cerr std::cout std::endl
#include <list>										// std::list std::list::iterator
#include <sstream>									// std::stringstream
#include <string>									// std::string
#include <vector>									// std::vector

#define MICROSEC 1000000							// 1 second = 1,000,000 microseconds

#define BLUE "\033[1;34m"							// Blue color
#define GREEN "\033[1;32m"							// Green color
#define MAGENTA "\033[1;35m"						// Magenta color
#define RED "\033[1;31m"							// Red color
#define RESET "\033[0m"								// Reset color

class PmergeMe {

	public:

		PmergeMe();									// default constructor
		PmergeMe(const PmergeMe &src);				// copy constructor
		PmergeMe &operator=(const PmergeMe &src);	// assignation operator
		~PmergeMe();								// destructor

		void sortList(int argc, char *argv[]);		// sort the list
		void sortVector(int argc, char *argv[]);	// sort the vector

		class InvalidInput : public std::exception {		// InvalidInput exception class
			public:
				virtual const char *what() const throw();	// return the exception message
		};

};
