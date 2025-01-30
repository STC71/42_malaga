/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-28 17:35:52 by sternero          #+#    #+#             */
/*   Updated: 2025-01-28 17:35:52 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

using std::cout;
using std::endl;

int main(){

	DiamondTrap	Diamond("Damien");			// Create a DiamondTrap object named "Damien"

	cout << "\n * * * * * * DiamondTrap Damien * * * * * * " << endl;
	
	cout << endl;
	
	Diamond.attack("The priest");			// "Damien" attacks "The priest"
	Diamond.attack("The photographer");		// "Damien" attacks "The photographer"
	Diamond.attack("The mother");			// "Damien" attacks "The mother"

	cout << endl;

	Diamond.beRepaired(6);					// "Damien" is repaired by 6 points
	Diamond.takeDamage(66);					// "Damien" takes 66 points of damage
	Diamond.whoAmI();						// "Damien" is also known as "The child"
	Diamond.highFivesGuys();				// "Damien" says: Give me five!
	Diamond.guardGate();					// "Damien" enters in Gate Keeper Mode

}