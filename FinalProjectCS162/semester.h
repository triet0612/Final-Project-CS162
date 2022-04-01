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
	CoursesRegistrationsController courseRegs;
	string semester_name;
	string yearname;
	Date startdate;
	Date endate;
	semester() {};
	semester(string name, string yearname, Date s, Date e) {
		semester_name = name;
		startdate = s;
		endate = e;
		this->yearname = yearname;
		this->courses = Course_controller(yearname, semester_name);
		this->courseRegs = CoursesRegistrationsController(yearname, semester_name);
		//this->courseRegs;
	};


};
