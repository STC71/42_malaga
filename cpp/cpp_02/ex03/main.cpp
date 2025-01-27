/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-19 14:33:54 by sternero          #+#    #+#             */
/*   Updated: 2025-01-19 14:33:54 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

using std::cout;					// using to write cout ... whithout std::

bool bsp(const Point& a, const Point& b, const Point& c, const Point& point);
// Function to check if a point is inside a triangle

static void printGreen(const std::string& text) {
    cout << "\033[32m" << text << "\033[0m";
}	// Function to print in green

static void	printData(const Point& A, const Point& B, const Point& C, const Point& P){
	cout << "\nThe ";
	printGreen("triangle vertices");
	cout << " are : \n" << std::endl;
	cout << "	position of A : (" << A.getX().toFloat() << ", " << A.getY().toFloat() << ") \n ";
	cout << "	position of B : (" << B.getX().toFloat() << ", " << B.getY().toFloat() << ") \n ";
	cout << "	position of C : (" << C.getX().toFloat() << ", " << C.getY().toFloat() << ")";
	cout << "\n" <<std::endl;
	cout << "The position to search for is (P) : ";
	cout << "(" << P.getX().toFloat() << ", " << P.getY().toFloat() << ")\n" << std::endl;
}	// Function to print the data

int main( void ) {
	Point		A(0.f, 0.f);
	Point		B(10.f, 30.f);
	Point		C(20.f, 0.f);
	Point		P(0.f, 15.f);	// outside: change the comment to test the inside
	//Point		P(10.f, 15.f);	// inside : change the comment to test the outside
	std::string	answer;

	answer = bsp(A, B, C, P) ? "\033[32m inside \033[0m" : "\033[31m outside \033[0m";
	printData(A, B, C, P);
	cout << "The point (P) is" << answer << "of the triangle. \n" << std::endl;

	return 0;
}	// Main function to test the bsp function
