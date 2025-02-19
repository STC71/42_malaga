/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serialization.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-16 15:32:59 by sternero          #+#    #+#             */
/*   Updated: 2025-02-16 15:32:59 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serialization.hpp"

uintptr_t serialize(Data* ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}														// Serialize Data struct into a uintptr_t

Data* deserialize(uintptr_t converted) {
	return reinterpret_cast<Data*>(converted);
}														// Deserialize uintptr_t into a Data struct									
