#pragma once

#include <cstring>
#include <string>

using namespace std;

#include "SinglyLinkedList.h"
#include "CourseRegistration.h"

class CoursesRegistrationsController {
public:
	SinglyLinkedList<CourseRegistration> coursesRegistrations;
	CoursesRegistrationsController();

	bool loadDataFromFile(const string& path);
	bool writeDataToFile(const string& path) const;
};