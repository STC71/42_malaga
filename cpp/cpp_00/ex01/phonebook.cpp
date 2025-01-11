/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-03 11:47:54 by sternero          #+#    #+#             */
/*   Updated: 2025-01-03 11:47:54 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

void	putstr(std::string tmp)
{
	std::cout << "|";
	if (tmp.size() > 10)
	{
		tmp.resize(9);
		std::cout << tmp << ".";
	}
	else
		std::cout << std::setw(10) << tmp;
}

int	main(void)
{
	PhoneBook myPhoneBook;
	std::string	command;
	int	selector;
	myPhoneBook.num = 0;

	while (1)
	{
		std::cout << std::endl;
		std::cout << "| WRITE OPTION: | ADD | SEARCH | EXIT |" << std::endl;
		std::cout << std::endl;
		std::getline(std::cin, command);
		
		if (command == "ADD")
		{
			std::cout << std::endl;
			std::cout << "ADD New Contact"<< std::endl;

		if (myPhoneBook.num == 8)
		{
			for (int i = 7; i > 0; i--)
				myPhoneBook.Inputs[i] = myPhoneBook.Inputs[i - 1];
		}
		else
		{		
			for (int i = myPhoneBook.num - 1; i >= 0; i--)
    			myPhoneBook.Inputs[i+1] = myPhoneBook.Inputs[i];
		}

			std::cout << std::endl;
			std::cout << "First name: ";
			std::getline(std::cin, myPhoneBook.Inputs[0].name);
			if (std::cin.eof())
				break ;

			std::cout << "Last name of ";
			std::cout << myPhoneBook.Inputs[0].name;
			std::cout << ": ";
			std::getline(std::cin, myPhoneBook.Inputs[0].Last_name);
			if (std::cin.eof())
				break ;

			std::cout << "Nick name: ";
			std::cout << myPhoneBook.Inputs[0].name;
			std::cout << ": ";
			std::getline(std::cin, myPhoneBook.Inputs[0].Nick_name);
			if (std::cin.eof())
				break ;

			std::cout << "Phone number of ";
			std::cout << myPhoneBook.Inputs[0].name;
			std::cout << ": ";
			std::getline(std::cin, myPhoneBook.Inputs[0].phone);
			if (std::cin.eof())
				break ;

			std::cout << "Darkest secret of ";
			std::cout << myPhoneBook.Inputs[0].name;
			std::cout << ": ";
			std::getline(std::cin, myPhoneBook.Inputs[0].secret);
			if (std::cin.eof())
				break ;

			if (myPhoneBook.num < 8)
				myPhoneBook.num++;
			
			continue;
		}

		else if (command == "SEARCH")
		{
			std::cout << "  -------------------------------------------" << std::endl;
            std::cout << " |  Index   |   Name   |   Last   |   Nick   |" << std::endl;  
            std::cout << "  A-------------------------------------------" << std::endl;
            
			for (int i = 0; i < myPhoneBook.num; i++)
			{
				std::cout << " |";
                std::cout << std::setw(10) << i + 1;
				putstr(myPhoneBook.Inputs[i].name);
				putstr(myPhoneBook.Inputs[i].Last_name);
				putstr(myPhoneBook.Inputs[i].Nick_name);
				std::cout << "|" << std::endl;
			}
			std::cout << "  -------------------------------------------" << std::endl;
			std::cout << std::endl;
			std::cout << "Enter the index of the contact to display: ";
    		std::cin >> selector;
			if (std::cin.eof())
				break ;
			if (std::cin.fail())
   			{
				std::cout << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid selection" << std::endl;
				continue;
			}
    		std::cin.ignore();
    		selector--;

			if (selector >= 0 && selector < myPhoneBook.num)
			{
                std::cout << "First name: " << myPhoneBook.Inputs[selector].name << std::endl;
                std::cout << "Last name: " << myPhoneBook.Inputs[selector].Last_name << std::endl;
                std::cout << "Nickname: " << myPhoneBook.Inputs[selector].Nick_name << std::endl;
                std::cout << "Phone number: " << myPhoneBook.Inputs[selector].phone << std::endl;
                std::cout << "Darkest secret: " << myPhoneBook.Inputs[selector].secret << std::endl;
			}
			else
			{
				std::cout << "invalid selection" << std::endl;
				continue;
			}
		}
		else if (command == "EXIT" || std::cin.eof())
			break ;
		else
			std::cout << "Invalid command. Please enter ADD, SEARCH, or EXIT." << std::endl;
	}
}