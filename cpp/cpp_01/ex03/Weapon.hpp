/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-11 21:20:22 by sternero          #+#    #+#             */
/*   Updated: 2025-01-11 21:20:22 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <iostream> // std::cout std::endl 
#include <string>

class Weapon{

	public:

		Weapon(std::string weaponType);
		~Weapon();

		std::string const	&getType();
		void				setType(std::string weaponType);
	
	private:

		std::string _type;
	
};

#endif