/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-13 20:34:42 by sternero          #+#    #+#             */
/*   Updated: 2025-01-13 20:34:42 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

using std::cerr;
using std::cout;
using std::endl;

int	main(int argc, char **argv)
{
	Harl harl;

	if (argc != 2 || !argv[1]) {
		cerr << ARGC_ERR << '\n';
		cerr << USAGE << endl;
		return 1;
	}
	harl.filterComplaint(argv[1]);
	return 0;
}