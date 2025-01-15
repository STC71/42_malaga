/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-13 20:34:16 by sternero          #+#    #+#             */
/*   Updated: 2025-01-13 20:34:16 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

using std::cout;
using std::endl;

Harl::Harl(void) {};
Harl::~Harl(void) {};

void	Harl::debug(void) {
	cout << "[ DEBUG ] " << endl;
	cout << DEBUG_MESSAGE << endl;
}

void	Harl::info(void) {
	cout << "[ INFO ] " << endl;
	cout << INFO_MESSAGE << endl;
}

void	Harl::warning(void) {
	cout << "[ WARNING ] " << endl;
	cout << WARNING_MESSAGE << endl;
}

void	Harl::error(void) {
	cout << "[ ERROR ] " << endl;
	cout << ERROR_MESSAGE << endl;
}

void	Harl::filterComplaint(std::string level){
	HarlLogFunction logFunctions[] = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	std::string logLevels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	for (int i = 0; i < 4; i++){
		if (level == logLevels[i]){
			switch (i){
				case 0:
					(this->*logFunctions[0])();
					(this->*logFunctions[1])();
					(this->*logFunctions[2])();
					(this->*logFunctions[3])();
					break;
				case 1:
					(this->*logFunctions[1])();
					(this->*logFunctions[2])();
					(this->*logFunctions[3])();
					break;
				case 2:
					(this->*logFunctions[2])();
					(this->*logFunctions[3])();
					break;
				case 3:
					(this->*logFunctions[3])();
					break;
				default:
					break;
			}
			return;
		}
	}
	cout << " [ Probably complaining about insignificant problems ] " << endl;
}


