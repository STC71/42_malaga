/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 20:10:37 by sternero          #+#    #+#             */
/*   Updated: 2025-02-26 20:10:37 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// default constructor
BitcoinExchange::BitcoinExchange() {}

// assignment operator
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src) {
	
	this->_bitcoinPrice = src._bitcoinPrice;	// assign src to this
	return *this;								// return this
	
}

// copy constructor
BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {
	
	*this = src;						// assign src to this
	
}

// ft_stof convert string to float
float	ft_stof(const std::string &str) {

	float n;							// float variable
	std::stringstream ss(str);			// create a stringstream object
	ss >> n;							// convert string to float
	return n;							// return float
	
}

// read data from file and store it in database map
float BitcoinExchange::getBitcoinPrice(const std::string date) {
	
	if (!isValidDate(date)) {
        //std::cerr << RED << "Invalid date: " << date << RESET << std::endl;
        return 1; //-1.0f; // Valor de error para indicar problema
    }

    if (this->_bitcoinPrice.count(date) > 0) {
        return this->_bitcoinPrice.at(date);
    }

    std::map<std::string, float>::iterator it = this->_bitcoinPrice.lower_bound(date);
    if (it == this->_bitcoinPrice.begin() && date < it->first) {
        std::cerr << RED << "No data available before " << it->first << RESET << std::endl;
        return -1.0f; // No hay datos anteriores
    }
    if (it == this->_bitcoinPrice.end()) {
        return (--it)->second; // Retorna el último valor disponible
    }
    return (--it)->second; // Retorna el valor de la fecha inmediatamente anterior
	
}

// try to read data from file, if file is empty or not found, print error message
bool BitcoinExchange::isDateFormatValid(const std::string &date) {

	if (date.empty()) {							// if date is empty
		std::cerr << DATE_ERR << "empty date" << std::endl;		// print error message
		return false;							// return false
	}
	return true;								// return true

}

// check if date is in the correct format and in the range of the database
bool BitcoinExchange::isValidDate(const std::string &date) {

	if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        std::cerr << RED << DATE_ERR << "\"" << date << "\"" << RESET << std::endl;
        return false;
    }

    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);

    // check if all parts are numeric
    for (size_t i = 0; i < yearStr.size(); ++i) {
        if (!isdigit(yearStr[i])) {
            std::cerr << RED << DATE_ERR << "\"" << date << "\"" << RESET << std::endl;
            return false;
        }
    }

	for (size_t i = 0; i < monthStr.size(); ++i) {
		if (!isdigit(monthStr[i])) {
			std::cerr << RED << DATE_ERR << "\"" << date << "\"" << RESET << std::endl;
			return false;
		}
	}

	for (size_t i = 0; i < dayStr.size(); ++i) {
		if (!isdigit(dayStr[i])) {
			std::cerr << RED << DATE_ERR << "\"" << date << "\"" << RESET << std::endl;
			return false;
		}
	}

    // Convert the parts to integers
	int year, month, day;
	std::stringstream(yearStr) >> year;
	std::stringstream(monthStr) >> month;
	std::stringstream(dayStr) >> day;

    // check if the year is in the range
	if (year < 2009) {
		std::cerr << RED << YEAR_ERR << year << RESET << std::endl;
		return false;
	}

    // check if the month is in the range
	if (month < 1 || month > 12) {
		std::cerr << RED << MONTH_ERR << month << RESET << std::endl;
		return false;
	}

    // check if the day is in the range
	if (day < 1 || day > 31
	|| (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11))
	|| (day > 29 && month == 2) || (day > 28 && month == 2 && (year % 4 != 0
	|| (year % 100 == 0 && year % 400 != 0)))) {
		std::cerr << RED << DAY_ERR << day << RESET << std::endl;
		return false;
	}

	return true;

}

// check if data is in the correct format and in the range
bool BitcoinExchange::isDataInRange(const std::string &data) {

	if (data.empty() || data.find_last_not_of("0123456789.-") != std::string::npos
	|| data.at(0) == '.' || data.find('.', data.length() - 1) != std::string::npos)
		std::cerr << RED << DATE_ERR << data << RESET << std::endl;
	else if (data.at(0) == '-')
		std::cerr << RED << POSITIVE_ERR << RESET << std::endl;
	else if (data.length() > 10 || (data.length() == 10 && data > "2147483647"))
		std::cerr << RED << LARGE_ERR << RESET << std::endl;
	else
		return true;
	return false;
}

// read data from file and store it in the database map
void BitcoinExchange::readData(std::ifstream &file) {

	std::string line;
    size_t pos;
	bool hasHeader = false;

	if (std::getline(file, line)) {
        // check if it is a header (contains "date", "value" or newline)
        if (line.find("date") != std::string::npos 
		|| line.find("value") != std::string::npos) {
            hasHeader = true;
        } else {
            pos = line.find(',');
            if (pos != std::string::npos) {
                std::string date = line.substr(0, pos);
                std::string valueStr = line.substr(pos + 1);
                if (isValidDate(date)) {
                    float value;
                    std::stringstream ss(valueStr);
                    if (ss >> value) {
                        this->_bitcoinPrice[date] = value;
                    } else {
                        std::cerr << "Invalid value in data: " << valueStr << std::endl;
                    }
                } else {
                    std::cerr << "Invalid date in data: " << date << std::endl;
                }
            } else {
                std::cerr << "Invalid line format: " << line << std::endl;
            }
        }
    }

    while (std::getline(file, line)) {
        pos = line.find(',');
        if (pos == std::string::npos) {
            std::cerr << "Invalid line format: " << line << std::endl;
            continue;
        }
        std::string date = line.substr(0, pos);
        std::string valueStr = line.substr(pos + 1);

        if (!isValidDate(date)) {
            std::cerr << "Invalid date in data: " << date << std::endl;
            continue;
        }

        float value;
        std::stringstream ss(valueStr);
        if (!(ss >> value)) {
            std::cerr << "Invalid value in data: " << valueStr << std::endl;
            continue;
        }

        this->_bitcoinPrice[date] = value;
    }
    file.close();

}

// destructor
BitcoinExchange::~BitcoinExchange() {}