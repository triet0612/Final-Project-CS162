#include <fstream>

using namespace std;

#include "CourseRegistration.h"

void CourseRegistration::createRegistration(const string& yearName, const string& semesterName, const string& courseID) {
	(this->yearName) = yearName;
	(this->semesterName) = semesterName;
	(this->courseID) = courseID;
};

Date CourseRegistration::getStartDate() const {
	return this->startDate;
};

Date CourseRegistration::getEndDate() const {
	return this->endDate;
};

bool CourseRegistration::loadDates() {
	/*
		return true if dates are loaded successfully and false otherwise
	*/
	ifstream finput("Data/" + (this->yearName) + "/" + semesterName + "/coursesRegistrationsDates.txt");
	cerr << "Data/" + (this->yearName) + "/" + semesterName + "/coursesRegistrationsDates.txt" << '\n';
	if (finput) {
		string id;
		int day, month, year;
		Date start, end;
		while (finput >> id) {
			finput >> day >> month >> year;
			start.setDate(day, month, year);
			finput >> day >> month >> year;
			end.setDate(day, month, year);
			if (id == (this->courseID)) {
				finput.close();
				this->startDate = start;
				this->endDate = end;
				return true;
			}
		}
	}
	finput.close();
	return false;
};

bool CourseRegistration::checkRegistration() const {
	/*
		return true if student can enroll in course and false otherwise
	*/
	Date today = Date::getCurrentDate();
	return (this->startDate) <= today && today <= (this->endDate);
};