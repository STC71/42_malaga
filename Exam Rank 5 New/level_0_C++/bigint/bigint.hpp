#pragma once
#include <string>
#include <iostream>

class bigint {

	private:

		std::string num;
		void remove_zeros() {
			size_t pos = num.find_first_not_of('0');
			if (pos == std::string::npos) {	num = "0"; }
			else { num.erase(0, pos); }
		}

	public:

		bigint() : num("0") {}
		bigint(const std::string &n) : num(n) { remove_zeros(); }
		bigint(unsigned int n) : num(std::to_string(n)) {}

		bigint operator+(const bigint &oth) const {
			std::string a = num; std::string b = oth.num; std::string result = "";
			while (a.size() < b.size()) { a = '0' + a; }
			while (b.size() < a.size()) { b = '0' + b; }
			int carry = 0;
			for (int i = a.size() - 1; i >= 0; i--) {
				int sum = (a[i] - '0') + (b[i] - '0') + carry;
				carry = sum / 10; sum %= 10; result.insert(result.begin(), '0' + sum); }
			if (carry) { result.insert(result.begin(), '0' + carry); }
			bigint res(result); res.remove_zeros(); return res; }

		bigint &operator+=(const bigint &oth) { *this = *this + oth; return *this; }
		bigint& operator++() { *this = *this + bigint(1); return *this; }
		bigint operator++(int) { bigint temp = *this; ++(*this); return temp; }

		bigint operator<<(int shift) const {
			if (num == "0") { return bigint("0"); }
			return bigint(num + std::string(shift, '0')); }
		bigint operator>>(int shift) const {
			if (shift >= (int)num.size()) { return bigint("0"); }
			bigint res(num.substr(0, num.size() - shift));
			res.remove_zeros(); return res; }
		bigint &operator<<=(int shift) { *this = *this << shift; return *this; }
		bigint &operator>>=(int shift) { *this = *this >> shift; return *this; }
		bigint &operator>>=(const bigint &oth) { 
			int shift = std::stoi(oth.num); *this = *this >> shift; return *this; }

		bool operator<(const bigint &oth) const {
			if (num.size() != oth.num.size()) {	return num.size() < oth.num.size(); }
			return num < oth.num; }
		bool operator>(const bigint &oth) const { return oth < *this; }
		bool operator<=(const bigint &oth) const { return !(*this > oth); }
		bool operator>=(const bigint &oth) const { return !(*this < oth); }
		bool operator==(const bigint &oth) const { return num == oth.num; }
		bool operator!=(const bigint &oth) const { return !(*this == oth); }

		friend std::ostream &operator<<(std::ostream &os, const bigint &b) { os << b.num; return os; }

};
