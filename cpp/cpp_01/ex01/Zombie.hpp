/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-11 17:23:20 by sternero          #+#    #+#             */
/*   Updated: 2025-01-11 17:23:20 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <cstdlib>
#include <iostream>
#include <string.h>
#include <stdio.h>

class Zombie {

	public:

                void setName(std::string name);

                const std::string& getName(void) const;

                void announce(void);
                
                ~Zombie(void);

	private:

		std::string name;
};

Zombie	*zombieHorde(int N, std::string name);

#endif