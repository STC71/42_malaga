/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-11 21:21:41 by sternero          #+#    #+#             */
/*   Updated: 2025-01-11 21:21:41 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon) : _name(name), _weapon(weapon){
	return ;
}

HumanA::~HumanA(){
	return ;
}

void	HumanA::attack(void){
	std::cout << this->_name << " attacks with his " << this->_weapon.getType() << std::endl;
}