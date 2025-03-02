/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 21:08:03 by sternero          #+#    #+#             */
/*   Updated: 2025-02-28 21:08:03 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

using std::cerr; using std::cout; using std::endl;

PmergeMe::PmergeMe() {}									// default constructor

PmergeMe::PmergeMe(const PmergeMe &src) {				// copy constructor
	*this = src;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src) {	// assignation operator
	(void)src;
	return *this;
}

const char *PmergeMe::InvalidInput::what() const throw() {	// return the exception message
	return RED "Invalid input" RESET;
}

// to convert a string to an unsigned int
unsigned int ft_stou(const std::string &str);

// ************************ VECTOR ************************

// to print de elements of VECTOR
static void printVector(const std::vector<unsigned int> &v) {
	std::vector<unsigned int>::const_iterator it;		// iterator to browse the vector
	int i = 0;											// int variable to count the elements
	for (it = v.begin(); it != v.end(); it++) {
		if (i < 7) {
			cout << *it << " ";
			i++;
		}
		else {
			cout << "[...] ";
			break;
		}
	}
	cout << endl;
}

// to join two vectors in one ascending order vector
static std::vector<unsigned int> 
joinVec(std::vector<unsigned int> 
&id, std::vector<unsigned int> &dd) {

	std::vector<unsigned int> res;						// create a vector object to store the result

	// join two vector until one of them is empty
	while (!id.empty() && !dd.empty()) {				// while the first vector (left) and the second vector are not empty
		if (id.front() <= dd.front()) {					// if the first element of the first vector is less than the first element of the second vector
			res.push_back(id.front());					// push the first element of the first vector to the result vector
			id.erase(id.begin());						// erase the first element of the first vector
		} else {
			res.push_back(dd.front());					// push the first element of the second vector to the result vector
			dd.erase(dd.begin());						// erase the first element of the second vector
		}
	}
	// Add the remaining elements of the left vector
	while (!id.empty()) {								// while the first vector (left) is not empty
		res.push_back(id.front());						// push the first element of the first vector to the result vector
		id.erase(id.begin());							// erase the first element of the first vector
	}
	// Add the remaining elements of the right vector
	while (!dd.empty()) {								// while the second vector (right) is not empty
		res.push_back(dd.front());						// push the first element of the second vector to the result vector
		dd.erase(dd.begin());							// erase the first element of the second vector
	}
	return res;											// return the result vector
}

// to sort the list implementing merge sort algorithm
static std::vector<unsigned int> insertVec(std::vector<unsigned int> &v) {
	if (v.size() <= 1)									// if the vector has 1 or less elements, is already sorted
		return v;										// return the vector

	int mid = v.size() / 2;								// divide the vector in two parts
	
	std::vector<unsigned int> id(v.begin(), v.begin() + mid);	// create a vector for the left part
	std::vector<unsigned int> dd(v.begin() + mid, v.end());		// create a vector for the right part
	
	id = insertVec(id);									// recursive call to sort the left part
	dd = insertVec(dd);									// recursive call to sort the right part
	
	return joinVec(id, dd);								// return tghe result of joining the two parts
}

// to print the elements of the VECTOR sorted and the duration
void PmergeMe::sortVector(int argc, char *argv[]) {
	std::vector<unsigned int> res;						// create a vector object to storage the result

	for (int i = 1; i < argc; i++) {
		res.push_back(ft_stou(argv[i]));				// convert the string to unsigned int and push it to the vector
	}

	cout << "\n\tVECTOR - "
		<< BLUE "Before sorting: " << RESET; 			// print the message
	printVector(res);									// print the elements of the vector

	std::clock_t start = std::clock();					// start the clock
	res = insertVec(res);								// sort the vector
	
	double duration = static_cast<double>(std::clock() 
	- start) / static_cast<double>CLOCKS_PER_SEC 
	* MICROSEC;											// calculate the duration in microseconds

	cout  << "\tVECTOR - "
		<< GREEN"After sorting : " << RESET;			// print the message
	printVector(res);									// print the elements of the vector
	//cout << endl;

	cout << "\nVector of " << BLUE << argc - 1 
	<< " elements " << RESET << "sorted in : " 
	<< GREEN << duration << " µs" << RESET << endl;		// print the number of elements and the duration
}

// ************************ LIST ************************

// to print the elements of the LIST
static void printList(std::list<unsigned int> &l) {
	std::list<unsigned int>::const_iterator it;			// iterator to browse the list
	int i = 0;											// int variable to count the elements
	for (it = l.begin(); it != l.end(); it++) {
		if (i < 7) {
			cout << *it << " ";
			i++;
		}
		else {
			cout << "[...] ";
			break;
		}
	}
	cout << endl;
}

// to sort the list implementing merge sort algorithm
static std::list<unsigned int> 
joinList(std::list<unsigned int> &id, 
std::list<unsigned int> &dd) {

	std::list<unsigned int> res;						// create a list object to store the result

	// join two list until one of them is empty
	while (!id.empty() && !dd.empty()) {				// while the first list (left) and the second list are not empty
		if (id.front() <= dd.front()) {					// if the first element of the first list is less than the first element of the second list
			res.push_back(id.front());					// push the first element of the first list to the result list
			id.erase(id.begin());						// erase the first element of the first list
		} else {
			res.push_back(dd.front());					// push the first element of the second list to the result list
			dd.erase(dd.begin());						// erase the first element of the second list
		}
	}
	// Add the remaining elements of the left list
	while (!id.empty()) {								// while the first list (left) is not empty
		res.push_back(id.front());						// push the first element of the first list to the result list
		id.erase(id.begin());							// erase the first element of the first list
	}
	// Add the remaining elements of the right list
	while (!dd.empty()) {								// while the second list (right) is not empty
		res.push_back(dd.front());						// push the first element of the second list to the result list
		dd.erase(dd.begin());							// erase the first element of the second list
	}
	return res;											// return the result list
}

// to sort the list implementing merge sort algorithm
static std::list<unsigned int> insertList(std::list<unsigned int> &l) {
	if (l.size() <= 1)									// if the list has 1 or less elements, is already sorted
		return l;										// return the list

	int mid = l.size() / 2;								// divide the list in two parts
	
	std::list<unsigned int> id;							// create a list for the left part
	std::list<unsigned int> dd;							// create a list for the right part
	
	for (int i = 0; i < mid; i++) {						// fill the left list
		id.push_back(l.front());						// push the first element of the list to the left list
		l.pop_front();									// erase the first element of the list
	}
	dd = l;												// fill the right list

	id = insertList(id);								// recursive call to sort the left part
	dd = insertList(dd);								// recursive call to sort the right part
	
	return joinList(id, dd);							// return tghe result of joining the two parts
}

// to print the elements of the LIST sorted and the duration
void PmergeMe::sortList(int argc, char *argv[]) {
	std::list<unsigned int> res;						// create a list object to storage the result

	for (int i = 1; i < argc; i++) {
		res.push_back(ft_stou(argv[i]));				// convert the string to unsigned int and push it to the list
	}

	cout << "\tLIST - "
		<< BLUE << "Before sorting :  " << RESET;			// print the message
	printList(res);										// print the elements of the list

	std::clock_t start = std::clock();					// start the clock
	res = insertList(res);								// sort the list
	
	double duration = static_cast<double>(std::clock() 
	- start) / static_cast<double>CLOCKS_PER_SEC 
	* MICROSEC;											// calculate the duration in microseconds

	cout  << "\tLIST - " 
		<< GREEN << "After sorting  :  " << RESET;		// print the message
	printList(res);										// print the elements of the list
	cout << endl;

	cout << "List of " << BLUE << argc - 1 
	<< " elements " << RESET << "sorted in  :  " 
	<< GREEN << duration << " µs" << RESET << endl;		// print the number of elements and the duration
}

PmergeMe::~PmergeMe() {}								// destructor
