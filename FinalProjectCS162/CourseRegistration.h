#pragma once

#include <string>
#include <cstring>

using namespace std;

#include "Date.h"

class CourseRegistration {
private:
	string yearName, semesterName, courseID;
	Date startDate, endDate;
	bool writeDataToFile();
public:
	void createRegistration(const string& yearName, const string& semesterName, const string& courseID);
	Date getStartDate() const;
	Date getEndDate() const;
	string getCourseID() const;
	bool loadDates();
	bool checkRegistrationDates() const;
	void changeDates();
};