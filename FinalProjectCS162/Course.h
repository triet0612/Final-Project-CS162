#pragma once

#include <fstream>
#include <string>
#include <cstring>

using namespace std;

class Course {
public:
	int number, credits, maximumStudent;
	string courseID, nameOfCourse, nameOfTeacher, daySession1, daySession2;

	Course();
	bool readData(ifstream& finput);
	void writeData(ofstream& foutput) const;
	bool updateCourse();
	bool checkConflicted(const Course& course) const;
	pair<string, pair<int, int> > getDaySession1() const;
	pair<string, pair<int, int> > getDaySession2() const;
};
