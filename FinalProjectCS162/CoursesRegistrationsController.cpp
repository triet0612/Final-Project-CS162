#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "CoursesRegistrationsController.h"
#include "helper.h"

CoursesRegistrationsController::CoursesRegistrationsController() {};

bool CoursesRegistrationsController::writeDataToFile(const string& path) const {
	ofstream foutput(path + "/coursesRegistrationsDates.txt");
	if (foutput) {
		for (const CourseRegistration& courseRegistration : (this->coursesRegistrations)) {
			foutput << courseRegistration.getCourseID() << '\n';
			printDates(foutput, courseRegistration.getStartDate(), " ");
			cout << " ";
			printDates(foutput, courseRegistration.getEndDate(), " ");
			cout << '\n';
		}
		foutput.close();
		return true;
	}
	foutput.close();
	return false;
};

bool CoursesRegistrationsController::loadDataFromFile(const string& path) {
	ifstream finput(path);
	if (finput) {
		CourseRegistration courseRegistration;
		(this->coursesRegistrations).clear();
		courseRegistration.createRegistration(this->yearName, this->semesterName);
		while (courseRegistration.loadData(finput)) 
			(this->coursesRegistrations).push_back(courseRegistration);
		finput.close();
		return true;
	}
	finput.close();
	return false;
};

bool CoursesRegistrationsController::loadData() {
	return this->loadDataFromFile("Data/" + (this->yearName) + "/" + (this->semesterName) + "/coursesRegistrationsDates.txt");
};

bool CoursesRegistrationsController::writeData() const {
	return this->writeDataToFile("Data/" + (this->yearName) + "/" + (this->semesterName) + "/coursesRegistrationsDates.txt");
};

/*
CourseRegistration& CoursesRegistrationsController::getCourseRegistration(const string& courseID) {
	for (CourseRegistration& courseRegistration : (this->coursesRegistrations))
		if (courseRegistration.getCourseID() == courseID)
			return courseRegistration;
};
*/

void CoursesRegistrationsController::createCoursesRegistration(const string& yearName, const string& semesterName) {
	(this->yearName) = yearName;
	(this->semesterName) = semesterName;
};

void CoursesRegistrationsController::displayCoursesRegistrationTable() const {
	int courseID_length = strlen("Course ID"),
		startDate_length = strlen("Start date"),
		endDate_length = strlen("End date"),
		totalLength;
	for (const CourseRegistration& courseRegistration : (this->coursesRegistrations)) {
		courseID_length = max(courseID_length, (int)courseRegistration.getCourseID().size());
		startDate_length = max(startDate_length, (int)courseRegistration.getStartDate().convert2String().size());
		endDate_length = max(endDate_length, (int)courseRegistration.getEndDate().convert2String().size());
	}
	courseID_length += 2;
	startDate_length += 2;
	endDate_length += 2;
	totalLength = 4 + courseID_length + startDate_length + endDate_length;
	cout << string(totalLength, '-') << '\n';
	cout << '|' 
		 << setw(courseID_length) << "Course ID" << '|' 
		 << setw(startDate_length) << "Start Date" << '|' 
		 << setw(endDate_length) << "End Date" << '|' 
		 << '\n';
	cout << string(totalLength, '-') << '\n';
	for (const CourseRegistration& courseRegistration : (this->coursesRegistrations)) {
		cout << '|'
			 << setw(courseID_length) << courseRegistration.getCourseID() << '|'
			 << setw(startDate_length) << courseRegistration.getStartDate().convert2String() << '|'
			 << setw(endDate_length) << courseRegistration.getEndDate().convert2String() << '|'
			 << '\n';
	}
	cout << string(totalLength, '-') << '\n';
};