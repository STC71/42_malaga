/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-27 18:17:14 by sternero          #+#    #+#             */
/*   Updated: 2025-01-27 18:17:14 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

using std::cout;
using std::endl;

int	main() {

	ClapTrap	Bobby("Bobby");		// Create a ClapTrap object named "Bobby"

	Bobby.setAttackDamage(2);		// Set the attack damage of "Bobby" to 3
	cout << "\n* * * * * Bobby is ready to perform! * * * * *\n" << endl;
	cout << "Hit Points    : " << Bobby.getHitPoints() << endl;
	cout << "Energy Points : " << Bobby.getEnergyPoints() << endl;
	cout << "Attack Damage : " << Bobby.getAttackDamage() << endl;
	cout << "\nStatus        : OK" << endl;

	cout << "\n* * * * * *  Bobby's show begins   * * * * * *\n" << endl;
	Bobby.attack("Peter Pan");		// "Bobby" attacks "Peter Pan"
	Bobby.attack("Bambi");			// "Bobby" attacks "Bambi"

	cout << endl;
	Bobby.takeDamage(4);			// "Bobby" takes 4 points of damage
	Bobby.takeDamage(4);			// "Bobby" takes 4 points of damage

	Bobby.beRepaired(10);			// "Bobby" is repaired for 10 points
	cout << endl;

	Bobby.attack("Pinocho");		// "Bobby" attacks "Pinocho"
	Bobby.attack("Mulan");			// "Bobby" attacks "Mulan"
	Bobby.attack("Tarzan");			// "Bobby" attacks "Tarzan"
	Bobby.attack("Nemo");			// "Bobby" attacks "Nemo"

	cout << "\n* * * * * * * Bobby's show ends  * * * * * * *\n" << endl;

}
