/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-21 14:59:34 by sternero          #+#    #+#             */
/*   Updated: 2025-02-21 14:59:34 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>											// NULL
#include <exception>										// std::exception		
#include <iostream>											// std::cout std::endl
#include <stdint.h>											// uint32_t	
#include <string>											// std::string

#define BLUE "\033[1;34m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

using std::cout; using std::endl;

template <typename T>										// template type T
class Array
{
	
	public:

		Array();											// default constructor
		Array(uint32_t n);									// constructor with size
		Array(Array const &src);							// copy constructor
		Array& operator=(Array const &src);					// assignation operator
		T& operator[](uint32_t n) throw(std::exception);	// operator[] overload
		uint32_t size() const;									// return size of array
		~Array();											// destructor
	
		class OutOfLimits : public std::exception {			// exception class
			public:
			virtual const char* what() const throw();
	};

	private:
		T*			store;									// pointer to array
		uint32_t	storeLen;								// size of array
	
};

template <typename T>
Array<T>::Array() : store(new T[0]()), storeLen	(0) {
	cout << "Array - default constructor called" << endl;
}

template <typename T>
Array<T>::Array(uint32_t n) : store(new T[n]()), storeLen(n) {
	cout << "Array - parametric constructor called" << endl;
}

template <typename T>
Array<T>::Array(const Array &src) : store(new T[src.size()]()), storeLen(src.size()) {
	cout << "Array - copy constructor called" << endl;
	*this = src;
}

template <typename T>
Array<T>& Array<T>::operator=(Array const &src) {
	if (this != &src) {
		delete[] this->store;
		this->store = new T[src.storeLen]();
		this->storeLen = src.size();
		for (uint32_t i = 0; i < src.storeLen; i++)
			this->store[i] = src.store[i];
	}
	cout << "Array - assignation operator called" << endl;
	return *this;
}

template <typename T>
T& Array<T>::operator[](uint32_t n) throw(std::exception) {
	if (n >= this->storeLen)
		throw Array<T>::OutOfLimits();
	return this->store[n];
}															// operator[] overload

template <typename T>
uint32_t Array<T>::size() const {
	return this->storeLen;
}															// return size of array

template <typename T>
char const *Array<T>::OutOfLimits::what() const throw() {
	return "Error: Out of limits";
}

template <typename T>
Array<T>::~Array() {
	delete[] this->store;
	cout << "Array - destructor called" << endl;
}