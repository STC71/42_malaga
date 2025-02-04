/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 09:25:56 by sternero          #+#    #+#             */
/*   Updated: 2025-01-31 09:25:56 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

class Brain {

	public:

		Brain();										// default constructor
		Brain(const Brain& src);						// copy constructor
		Brain& operator=(const Brain& src);				// operator overload =
		~Brain();										// destructor
		
		void addIdea(std::string idea);					// function to add an idea
		const std::string& getIdea(unsigned int i) const;	// const function to get the idea

	private:											// no protected because we don't need to access it from outside of the class

		unsigned int size;								// private unsigned int size
		std::string _ideas[100];							// private string ideas[100]

};