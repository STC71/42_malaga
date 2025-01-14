/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-11 17:23:24 by sternero          #+#    #+#             */
/*   Updated: 2025-01-11 17:23:24 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::~Zombie(void){
	std::cout << "Zombie 🧟 " << this->getName() << " is dead 💤" << std::endl;
}

void Zombie::setName(std::string name){
	this->name = name;
}

const std::string& Zombie::getName(void) const{
	return (this->name);
}

void Zombie::announce(void){
	std::cout << this->getName() << " 🧟 " << " BraiiiiiiinnnzzzZ..." << std::endl;
}
