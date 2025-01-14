/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-11 21:21:20 by sternero          #+#    #+#             */
/*   Updated: 2025-01-11 21:21:20 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

#include "Weapon.hpp"

class HumanA {

	public:

		HumanA(std::string name, Weapon &weapon);
		~HumanA(void);
		void	attack(void);

	private:

		std::string	_name;
		Weapon		_weapon;

};

#endif