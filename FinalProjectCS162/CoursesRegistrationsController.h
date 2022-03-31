#pragma once

#include <cstring>
#include <string>

using namespace std;

#include "SinglyLinkedList.h"
#include "CourseRegistration.h"

class CoursesRegistrationsController {
public:
	SinglyLinkedList<CourseRegistration> coursesRegistrations;
	string yearName, semesterName;

	CoursesRegistrationsController();
	void createCoursesRegistration(const string& yearName, const string& semesterName);
	bool loadData();
	bool loadDataFromFile(const string& path);
	bool writeData() const;
	bool writeDataToFile(const string& path) const;
	//CourseRegistration& getCourseRegistration(const string& courseID);
	void displayCoursesRegistrationTable() const;
};