#pragma once

#include <string>

using namespace std;

#include "SinglyLinkedList.h"
#include "Course.h"
#include "StudentScore.h"
#include "CourseRegistration.h"

class Course_controller {
private:
	SinglyLinkedList<StudentScore> getScore(const string& courseID) const;
	void printScoresToCSVfile(const string&courseID, const SinglyLinkedList<StudentScore>& scoresOfStudents) const;
	void displayRegistrationTable(const bool* status, const int* numberOfStudents, const SinglyLinkedList<CourseRegistration> &coursesRegistrations) const;
public:
	string yearName, semesterName;
	SinglyLinkedList<Course> courses;
	Course_controller();
	
	void createCourses(const string& yearName, const string& semesterName);
	void viewListOfCourses();
	bool containsCourse(const string& courseID) const;
	bool viewScore(const string& courseID) const;
	void updateScore(const string& courseID, const int studentID);
	void addStudentToEnrolledCourses(const int studentID, const SinglyLinkedList<string> enrolledCourses);
	void viewScoresOfStudents(const string& courseID, const int studentID) const;
	SinglyLinkedList<pair<int, SinglyLinkedList<string> > > getListOfEnrolledCourses() const;
	SinglyLinkedList<string> getListOfEnrolledCoursesOfStudent(const int studentID) const;
	int countStudentsInCourse(const string& courseID) const;
	void changeEnrolledCourses(const int studentID);
};