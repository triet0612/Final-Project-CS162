#pragma once

#include "SinglyLinkedList.h"
#include "Course.h"

class CoursesList : public SinglyLinkedList<Course> {
public:
	void displayListOfCourses() const;
	bool containsCourse(const string& courseID) const;
	void updateInformation();
};