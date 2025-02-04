/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 18:39:15 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 18:39:15 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

#define COUNT 4

using std::cout;
using std::endl;

int	main(){

	Animal	*animals[COUNT];					// array of animals to create

	cout << "\n* * * * * * Creating Animals's group * * * * * * \n" << endl;

	for (int i = 0; i < COUNT; i++)
	{
		if (i % 2 == 0)
			animals[i] = new Dog();				// creating a cat
		else
			animals[i] = new Cat();				// creating a dog
		cout << endl;
	}

	cout << "\n* * * * * * Deleting the Animals's group * * * * * * \n" << endl;

	for (int i = 0; i < COUNT; i++)
		delete animals[i];						// deleting the animals

	return 0;
}