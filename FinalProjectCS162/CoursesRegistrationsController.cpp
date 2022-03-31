#include <iostream>
#include <fstream>

using namespace std;

#include "CoursesRegistrationsController.h"
#include "helper.h"

CoursesRegistrationsController::CoursesRegistrationsController() {};

bool CoursesRegistrationsController::writeDataToFile(const string& path) const {
	ofstream foutput(path + "/coursesRegistrationsDates.txt");
	if (foutput) {
		for (const CourseRegistration& courseRegistration : coursesRegistrations) {
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
		while (courseRegistration.loadData(finput))
			(this->coursesRegistrations).push_back(courseRegistration);
		finput.close();
		return true;
	}
	finput.close();
	return false;
};