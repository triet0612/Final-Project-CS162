#pragma once

#include <fstream>
#include <string>

using namespace std;

class Course {
public:
	int no, credits, maximumStudent;
	string courseID, nameOfCourse, nameOfTeacher, daySession1, daySession2;
	bool readData(ifstream& finput);
};
