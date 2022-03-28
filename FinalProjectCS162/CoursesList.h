#pragma once

#include "SinglyLinkedList.h"
#include "Course.h"

class CoursesList : public SinglyLinkedList<Course> {
public:
	bool readFile(const string& path);
	void displayListOfCourses() const;
	bool containsCourse(const string& courseID) const;
	void updateInformation();
	bool writeFile(const string& path) const;
	bool checkSessionsConflicted(const bool *enrolled) const;
};