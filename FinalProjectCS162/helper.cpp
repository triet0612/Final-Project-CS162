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