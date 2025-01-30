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

#include "ScavTrap.hpp"

using std::cout;
using std::endl;

int main(){

	ScavTrap tmp("Damien");			// Create a temporary object of ScavTrap named "Damien"
	ScavTrap Damien("The child");

	tmp.setEnergyPoints(666);		// Set the energy points of the temporary object to 666
	Damien = tmp;					// Assign the temporary object to the object "Damien" to copy its data

	cout << "\n * * * * * * ScavTrap Damien * * * * * * " << endl;
	cout << "\n\tAttack damage : " << Damien.getAttackDamage();				// Get the attack damage of "Damien"
	cout << "\n\tEnergy points : " << Damien.getEnergyPoints();				// Get the energy points of "Damien"
	cout << "\n\tHit points    : " << Damien.getHitPoints() << endl;		// Get the hit points of "Damien"

	cout << "\n * * * * * *  Damien's games  * * * * * * " << endl << endl;

	Damien.attack("The hospital");			// "Damien" attacks "The hospital"
	cout << endl;
	Damien.attack("The nanny");				// "Damien" attacks "The nanny"

	cout << endl;

	Damien.takeDamage(6);					// "Damien" takes 6 points of damage
	Damien.takeDamage(6);					// "Damien" takes 6 points of damage
	Damien.beRepaired(6);					// "Damien" is repaired by 6 points

	cout << endl;

	Damien.attack("The priest");			// "Damien" attacks "Father Brennan"
	cout << endl;
	Damien.attack("The photographer");		// "Damien" attacks "The photographer"
	cout << endl;
	Damien.attack("The mother");			// "Damien" attacks "The mother"
	cout << endl;
	Damien.attack("The ambassador");		// "Damien" attacks "The ambassador"

	cout << endl;

	cout << "\n * * * * * * The Omen to be continued... * * * * * * " << endl << endl;
	Damien.guardGate();						// "Damien" enters in Gate Keeper Mode
	cout << "... And Damien will now be under the tutelage of the President..." << endl << endl;
}