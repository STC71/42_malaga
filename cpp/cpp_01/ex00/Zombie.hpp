/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-10 19:12:08 by sternero          #+#    #+#             */
/*   Updated: 2025-01-10 19:12:08 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>

class Zombie{

	public:

		void	announce(void) const;
		const std::string&	getName(void) const;
		void	setName(std::string name);

		~Zombie(void);

	private:

		std::string	name;
};

void 	randomChump(std::string name);
Zombie* newZombie(std::string name);

#endif