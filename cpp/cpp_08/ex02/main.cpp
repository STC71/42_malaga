/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-24 17:23:31 by sternero          #+#    #+#             */
/*   Updated: 2025-02-24 17:23:31 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <list>
#include <iostream>

// My test function to test the MutantStack with a stack and a list

template <typename Container>
void testContainer(Container &container) {
	container.push(5);									// Add the number 5 to the stack
	container.push(17);									// Add the number 17 to the stack
	std::cout << "Top element: " << container.top() << std::endl;	// Print the top of the stack (17)
	container.pop();									// Remove the top of the stack (17)
	std::cout << "Size: " << container.size() << std::endl;			// Print the size of the stack with only 1 element (1)
	container.push(3);									// Add the number 3 to the stack
	container.push(5);									// Add the number 5 to the stack
	container.push(737);								// Add the number 737 to the stack
	container.push(0);									// Add the number 0 to the stack

	typename Container::iterator it = container.begin();	// Create an iterator for the beginning of the stack
	typename Container::iterator ite = container.end();	// Create an iterator for the end of the stack
	++it;												// Move the iterator to the next element
	--it;												// Move the iterator to the previous element
	while (it != ite)									// Loop through the stack while the iterator is not at the end
	{
		std::cout << *it << std::endl;					// Print the element at the iterator
		++it;											// Move the iterator to the next element
	}
}

template <>
void testContainer(std::list<int> &container) {
	container.push_back(5);								// Add the number 5 to the stack 
	container.push_back(17);							// Add the number 17 to the stack
	std::cout << "Top element: " << container.back() << std::endl;	// Print the top of the stack (17)
	container.pop_back();								// Remove the top of the stack (17)
	std::cout << "Size: " << container.size() << std::endl;			// Print the size of the stack with only 1 element (1)
	container.push_back(3);								// Add the number 3 to the stack
	container.push_back(5);								// Add the number 5 to the stack
	container.push_back(737);							// Add the number 737 to the stack
	container.push_back(0);								// Add the number 0 to the stack

	std::list<int>::iterator it = container.begin();	// Create an iterator for the beginning of the stack
	std::list<int>::iterator ite = container.end();		// Create an iterator for the end of the stack
	++it;												// Move the iterator to the next element
	--it;												// Move the iterator to the previous element
	while (it != ite)									// Loop through the stack while the iterator is not at the end
	{
		std::cout << *it << std::endl;					// Print the element at the iterator
		++it;											// Move the iterator to the next element
	}
}

int	main() {
	cout << BLUE << "Testing MutantStack with stack" << RESET << endl;	// Print the title of the test
	MutantStack<int> mstack;							// Create an instance of MutantStack
	testContainer(mstack);								// Test the stack with the test function

	cout << BLUE << "Testing MutantStack with list" << RESET << endl;
	std::list<int> list;								// Create a list of integers to test the MutantStack
	testContainer(list);								// Test the list with the same function

	return 0;
}

// main for testing included in the subject.

// int main() {

// 	MutantStack<int> mstack;						// Create an instance of MutantStack

// 	mstack.push(5);									// Add the number 5 to the stack
// 	mstack.push(17);								// Add the number 17 to the stack

// 	std::cout << mstack.top() << std::endl;			// Print the top of the stack (17)
// 	mstack.pop();									// Remove the top of the stack (17)
// 	std::cout << mstack.size() << std::endl;		// Print the size of the stack with only 1 element (1)
// 	mstack.push(3);									// Add the number 3 to the stack
// 	mstack.push(5);									// Add the number 5 to the stack
// 	mstack.push(737);								// Add the number 737 to the stack
// 	//[...]
// 	mstack.push(0);									// Add the number 0 to the stack
// 	MutantStack<int>::iterator it = mstack.begin();	// Create an iterator for the beginning of the stack
// 	MutantStack<int>::iterator ite = mstack.end();	// Create an iterator for the end of the stack
// 	++it;											// Move the iterator to the next element
// 	--it;											// Move the iterator to the previous element
// 	while (it != ite)								// Loop through the stack while the iterator is not at the end
// 	{
// 		std::cout << *it << std::endl;				// Print the element at the iterator
// 		++it;										// Move the iterator to the next element
// 	}
// 	std::stack<int> s(mstack);						// Create a stack from the MutantStack to test the copy constructor
	
// 	return 0;
// }