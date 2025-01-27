/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-16 14:36:11 by sternero          #+#    #+#             */
/*   Updated: 2025-01-16 14:36:11 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed {

	private:

		int					_rawBits;
		static const int	_fractionalBits = 8;

	public:

		Fixed();					// Default constructor
		Fixed(const Fixed &fix1);	// Copy constructor
		~Fixed();					// Destructor

		Fixed &operator = (const Fixed &fix2);	// Assignation operator

		int		getRawBits(void) const;
		void	setRawBits(int const raw);

};

#endif