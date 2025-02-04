/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 14:40:55 by sternero          #+#    #+#             */
/*   Updated: 2025-01-30 14:40:55 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

using std::cout;
using std::endl;

int main()
{
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	cout << "\n* * * * * * * Animals * * * * * * * " << endl;

	cout << endl;
	cout << "New type: " << j->getType() << endl;
	cout << "New Type: " << i->getType() << endl;

	cout << "\n* * * * * Animals sounds  * * * * * " << endl;
	cout << endl;
	i->makeSound(); 			//will output the cat sound!
	j->makeSound();				//will output the dog sound!
	meta->makeSound();			//will output the animal sound!

	cout << "\n* * * * Destroying animals  * * * * " << endl;
	cout << endl;
	delete meta;
	delete j;
	delete i;

	cout << "\n* * * * * Testing animals * * * * * " << endl;
	cout << endl;
	WrongAnimal	*wrongAnimal = new WrongAnimal;
	WrongAnimal	*wrongCat = new WrongCat;

	cout << "\n* * * wrongAnimal : ";

	wrongAnimal->makeSound();
	
	cout << "\n* * * wrongCat    : ";
	
	wrongCat->makeSound();

	cout << "\n* * * Destroying wrong animals * * * " << endl;
	cout << endl;
	delete wrongAnimal;
	delete wrongCat;
}