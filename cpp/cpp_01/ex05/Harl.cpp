/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-13 16:21:15 by sternero          #+#    #+#             */
/*   Updated: 2025-01-13 16:21:15 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl()
{
	handlers[0].severity = "DEBUG";
	handlers[0].f = &Harl::debug;
	handlers[1].severity = "INFO";
	handlers[1].f = &Harl::info;
	handlers[2].severity = "WARNING";
	handlers[2].f = &Harl::warning;
	handlers[3].severity = "ERROR";
	handlers[3].f = &Harl::error;
}

void	Harl::debug(void) 
{
	std::cout << "[DEBUG] I love having extra bacon for my 7XL-double-cheese-triple-pickle-special ketchup burger. I really do!\n";
}

void	Harl::info(void) 
{
	std::cout << "[INFO] I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!\n";
}

void	Harl::warning(void) 
{
	std::cout << "[WARNING] I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month.\n";
}

void	Harl::error(void) 
{
	std::cout << "[ERROR] This is unacceptable! I want to speak to the manager now.\n";
}

void	Harl::complain(std::string severity)
{
	static int i = -1;
	if (i <= 3)
		severity == handlers[++i].severity ? (this->*handlers[i].f)() : complain(severity);
	i = -1;
}