/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-29 10:30:34 by sternero          #+#    #+#             */
/*   Updated: 2025-01-29 10:30:34 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

using std::cout;
using std::endl;

FragTrap::FragTrap() : ClapTrap(){
	cout << "FragTrap default constructor called." << endl;
}	// default constructor

FragTrap::FragTrap(const std::string& name) : ClapTrap(name){
	cout << "FragTrap " << name << " has been created." << endl;
}	// parameterized constructor

FragTrap::FragTrap(const FragTrap& newFragTrap) : ClapTrap(newFragTrap){
	cout << "FragTrap copy constructor called." << endl;
}	// copy constructor

void FragTrap::highFivesGuys(void) const{
	cout << "FragTrap " << this->getName() << " says: Give me five!" << endl;
}	// high fives method

FragTrap::~FragTrap(){
	cout << "FragTrap " << this->getName() << " has been destroyed." << endl;
}	// destructor