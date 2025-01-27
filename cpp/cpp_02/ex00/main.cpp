/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-16 14:36:47 by sternero          #+#    #+#             */
/*   Updated: 2025-01-16 14:36:47 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int	main(void) {

	Fixed i;
	Fixed j(i);
	Fixed k;

	k = j;

	std::cout << i.getRawBits() << std::endl;
	std::cout << j.getRawBits() << std::endl;
	std::cout << k.getRawBits() << std::endl;

	return 0;
	
}