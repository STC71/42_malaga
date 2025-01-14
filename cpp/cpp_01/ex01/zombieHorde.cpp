/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-11 17:23:47 by sternero          #+#    #+#             */
/*   Updated: 2025-01-11 17:23:47 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie	*zombieHorde(int N, std::string name){

	Zombie *str_zombie = new Zombie[N];

	for (int i = 0; i < N; i++)
		str_zombie[i].setName(name);
	return (str_zombie);
}
