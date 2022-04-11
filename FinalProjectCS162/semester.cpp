#include "semester.h"

semester::semester() {}

semester::semester(const string& name, const string& yearname, const Date& s, const Date& e) {
	semester_name = name;
	startdate = s;
	endate = e;
	this->yearname = yearname;
	this->courses = Course_controller(yearname, semester_name);
	//this->courseRegs;
}
