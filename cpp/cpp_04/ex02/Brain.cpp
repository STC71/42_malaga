/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 09:26:09 by sternero          #+#    #+#             */
/*   Updated: 2025-01-31 09:26:09 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

using std::cout;
using std::endl;

Brain::Brain() {
	cout << "Brain constructor called 👷‍♂️" << endl;
	size = 0;
}														// default constructor

Brain::Brain(const Brain& src) {
	cout << "Brain copy constructor called 👷‍♀️" << endl;
	*this = src;
}														// copy constructor

Brain& Brain::operator=(const Brain& src) {
	cout << "\nBrain operator = called 🧠" << endl;
	for (int i = 0; i < 100; i++)
		this->_ideas[i] = src._ideas[i];
	this->size = src.size;
	return *this;
}														// operator overload =

Brain::~Brain() {
	cout << "Brain destructor called 💣" << endl;
}														// destructor

void Brain::addIdea(std::string idea) {
	if (size == 100)
		return;
	this->_ideas[size++] = idea;
}														// function to add an idea

const std::string& Brain::getIdea(unsigned int i) const {
	return this->_ideas[i];
}														// const function to get the idea