#include <iostream>

using namespace std;

#include "helper.h"

int getNumberOfDigits(long long x) {
	if (x == 0)
		return 1;
	int result = 0;
	for (; x; x /= 10)
		++result;
	return result;
};

void adjustString(string& s) {
	if (!s.empty() && s[0] == '"' && s.back() == '"') 
		s = s.substr(1, (int)s.size() - 2);
	while (!s.empty() && isspace(s.back()))
		s.pop_back();
};

bool checkLeapYear(const int year) {
	if (year % 4)
		return false;
	if (year % 100)
		return true;
	return year % 400 == 0;
};

bool checkValidDate(const int day, const int month, const int year) {
	if (month < 1 || month > 12)
		return false;
	const int days[12] = {31, 28 + checkLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	return 1 <= day && day <= days[month - 1];
};

bool readInteger(int& answer) {
	string s;
	getline(cin, s);
	const int n = s.size();
	if (n >= 9) //Integer is too large
		return false;
	int result = 0;
	if (s[0] == '-') {
		for (int i = 1; i < n; ++i)
			if (isdigit(s[i]))
				(result *= 10) += s[i] - '0';
			else
				return false;
		result *= -1;
	} else {
		for (int i = 0; i < n; ++i)
			if (isdigit(s[i]))
				(result *= 10) += s[i] - '0';
			else
				return false;
	}
	//The value of variable is only updated when number is successfully inputted
	answer = result;
	return true;
};