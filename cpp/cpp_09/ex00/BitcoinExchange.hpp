/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 20:10:06 by sternero          #+#    #+#             */
/*   Updated: 2025-02-26 20:10:06 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>							// to use exit, EXIT_FAILURE, EXIT_SUCCESS
#include <fstream>							// to read file, ifstream and ofstream
#include <iomanip>							// to setprecision and fixed
#include <iostream>							// to use cout, cin, cerr
#include <map>								// to use map container
#include <sstream>							// to use stringstream to convert string to double
#include <string>							// to use string

#define BLUE "\033[0;34m"					// blue color
#define GREEN "\033[0;32m"					// dark green color
#define PURPLE "\033[0;35m"					// purple color
#define RED "\033[0;31m"					// red color
#define RESET "\033[0m"						// reset color

#define FILE "./data.csv"					// Data base file

// message error define 
#define DATE_ERR "Error: incorrect data => "
#define YEAR_ERR "Error: year is not at the database => "
#define MONTH_ERR "Error: incorrect month => "
#define DAY_ERR "Error: incorrect day => "
#define BUYS_ERR "Error: invalid acquisition => "
#define POSITIVE_ERR "Error: not a positive number."
#define LARGE_ERR "Error: too large number."

#define BAD_ARG "Error: bad number of arguments"
#define INPUT_ERR "Error: bad input => "
#define OPEN_ERR_FILE "Error: could not open file"
#define OPEN_ERR_DB "Error: cannot open database"

class BitcoinExchange {

	public:
		BitcoinExchange();									// default constructor	
		BitcoinExchange(const BitcoinExchange &src);		// copy constructor
		~BitcoinExchange();									// destructor

		BitcoinExchange &operator=(const BitcoinExchange &src);	// assignment operator

		void readData(std::ifstream &file);					// read data from file
		float getBitcoinPrice(const std::string date);		// get bitcoin price from date
		bool isDateFormatValid(const std::string &date);	// check if date is valid
		bool isValidDate(const std::string &date);			// check if date is valid
		bool isDataInRange(const std::string &rate);		// check if date is in range

	private:

		std::map<std::string, float> _bitcoinPrice;			// map to store bitcoin price

};