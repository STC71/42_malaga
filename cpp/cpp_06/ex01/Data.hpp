/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-16 15:19:54 by sternero          #+#    #+#             */
/*   Updated: 2025-02-16 15:19:54 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>							// std::rand std::srand std::atoi ...
#include <iostream>							// std::cout ...
#include <stdint.h>							// uint32_t
#include <string>							// std::string

#define GREEN "\033[1;32m"					// Define the color dark green
#define RED "\033[1;31m"					// Define the color dark red
#define RESET "\033[0m"						// Define the color reset

typedef struct data {
	std::string str;
}	Data;

uintptr_t serialize(Data* ptr);				// Serialize Data struct into a uintptr_t
Data* deserialize(uintptr_t converted);		// Deserialize uintptr_t into a Data struct