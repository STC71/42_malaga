/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-20 17:38:56 by sternero          #+#    #+#             */
/*   Updated: 2025-02-20 17:38:56 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>								// size_t type definition ..
#include <iostream>								// cout, endl functions ..
#include <stdint.h>								// uint32_t type definition ..
#include <string>								// string type definition ..

#define GREEN "\033[0;32m"						// dark green color
#define RESET "\033[0m"							// reset color

template <typename T>
void addOne(T& x) { x++; }

template <typename T>
void print(const T& x) { std::cout << x << std::endl; }

// function iter overloading to handle const and non-const arrays ...

template <typename T>
void iter(T* array, size_t size, void (*f)(T&))	{
	for (size_t i = 0; i < size; i++)
		f(array[i]);
}

template <typename T>
void iter(const T* array, size_t size, void (*f)(const T&))	{
	for (size_t i = 0; i < size; i++)
		f(array[i]);
}
