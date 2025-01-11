/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-10 19:13:22 by sternero          #+#    #+#             */
/*   Updated: 2025-01-10 19:13:22 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void	randomChump(std::string name)
{
	Zombie other_zombie;
	other_zombie.setName(name);
	other_zombie.announce();
}

/*	This function creates a new Zombie object on the stack and sets its name 
	to the given string. It is used in the main.cpp file to create a new Zombie
	object. The difference between this function and newZombie is that this
	function creates the Zombie object on the stack, while newZombie creates it
	on the heap. It returns nothing.	*/