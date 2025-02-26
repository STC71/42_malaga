/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-22 16:49:18 by sternero          #+#    #+#             */
/*   Updated: 2025-02-22 16:49:18 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"


class EasyFindException : public std::exception {
	
	public:
	
	const char *what() const throw() {
		return "Error: Value not found in container 😡";
	}
};

#include "easyfind.tpp"

template <typename T>
bool easyfind(T &container, int toFind);
