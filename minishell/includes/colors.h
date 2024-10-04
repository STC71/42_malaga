/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-02 11:01:12 by sternero          #+#    #+#             */
/*   Updated: 2024-07-02 11:01:12 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// To reset the color of the text to the default color (white):

# define RESET		"\033[0m"    // expample: printf(RESET "Hello World\n");

// To print the texts in diferent colors:

# define RED		"\033[0;31m" // expample: printf(RED "Hello World\n");
# define GREEN		"\033[0;32m" // expample: @echo -e "$(GREEN)Hello World"
# define YELLOW		"\033[0;33m" 
# define BLUE		"\033[0;34m" 
# define MAGENTA	"\033[0;35m" 
# define CYAN		"\033[0;36m" 
# define WHITE		"\033[0;37m"
# define ORANGE 	"\033[1;31m"
# define NC         "\033[31;1m" // No Color

// To print the bold texts in diferent colors:

# define BDBLACK 	"\033[1;30m" // expample: printf(BDBLACK "Hello World\n");
# define BDRED 		"\033[1;31m" // expample: @echo -e "$(BDRED)Hello World"
# define BDGREEN 	"\033[1;32m"
# define BDYELLOW 	"\033[1;33m"
# define BDBLUE 	"\033[1;34m"
# define BDMAGENTA 	"\033[1;35m"
# define BDCYAN 	"\033[1;36m"
# define BDWHITE 	"\033[1;37m"

// To print the underlined texts in diferent colors:

# define ULRED 		"\033[4;31m" // expample: printf(ULRED "Hello World\n");
# define ULGREEN 	"\033[4;32m" // expample: @echo -e "$(ULGREEN)Hello World"
# define ULYELLOW 	"\033[4;33m"
# define ULBLUE 	"\033[4;34m"
# define ULMAGENTA 	"\033[4;35m"
# define ULCYAN 	"\033[4;36m"
# define ULWHITE 	"\033[4;37m"

// To print lines, shades, blocks and arrows:

# define EQLIN 		"\u2550" // EQUAL LINE     ═══════════════════
# define LSHADE 	"\u2591" // LIGHT SHADE    ░░░░░░░░░░░░░░░░░░░
# define MSHADE 	"\u2592" // MEDIUM SHADE   ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
# define HSHADE 	"\u2593" // HEAVY SHADE    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
# define FBLOCK 	"\u2588" // FULL BLOCK     ███████████████████
# define EBLOCK 	"\u258d" // EIGHTH BLOCK   ▍▍▍▍▍▍▍▍▍▍▍▍▍▍▍▍▍▍▍
# define ARROWRG 	"\u2911" // RIGHT ARROW    ⤑⤑⤑⤑⤑⤑⤑⤑⤑⤑⤑⤑⤑⤑

#endif
