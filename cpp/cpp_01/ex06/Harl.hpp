/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-13 20:33:52 by sternero          #+#    #+#             */
/*   Updated: 2025-01-13 20:33:52 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

# include <cstdlib>
# include <iostream>
# include <string>

class Harl {
    public:
        Harl(void);
        ~Harl(void);

        void filterComplaint(std::string level);

    private:
        void debug(void);
        void info(void);
        void warning(void);
        void error(void);
};

typedef void (Harl::* HarlLogFunction) (void);

#define ARGC_ERR "Invalid arguments"
#define USAGE "Usage: ./harlFilter <level>\nlevels: DEBUG, INFO, WARNING, ERROR"

#define DEBUG_MESSAGE  "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!\n"
#define INFO_MESSAGE   "I cannot believe adding extra bacon costs more money.\nYou didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!\n"
#define WARNING_MESSAGE "I think I deserve to have some extra bacon for free.\nI've been coming for years whereas you started working here since last month.\n"
#define ERROR_MESSAGE   "This is unacceptable! I want to speak to the manager now.\n"

#endif