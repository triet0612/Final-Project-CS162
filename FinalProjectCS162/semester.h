#pragma once
#include <iostream>
#include <string>

using namespace std;

#include "Date.h"
#include "Course_controller.h"

class semester
{
public:
	Course_controller course;
	string semester_name;
	Date startdate;
	Date endate;
	semester(string name, Date s, Date e) {
		semester_name = name;
		startdate = s;
		endate = e;
	}
};

