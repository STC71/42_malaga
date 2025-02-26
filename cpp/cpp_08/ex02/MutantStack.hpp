/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-24 17:24:24 by sternero          #+#    #+#             */
/*   Updated: 2025-02-24 17:24:24 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>									// to use rand()
#include <iostream>
#include <list>										// to use list
#include <stack>									// to use stack

# define BLUE "\033[34m"
# define GREEN "\033[32m"
# define RED "\033[31m"
# define RESET "\033[0m"

using std::cout; using std::endl;

template <typename T>											// Define a template for the stack
class MutantStack : public std::stack<T>						// Inherit from the stack
{
	public:

		typedef typename std::stack<T>::container_type::iterator iterator;	// Define the iterator type for the stack
		MutantStack();											// Constructor
		MutantStack(const MutantStack &src);					// Copy constructor
		MutantStack &operator=(const MutantStack &src);			// Copy assignment operator
		~MutantStack();											// Destructor

		iterator begin();										// Return the beginning of the stack
		iterator end();											// Return the end of the stack

};

template <typename T>
MutantStack<T>::MutantStack() {
	cout << "MutantStack "<< GREEN << "constructor" << RESET " called" << endl;
};

template <typename T>
MutantStack<T>::MutantStack(const MutantStack &src) {
	*this = src;
	cout << "MutantStack "<< GREEN << "copy constructor" << RESET " called" << endl;
};

template <typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack &src) {
	cout << "MutantStack "<< GREEN << "copy assignment operator" << RESET " called" << endl;
	std::stack<int>::operator=(src);			// Call the = operator from the stack
	return *this;								// Return the instance of the object
};

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() {
	return this->c.begin();
};												// Return the beginning of the stack	

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end() {
	return this->c.end();
};												// Return the end of the stack

template <typename T>
MutantStack<T>::~MutantStack() {
	cout << "MutantStack "<< RED << "destructor" << RESET " called" << endl;
};