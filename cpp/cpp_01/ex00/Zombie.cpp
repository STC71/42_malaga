/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-10 19:12:31 by sternero          #+#    #+#             */
/*   Updated: 2025-01-10 19:12:31 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void	Zombie::announce(void) const{
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
	//std::cout << "<" << this->name << "> BraiiiiiiinnnzzzZ..." << std::endl;
}

const std::string&	Zombie::getName(void) const{
	return this->name;
}

void	Zombie::setName(std::string name){
	this->name = name;
}

Zombie::~Zombie(void){
	//std::cout << "<" << this->name << "> has been destroyed.💤" << std::endl;
	std::cout << this->name << " has been destroyed.💤" << std::endl;
}