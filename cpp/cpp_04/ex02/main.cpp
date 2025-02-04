/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 09:27:15 by sternero          #+#    #+#             */
/*   Updated: 2025-01-31 09:27:15 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"

#define COUNT 4

using std::cout;
using std::endl;

int	main(){

	Animal	*animals[COUNT];					// array of animals to create
	Brain	*brain;								// brain to create

	cout << "\n* * * * * * Creating Animals's group * * * * * * \n" << endl;

	for (int i = 0; i < COUNT; i++)
	{
		if (i % 2 == 0)
			animals[i] = new Dog();				// creating a cat
		else
			animals[i] = new Cat();				// creating a dog
		cout << endl;
	}

	cout << "\n* * * Assigning ideas to the animals no: 3 * * * \n" << endl;

	brain = animals[3]->getBrain();						// getting the brain of the animal no: 3
	brain->addIdea("I hate the humans");				// adding an idea
	brain->addIdea("I hate the cats");					// adding an idea
	brain->addIdea("I hate the dogs");					// adding an idea
	brain->addIdea("I hate the animals in general");	// adding an idea

	cout << "The first idea of n. 3 was : " << brain->getIdea(0) << endl;

	cout << "\n* * * Copying the animal no: 3 to the animal no: 2 * * * \n";
	*(animals[2]) = *(animals[3]);						// copying the animal no: 3 to the animal no: 2
	*animals[2]->getBrain() = *animals[3]->getBrain();	// copying the brain of the animal no: 3 to the animal no: 2
	cout << "\nThe first idea of n. 2 is  : " << animals[2]->getBrain()->getIdea(0) << endl;

	cout << "\n*Assigning (copy) differents ideas to the animal n. 2 from n. 3\n";

	animals[2]->getBrain()->addIdea("The last of the n. 2");	// adding an idea to the animal no: 2
	cout << "The last idea of the animal n. 2 was: " << animals[2]->getBrain()->getIdea(4) << endl;
	animals[3]->getBrain()->addIdea("The last of the n. 3");	// adding an idea to the animal no: 3
	cout << "The last idea of the animal no. 3 was: " << animals[3]->getBrain()->getIdea(4) << endl;

	cout << "\n* * * * * Deleting the Animals's group * * * * * \n" << endl;

	for (int i = 0; i < COUNT; i++)
	{
		cout << animals[i] << " is going to be erased 🪦" << endl;
		delete animals[i];											// deleting the animals
		cout << endl;
	}

	return 0;

}