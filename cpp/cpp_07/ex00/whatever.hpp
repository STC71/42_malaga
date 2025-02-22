/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-19 20:57:01 by sternero          #+#    #+#             */
/*   Updated: 2025-02-19 20:57:01 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once							// include guard

template <typename T>					// template for swap
void	swap(T &a, T &b) {				// swap two values
	T tmp = a;							// store a in tmp
	a = b;								// a becomes b
	b = tmp;							// b becomes tmp
}										// result: a = b, b = a

template <typename T>					// template for min
T		min(T a, T b) {					// return the smallest value
	return (a < b ? a : b);				// if a < b, return a, else return b 
}										// (? = if, : = else - ternary operator)

template <typename T>					// template for max
T		max(T a, T b) {					// return the biggest value
	return (a > b ? a : b);				// if a > b, return a, else return b
}

/*	Template <typename T> represents a template of type T, which can be used
	for any type of data. In this case, it is used for the functions swap, min
	and max, which can be used with any type of data. This is called "generic
	programming" and is one of the most powerful features of C++. In this case,
	it is used to swap two values, return the smallest of two values and return
	the biggest of two values.
	Why is template used? Whith this we are seying to the compiler that we are
	going to use a generic type T, so the compiler will generate the code for
	each type of data that is used with the template. This allows you to write
	code that can be reused with any type of data.
	why is typename used? Whith this we are seying to the compiler that T is a
	type name. This is necessary when using templates, since the compiler needs
	to know that T is a type name and not a variable name. This is necessary when
	using templates, since the compiler needs to know that T is a type name and
	not a variable name. This is necessary when using templates, since the compiler
	needs to know that T is a type name and not a variable name.
	Why is T used? T is a generic type name that can be used for any type of data.
	Any type name can be used, but T is commonly used to represent a generic data
	type. In any case, any type name can be used, such as U, V, W, etc.
	In the first function, swap, two values of type T are swapped. & is used to
	pass the values by reference. This means that the original values are modified
	instead of copied. This is useful when you want to modify the original values
	instead of copying them. However, in the min and max functions, the values are
	passed by value, which means they are copied and the original values are not
	modified.
	This can be used with any type of data, whether int, float, double, char,
	string, etc; since it is not necessary to write a function for each type of
	data, but the same code can be reused for any type. This makes the code cleaner,
	easier to maintain and easier to understand. In addition, the code is safer,
	since the compiler can detect errors at compile time if an incorrect data type
	is used.
	In summary, templates are a very powerful feature of C++ that allows you to
	write generic and reusable code.	*/
