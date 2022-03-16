#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

#include "Course_controller.h"
#include "helper.h"

Course_controller::Course_controller() {};

void Course_controller::createCourses(const string& yearName, const string& semesterName) {
	ifstream finput("../Data/" + yearName + "/" + semesterName + "/Courses.csv");
	if (finput) {
		Course course;
		finput.ignore(5000, '\n'); //ignore first line
		while (course.readData(finput)) 
			courses.push_back(course);
	} else
		cerr << "There was error in opening file\n";
	finput.close();
};

void Course_controller::viewListOfCourses() {
	int number_length = strlen("no"),
		credits_length = strlen("credits"),
		maximumStudent_length = strlen("Maximum student width"),
		nameOfCourse_length = strlen("Name of course"),
		courseID_length = strlen("Course ID"), 
		nameOfTeacher_length = strlen("Name of teacher"), 
		daySession1_length = strlen("Day session 1"),
		daySession2_length = strlen("Day session 2"),
		totalLength;
	// Find the require length for each information
	for (const Course& course : (this->courses)) {
		number_length = max(number_length, getNumberOfDigits(course.no));
		credits_length = max(credits_length, getNumberOfDigits(course.credits));
		maximumStudent_length = max(maximumStudent_length, getNumberOfDigits(course.maximumStudent));
		courseID_length = max(courseID_length, (int)course.courseID.size());
		nameOfTeacher_length = max(nameOfTeacher_length, (int)course.nameOfTeacher.size());
		nameOfCourse_length = max(nameOfCourse_length, (int)course.nameOfCourse.size());
		daySession1_length = max(daySession1_length, (int)course.daySession1.size());
		daySession2_length = max(daySession2_length, (int)course.daySession2.size());
	}
	number_length += 2;
	credits_length += 2;
	maximumStudent_length += 2;
	courseID_length += 2;
	nameOfTeacher_length += 2;
	nameOfCourse_length += 2;
	daySession1_length += 2;
	daySession2_length += 2;
	totalLength = number_length + credits_length + maximumStudent_length + courseID_length + nameOfCourse_length + nameOfTeacher_length + daySession1_length + daySession2_length + 9;
	cout << string(totalLength, '-') << '\n';
	cout << '|'
		 << setw(number_length) << "No" << '|' 
		 << setw(courseID_length) << "Course ID" << '|' 
		 << setw(nameOfCourse_length) << "Name of course" << '|'
		 << setw(nameOfTeacher_length) << "Name of teacher" << '|'
		 << setw(credits_length) << "Credits" << '|'
	     << setw(maximumStudent_length) << "Maximum student" << '|'
		 << setw(daySession1_length) << "Day session 1" << '|'
		 << setw(daySession2_length) << "Day session 2" << '|'
	     << '\n';
	cout << string(totalLength, '-') << '\n';
	for (const Course& course : (this->courses))
		cout << '|'
		<< setw(number_length) << course.no << '|'
		<< setw(courseID_length) << course.courseID << '|'
		<< setw(nameOfCourse_length) << course.nameOfCourse << '|'
		<< setw(nameOfTeacher_length) << course.nameOfTeacher << '|'
		<< setw(credits_length) << course.credits << '|'
		<< setw(maximumStudent_length) << course.maximumStudent << '|'
		<< setw(daySession1_length) << course.daySession1 << '|'
		<< setw(daySession2_length) << course.daySession2 << '|' 
		<< '\n';
	cout << string(totalLength, '-') << '\n';
}