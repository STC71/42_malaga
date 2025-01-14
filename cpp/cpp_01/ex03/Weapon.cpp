/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-11 21:20:40 by sternero          #+#    #+#             */
/*   Updated: 2025-01-11 21:20:40 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string weaponType){
	this->setType(weaponType);
	return ;
}

Weapon::~Weapon(void){
	return ;
}

std::string const &Weapon::getType(){
	return (this->_type);
}

void	Weapon::setType(std::string weaponType){
	this->_type = weaponType;
}