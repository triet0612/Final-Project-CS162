#include "Course.h"
#include "helper.h"

bool Course::readData(ifstream& finput) {
	if (finput >> (this->no)) {
		finput.ignore(1, ',');
		getline(finput, this->courseID, ',');
		getline(finput, this->nameOfCourse, ',');
		getline(finput, this->nameOfTeacher, ',');
		finput >> (this->credits);
		finput.ignore(1, ',');
		finput >> maximumStudent;
		finput.ignore(1, ',');
		getline(finput, this->daySession1, ',');
		getline(finput, this->daySession2, '\n');
		adjustString(this->courseID);
		adjustString(this->nameOfCourse);
		adjustString(this->nameOfTeacher);
		adjustString(this->daySession1);
		adjustString(this->daySession2);
		return true;
	}
	return false;
};