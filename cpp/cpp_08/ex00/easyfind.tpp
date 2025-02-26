/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-22 16:58:16 by sternero          #+#    #+#             */
/*   Updated: 2025-02-22 16:58:16 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

template <typename T>
bool easyfind(T& container, int toFind) {

	if (std::find(container.begin(), container.end(), toFind) == container.end()) {
		throw EasyFindException();
		//return false;
	}
	else
		return true;
}