/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-13 16:21:28 by sternero          #+#    #+#             */
/*   Updated: 2025-01-13 16:21:28 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

#include <iostream>
#include <string>

class Harl { 

	public:

		Harl();
		void	complain(std::string severity);

	private:

		struct _handlers
		{
			std::string	severity;
			void	(Harl::*f)(void);
		};
		struct _handlers	handlers[4];
		void	debug(void);
		void	info(void);
		void	warning(void);
		void	error(void);

};

#endif