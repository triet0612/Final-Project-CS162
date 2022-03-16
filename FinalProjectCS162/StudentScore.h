#pragma once

#include <string>
#include <cstring>
#include <fstream>

using namespace std;

struct StudentScore {
public:
	double totalMark, finalMark, midtermMark, otherMark;
	int number, studentID;
	string name;

	bool readData(ifstream& finput);
};