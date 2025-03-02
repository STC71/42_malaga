/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 20:35:50 by sternero          #+#    #+#             */
/*   Updated: 2025-02-26 20:35:50 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

using std::cout; using std::cerr; using std::endl;

float ft_stof(const std::string &str);						// convert string to float

static int evil(std::string error) {
	cerr << RED << error << RESET << endl;
	return EXIT_FAILURE;
}															// print an error message and return 1

int main(int argc, char *argv[]) {

	if (argc != 2)											// if the number of arguments is not 2
		return evil(BAD_ARG);

	cout << PURPLE << "\n";
	cout << "	⠀⠀⠀⠀⣿⡇⠀⢸⣿⡇⠀⠀⠀⠀" << endl;
	cout << "	⠸⠿⣿⣿⣿⡿⠿⠿⣿⣿⣿⣶⣄⠀" << endl;
	cout << "	⠀⠀⢸⣿⣿⡇⠀⠀⠀⠈⣿⣿⣿⠀" << endl;
	cout << "	⠀⠀⢸⣿⣿⡇⠀⠀⢀⣠⣿⣿⠟⠀" << endl;
	cout << "	⠀⠀⢸⣿⣿⡿⠿⠿⠿⣿⣿⣥⣄⠀" << endl;
	cout << "	⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⢻⣿⣿⣧" << endl;
	cout << "	⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⣼⣿⣿⣿" << endl;
	cout << "	⢰⣶⣿⣿⣿⣷⣶⣶⣾⣿⣿⠿⠛⠁" << endl;
	cout << "	⠀⠀⠀⠀⣿⡇⠀⢸⣿⡇⠀⠀⠀⠀" << RESET << "\n" << endl;

	std::ifstream file(argv[1], std::ifstream::in);			// create an ifstream object (ifstream is used to read file)
	if (!file.is_open())									// if the file is not open
		return evil(OPEN_ERR_FILE);

	std::ifstream internal_db(FILE, std::ifstream::in);		// create an ifstream object (ifstream is used to read file)
	if (!internal_db.is_open())								// if the file is not open
		return evil(OPEN_ERR_DB);
	
	BitcoinExchange btc;									// create a BitcoinExchange object
	btc.readData(internal_db);								// read data from file

	std::string line;										// create a string object
	std::getline(file, line);								// get a line from file

	while (std::getline(file, line)) {						// while there is a line in the file

		size_t limit = line.find_first_of("|");				// find the first occurrence of '|'

		if (limit == std::string::npos || line.length() < limit +2) {	// if the limit is not found or the line is too short
			cerr << RED << INPUT_ERR << line << RESET << endl;			// print an error message
			continue;													// continue to the next iteration			
		}

		std::string date = line.substr(0, limit - 1);		// get the date from the line
		if (!btc.isDateFormatValid(date)					// if the date format is not valid
			|| !btc.isDataInRange(date))					// or the date is not in range
			continue;										// continue to the next iteration

		std::string buys_as_str = line.substr(limit + 2);	// get the buys from the line
		if (!btc.isDataInRange(buys_as_str))				// if the buys is not in range
			continue;										// continue to the next iteration
		float buys = ft_stof(buys_as_str);					// convert the buys to float
		
		if (buys < 0 || buys > 1000) {							// if the buys is greater than 1000
			cerr << RED << BUYS_ERR << buys << RESET << endl;	// print an error message
			continue;											// continue to the next iteration
		}

		if (btc.getBitcoinPrice(date) != 1)						// if the date is not valid
			cout << BLUE << date << RESET << " => " << GREEN << buys << RESET << " = "
			<< std::fixed << std::setprecision(2) << GREEN << buys * btc.getBitcoinPrice(date) 
			<< RESET << endl;									// print the date, buys and the bitcoin price

	}

	file.close();											// close the file
	internal_db.close();									// close the internal database

	return EXIT_SUCCESS;									// return 0

}