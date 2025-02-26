/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-23 11:29:17 by sternero          #+#    #+#             */
/*   Updated: 2025-02-23 11:29:17 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

// My test function to test the Span with a big range of numbers

int	main() {
	Span sp = Span(10000);												// Create an instance of Span with a max size of 10000

	std::vector<int> numbers;											// Create a vector of numbers
	for (int i = 0; i < 10000; i++)										// Loop through 10000 numbers
		numbers.push_back(i);											// Add the number to the vector
	
	sp.addNumbers(numbers.begin(), numbers.end());						// Add the range of numbers to the list
	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;	// Print the shortest span
	std::cout << "Longest span: " << sp.longestSpan() << std::endl;		// Print the longest span

	return 0;

}

// main for testing included in the subject.

// int main()
// {
// Span sp = Span(5);								// Create an instance of Span with a max size of 5
// sp.addNumber(6);									// Add the number 6
// sp.addNumber(3);									// ...
// sp.addNumber(17);
// sp.addNumber(9);
// sp.addNumber(11);
// std::cout << sp.shortestSpan() << std::endl;		// Print the shortest span
// std::cout << sp.longestSpan() << std::endl;		// Print the longest span
// return 0;
// }
