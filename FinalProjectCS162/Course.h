#pragma once

#include <fstream>
#include <string>

using namespace std;

class Course {
public:
	int number, credits, maximumStudent;
	string courseID, nameOfCourse, nameOfTeacher, daySession1, daySession2;
	bool readData(ifstream& finput);
	void writeData(ofstream& foutput) const;
	bool updateCourse();
};
