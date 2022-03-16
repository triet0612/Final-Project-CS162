#pragma once

#include "SinglyLinkedList.h"
#include "Course.h"

class Course_controller {
public:
	string yearName, semesterName;
	SinglyLinkedList<Course> courses;
	Course_controller();
	
	void createCourses(const string& yearName, const string& semesterName);
	void viewListOfCourses();
	bool containsCourse(const string& courseID) const;
	bool viewScore(const string& courseID) const;
};