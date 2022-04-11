#pragma once
#include <iostream>
#include <string>

using namespace std;

#include "Date.h"
#include "Course_controller.h"
#include "CoursesRegistrationsController.h"

class semester
{
public:
	Course_controller courses;
	string semester_name;
	string yearname;
	Date startdate;
	Date endate;
	semester();
	semester(const string& name, const string& yearname, const Date& s, const Date& e);

};
