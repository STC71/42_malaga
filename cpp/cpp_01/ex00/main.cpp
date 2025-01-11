/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-10 19:11:39 by sternero          #+#    #+#             */
/*   Updated: 2025-01-10 19:11:39 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void){

	std::string data;
	std::cout << "🧟 Enter the name of the stacked zombie: ";
	std::getline(std::cin, data);
	
	if (std::cin.eof() == true){
		std::cin.clear();
		clearerr(stdin);
		std::cout << "EOF detected, exiting program." << std::endl;
	}

	randomChump(data);

	std::cout << "🧟‍♀️ Enter the name of the heap zombie: ";
	std::getline(std::cin, data);
	
	if (std::cin.eof() == true){
		std::cin.clear();
		clearerr(stdin);
		std::cout << "EOF detected, exiting program." << std::endl;
	}

	Zombie* other_zombie = newZombie(data);

	delete other_zombie;

	return 0;

}
		