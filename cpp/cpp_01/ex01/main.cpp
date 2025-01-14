/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-11 17:22:14 by sternero          #+#    #+#             */
/*   Updated: 2025-01-11 17:22:14 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void){

	std::string zombies_name;
	int nbr_zombies;

	while(1) {
		
		std::cout << "Enter the name of zombies 🧟 : ";
		getline(std::cin, zombies_name);
		
		if (std::cin.eof() == true) {
			std::cin.clear();
			clearerr(stdin);
			std::cout << std::endl;
		}

		if (!zombies_name.empty())
			break;
		std::cout << "Please enter a valid name 🧟 :" << std::endl;
	}

	std::cout << "🧟 Enter the number of zombies: ";
	std::cin >> nbr_zombies;
	Zombie	*zombies_war = zombieHorde(nbr_zombies, zombies_name);

	for (int i = 0; i < nbr_zombies; i++)
		zombies_war[i].announce();
	delete [] zombies_war;
	return (0);
}