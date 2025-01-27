/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-19 14:35:53 by sternero          #+#    #+#             */
/*   Updated: 2025-01-19 14:35:53 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

float area(const Point& a, const Point& b, const Point& c){
	float x1, y1;						// x and y values for the first vertice
	float x2, y2;						// x and y values for the second vertice
	float x3, y3;						// x and y values for the third vertice

	x1 = a.getX().toFloat();			// Get the x value of the first vertice
	y1 = a.getY().toFloat();			// Get the y value of the first vertice
	x2 = b.getX().toFloat();			// Get the x value of the second vertice
	y2 = b.getY().toFloat();			// Get the y value of the second vertice
	x3 = c.getX().toFloat();			// Get the x value of the third vertice
	y3 = c.getY().toFloat();			// Get the y value of the third vertice

	return std::abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
	// Return the area of the triangle
}

bool	bsp(const Point& a, const Point& b, const Point& c, const Point& point){
	
	float A = area(a, b, c);			// Calculate area of ABC
	float A1 = area(point, b, c);		// Calculate area of PBC
	float A2 = area(a, point, c);		// Calculate area of APC
	float A3 = area(a, b, point);		// Calculate area of ABP
	return (A == A1 + A2 + A3);			// Calculate if A = A1 + A2 + A3
}

/*	If the sum of the areas of the three triangles is equal to the area of triangle ABC, 
	then point P is inside the triangle, otherwise it is outside.

	The area of the triangle is calculated by the formula:
	Area = [x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2)] / 2 
	if A(1,2) B(3,4) C(5,1) then the area is -5, and the abs is 5.
	The negative sign indicates that we've calculated the area in the 
	opposite direction if the clockwise direction.
	To obtain the real area, we need to multiply by -1.	*/