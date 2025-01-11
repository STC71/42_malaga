/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-07 13:06:59 by sternero          #+#    #+#             */
/*   Updated: 2025-01-07 13:06:59 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <ctime>
#include <iomanip>
#include <iostream>

/*	using is used to write: cin, cout, endl, etc. instead of std::cin,
	std::cout, std::endl, etc.	*/

using std::cin;
using std::cout;
using std::endl;

/*	The nexts lines initialize the static variables of the class Account	*/

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

/*	The nexts lines implement the private methods of the class Account	*/

int Account::getNbAccounts() {
	return _nbAccounts;
}

int Account::getTotalAmount(void){
	return _totalAmount;
}

int Account::getNbDeposits(){
	return _totalNbDeposits;
}

int Account::getNbWithdrawals(){
	return _totalNbWithdrawals;
}

/*	The next function is used to display the date and time of the operation	*/

void Account::_displayTimestamp(void)
{
	time_t timestamp;
	struct tm *localTime;

	std::time(&timestamp);
	localTime = localtime(&timestamp);
	cout << "[";
	cout << localTime->tm_year + 1900;
	cout << std::setw(2) << std::setfill('0') << localTime->tm_mon + 1;
	cout << std::setw(2) << std::setfill('0') << localTime->tm_mday << "_";
	cout << std::setw(2) << std::setfill('0') << localTime->tm_hour;
	cout << std::setw(2) << std::setfill('0') << localTime->tm_min;
	cout << std::setw(2) << std::setfill('0') << localTime->tm_sec;
	cout << "] ";
}

/*	The method _displayTimestamp() is a private method that displays the
	date and time of the operation, and generenal information about the
	operation.	*/

void Account::displayAccountsInfos(){
	_displayTimestamp();
	cout << "accounts:" << getNbAccounts() << ";"
		<< "total:" << getTotalAmount() << ";"
		<< "deposits:" << getNbDeposits() << ";"
		<< "withdrawals:" << getNbWithdrawals() << endl;
}

/*	The nexts lines implement the constructor of the class Account	*/

Account::Account(int initial_deposit){
	this->_accountIndex = _nbAccounts++;
	this->_amount = initial_deposit;
	this->_nbDeposits = 0;
	this->_nbWithdrawals = 0;
	this->_totalAmount += initial_deposit;
	_displayTimestamp();
	cout << "index:" << this->_accountIndex << ";"
		<< "amount:" << this-> _amount << ";" << "created" << endl;
	return ;
}

/*	The nexts lines implement the destructor of the class Account	*/

Account::~Account(){
	_displayTimestamp();
	cout << "index:" << this ->_accountIndex << ";"
		<< "amount:" << this->_amount << ";" << "closed" << endl;
}

/**/

void Account::makeDeposit(int deposit) {
	_displayTimestamp();
	cout << "index:" << this-> _accountIndex << ";" 
		<< "p_amount:" << this -> _amount << ";";
	this->_amount += deposit;
	this->_nbDeposits += 1;
	_totalAmount += deposit;
	_totalNbDeposits += 1;
	cout << "deposit:" << deposit << ";" << "amount:" << this->_amount << ";"
		<< "nb_deposits:" << this->_nbDeposits << endl;
}

/*	The next method is used to check if the amount is negative	*/

int Account::checkAmount(void) const
{
    if (this->_amount < 0)
        return 1;
    return 0;
}

/*	The next method is used to make a withdrawal	*/

bool Account::makeWithdrawal(int withdrawal)
{
	_displayTimestamp();
    cout << "index:" << this->_accountIndex << ";" 
         << "p_amount:" << this->_amount << ";";
    this->_amount -= withdrawal;
    if (checkAmount())
    {
        this->_amount += withdrawal;
        cout << "withdrawal:refused" << endl;
        return false;
    }
    _totalAmount -= withdrawal;
    this->_nbWithdrawals += 1;
    cout << "withdrawal:" << withdrawal << ";" << "amount:" << this->_amount << ";"
         << "nb_withdrawals:" << this->_nbWithdrawals << endl;
    return true;
}

/*	The next method is used to display the status of the account	*/

void Account::displayStatus(void) const
{
    _displayTimestamp();
    cout << "index:" << this->_accountIndex << ";"
         << "amount:" << this->_amount << ";" << "deposits:" << this->_nbDeposits << ";"
         << "withdrawals:" << this->_nbWithdrawals << endl;
}
