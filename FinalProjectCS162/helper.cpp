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