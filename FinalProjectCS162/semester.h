#pragma once
#include <iostream>
#include <string>
#include "Course_controller.h"
using namespace std;

class semester
{
public:
	Course_controller course;
	string semester_name;
	Date startdate;
	Date endate;
	semester() {
		semester_name = "";
		startdate = NULL;
		endate = NULL;
	}
	semester(string name, Date s, Date e) {
		semester_name = name;
		startdate = s;
		endate = e;
	}
};

