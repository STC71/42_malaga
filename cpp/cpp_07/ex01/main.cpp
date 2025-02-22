/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-20 17:38:40 by sternero          #+#    #+#             */
/*   Updated: 2025-02-20 17:38:40 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

using std::cout; using std::endl;

#define arraySize 3									// array size to iterate

int	main() {

	int arrayInt[] = { 1, 10, -100 };					// array of integers to iterate

	cout << "\n";
	cout << GREEN << "arrayInt before iter:" << RESET << endl;
	iter(arrayInt, arraySize, &::print<int>);		// iterate over arrayInt with print function

	::iter(arrayInt, arraySize, &::addOne<int>);	// iterate over arrayInt with addOne function

	cout << "\n";
	cout << GREEN << "arrayInt after iter:"<< RESET << endl;
	::iter(arrayInt, arraySize, &::print<int>);		// iterate over arrayInt with print function

	return 0;

}

/*
class Awesome
{
  public:
    Awesome( void ) : _n( 42 ) { return; }
    int get( void ) const { return this->_n; }
  private:
    int _n;
};
std::ostream & operator<<( std::ostream & o, Awesome const & rhs )
{
  o << rhs.get();
  return o;
}
template< typename T >
void print( T& x )
{
  std::cout << x << std::endl;
  return;
}
int main() {
  int tab[] = { 0, 1, 2, 3, 4 };
  Awesome tab2[5];
  iter( tab, 5, print<const int> );
  iter( tab2, 5, print<Awesome> );
  return 0;
}
*/
