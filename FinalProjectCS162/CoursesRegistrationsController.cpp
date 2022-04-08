#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "CoursesRegistrationsController.h"
#include "helper.h"

CoursesRegistrationsController::CoursesRegistrationsController() {};

bool CoursesRegistrationsController::saveCreatedCourseRegs(const string& path) const {
	ofstream foutput;
	foutput.open(path);
	for (const CourseRegistration& courseRegistration : (this->coursesRegistrations)) {
		foutput << courseRegistration.getCourseID() << '\n';
		printDates(foutput, courseRegistration.getStartDate(), " ");
		foutput << " ";
		printDates(foutput, courseRegistration.getEndDate(), " ");
		foutput << '\n';
	}
	foutput.close();


	return true;
};

bool CoursesRegistrationsController::loadCreatedCoursesRegsFromPath(const string& path) {
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

bool CoursesRegistrationsController::loadCreatedCourseRegs() {
	return this->loadCreatedCoursesRegsFromPath("Data/" + (this->yearName) + "/" + (this->semesterName) + "/coursesRegistrationsDates.txt");
};

bool CoursesRegistrationsController::writeData() const {
	ofstream ofs( "Data/" + (this->yearName) + "/" + (this->semesterName) + "/EnrolledCourses.csv");
	ofs << "Student ID";
	for (const CourseRegistration& courseRegistration : (this->coursesRegistrations)) {
		ofs << "," << courseRegistration.getCourseID();
	}

	ofs.close();
	return this->saveCreatedCourseRegs("Data/" + (this->yearName) + "/" + (this->semesterName) + "/coursesRegistrationsDates.txt");
};

CourseRegistration& CoursesRegistrationsController::getCourseRegistration(const string& courseID) {
	for (CourseRegistration& courseRegistration : (this->coursesRegistrations))
		if (courseRegistration.getCourseID() == courseID)
			return courseRegistration;
};

void CoursesRegistrationsController::createCoursesRegistration(const string& yearName, const string& semesterName) {
	(this->yearName) = yearName;
	(this->semesterName) = semesterName;
};

bool CoursesRegistrationsController::containsCourseRegistration(const string& courseID) {
	for (const CourseRegistration& courseRegistration : (this->coursesRegistrations))
		if (courseRegistration.getCourseID() == courseID)
			return true;
	return false;
};
