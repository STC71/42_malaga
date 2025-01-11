/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-10 19:12:50 by sternero          #+#    #+#             */
/*   Updated: 2025-01-10 19:12:50 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* newZombie(std::string name)
{
	Zombie* newZombie = new Zombie();
	newZombie->setName(name);
	return newZombie;
}

/*	This function creates a new Zombie object and sets its name to the given 
	string. It is used in the main.cpp file to create a new Zombie object.
	The difference between this function and randomChump is that this function
	creates the Zombie object on the heap, while randomChump creates it on the
	stack. It returns a pointer to the new Zombie object.	*/