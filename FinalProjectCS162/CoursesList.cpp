#include <iostream>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

#include "CoursesList.h"
#include "helper.h"

void CoursesList::displayListOfCourses() const {
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
	for (const Course& course : (*this)) {
		number_length = max(number_length, getNumberOfDigits(course.number));
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
	for (const Course& course : (*this))
		cout << '|'
		<< setw(number_length) << course.number << '|'
		<< setw(courseID_length) << course.courseID << '|'
		<< setw(nameOfCourse_length) << course.nameOfCourse << '|'
		<< setw(nameOfTeacher_length) << course.nameOfTeacher << '|'
		<< setw(credits_length) << course.credits << '|'
		<< setw(maximumStudent_length) << course.maximumStudent << '|'
		<< setw(daySession1_length) << course.daySession1 << '|'
		<< setw(daySession2_length) << course.daySession2 << '|'
		<< '\n';
	cout << string(totalLength, '-') << '\n';
};

bool CoursesList::containsCourse(const string& courseID) const {
	for (const Course& course : (*this))
		if (course.courseID == courseID)
			return true;
	return false;
};

void CoursesList::updateInformation() {
	int option;
	string courseID;
	while (true) {
		system("cls");
		this->displayListOfCourses();
		cout << "1. Escape (stop updating courses information)\n"
			 << "2. Update course information\n"
			 << "3. Remove a course\n"
			 << "Please enter your option: ";
		if (!readInteger(option) || option < 1 || option > 3) {
			cout << "Invalid option\n";
			system("pause");
			continue;
		}
		if (option == 1)
			break;
		if (option == 2) {
			cout << "Please enter the id of course you want to update information: ";
			getline(cin, courseID);
			if (!(this->containsCourse(courseID))) {
				cout << "There was no course with course id " << courseID << '\n';
				system("pause");
				continue;
			} else {
				for (Course& course : (*this))
					if (course.courseID == courseID) {
						course.updateCourse();
						cout << "Information is updated successfully\n";
						system("pause");
						break;
					}
			}
		} else if (option == 3) {
			cout << "Please enter the id of course you want to remove: ";
			getline(cin, courseID);
			if (!(this->containsCourse(courseID))) {
				cout << "There was no course with course id " << courseID << '\n';
				system("pause");
				continue;
			} else {
				this->deleteNode([&](const Course& course) -> bool {
					return course.courseID == courseID;
				});
				cout << "Course is removed successfully\n";
				system("pause");
			}
		}
	}
};

bool CoursesList::readFile(const string& path) {
	ifstream finput(path);
	this->clear();
	if (finput) {
		Course course;
		finput.ignore(5000, '\n'); //ignore first line
		while (course.readData(finput))
			this -> push_back(course);
		finput.close();
		return true;
	}
	finput.close();
	return false;
};

bool CoursesList::writeFile(const string& path) const {
	ofstream foutput(path);
	if (foutput) {
		foutput << "No,CourseID,NameOfCourse,NameOfTeacher,Credits,MaximumStudent,Day-Session1,Day-Session2\n";
		for (const Course& course : (*this))
			course.writeData(foutput);
		return true;
	}
	foutput.close();
	return false;
};

bool CoursesList::checkSessionsConflicted(const bool* enrolled) const {
	const int numberOfCourses = this->size();
	SinglyLinkedList<pair<string, pair<int, int> > > sessions[2];
	for (int i = 0; i < numberOfCourses; ++i)
		if (enrolled[i]) {
			sessions[0].push_back((*this)[i].getDaySession1());
			sessions[1].push_back((*this)[i].getDaySession2());
		}
	const int numberOfEnrolledCourses = sessions[0].size();
	for (int i = 1; i < numberOfEnrolledCourses; ++i)
		for (int j = 0; j < i; ++j)
			for (int x = 0; x < 2; ++x)
				for (int y = 0; y < 2; ++y)
					if (sessions[x][i].first == sessions[y][j].first && checkIntersection(sessions[x][i].second, sessions[y][j].second))
						return true;
	return false;
};

Course& CoursesList::getCourse(const string& courseID) {
	for (Course& course : (*this))
		if (course.courseID == courseID)
			return course;
};