#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

#include "Course_controller.h"
#include "helper.h"
#include "StudentScore.h"

Course_controller::Course_controller() {};

void Course_controller::createCourses(const string& yearName, const string& semesterName) {
	ifstream finput("../Data/" + yearName + "/" + semesterName + "/Courses.csv");
	(this->yearName) = yearName;
	(this->semesterName) = semesterName;
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

bool Course_controller::containsCourse(const string& courseID) const {
	for (const Course& course : (this->courses))
		if (course.courseID == courseID)
			return true;
	return false;
};

bool Course_controller::viewScore(const string& courseID) const {
	if (!(this->containsCourse(courseID))) {
		cout << "There is no course with " << courseID << '\n';
		return false;
	}
	ifstream finput("../Data/" + (this->yearName) + "/" + (this->semesterName) + "/Mark/" + courseID + ".csv");
	if (finput) {
		StudentScore studentScore;
		finput.ignore(5000, '\n'); //not read first line
		finput.precision(1);
		const int number_length = 3, studentID_length = 15, name_length = 15, 
			      totalMark_length = 15, finalMark_length = 15, midtermMark_length = 15, otherMark_length = 15,
				  totalLength = 8 + number_length + studentID_length + name_length + totalMark_length + finalMark_length + midtermMark_length + otherMark_length;
		cout << string(totalLength, '-') << '\n';
		cout << '|'
			 << setw(number_length) << "No" << '|'
			 << setw(studentID_length) << "Student ID" << '|'
			 << setw(name_length) << "Name" << '|'
			 << setw(totalMark_length) << "Total mark" << '|'
			 << setw(finalMark_length) << "Final mark" << '|'
			 << setw(midtermMark_length) << "Midterm mark" << '|'
			 << setw(otherMark_length) << "Other mark" << '|'
			 << '\n';
		cout << string(totalLength, '-') << '\n';
		while (studentScore.readData(finput))
			cout << '|'
			 	 << setw(number_length) << studentScore.number << '|'
				 << setw(studentID_length) << studentScore.studentID << '|'
				 << setw(name_length) << studentScore.name << '|'
				 << setw(totalMark_length) << studentScore.totalMark << '|'
				 << setw(finalMark_length) << studentScore.finalMark << '|'
				 << setw(midtermMark_length) << studentScore.midtermMark << '|'
				 << setw(otherMark_length) << studentScore.otherMark << '|'
				 << '\n';
		cout << string(totalLength, '-') << '\n';
		return true;
	}
	cerr << "There is error in opening file\n";
	return false;
};

void Course_controller::updateScore(const string& courseID, const int studentID) {
	if (!(this->containsCourse(courseID))) {
		cout << "There is no course with " << courseID << '\n';
		return;
	}
	double score;
	int id = -1, number = 0;
	StudentScore studentScore;
	SinglyLinkedList<StudentScore> scoresOfStudents = this->getScore(courseID);
	for (const StudentScore& studentScore : scoresOfStudents) {
		if (studentScore.studentID == studentID) {
			id = number;
			break;
		}
		++number;
	}
	if (id < 0) {
		cout << "There was no student with " << studentID << " in the course " << courseID << "\n";
		return;
	}
	studentScore = scoresOfStudents[id];
	do {
		system("cls");
		studentScore.printData(cout);
		cout << "Please enter one of following options\n"
			 << "1. Stop updating score\n"
		 	 << "2. Update total mark\n"
		 	 << "3. Update final mark\n"
		 	 << "4. Update midterm mark\n"
	 		 << "5. Update other mark\n"
			 << "Your option: ";
		cin >> number;
		if (number == 1) {
			scoresOfStudents[id] = studentScore;
			break;
		} else if (number < 1 || number > 5) {
			cout << "Option is invalid\n";
		} else {
			cout << "Please enter new score: ";
			cin >> score;
			switch (number) {
			case 2:
				studentScore.totalMark = score;
				break;
			case 3:
				studentScore.finalMark = score;
				break;
			case 4:
				studentScore.midtermMark = score;
				break;
			case 5:
				studentScore.otherMark = score;
				break;
			}
		}
		system("pause");
	} while (number != 1);
	printScoresToCSVfile(courseID, scoresOfStudents);
};

SinglyLinkedList<StudentScore> Course_controller::getScore(const string& courseID) {
	SinglyLinkedList<StudentScore> scoresOfStudents;
	ifstream finput("../Data/" + (this->yearName) + "/" + (this->semesterName) + "/Mark/" + courseID + ".csv");
	if (finput) {
		StudentScore studentScore;
		finput.ignore(5000, '\n'); //Not read first line
		while (studentScore.readData(finput)) 
			scoresOfStudents.push_back(studentScore);
	}
	finput.close();
	return scoresOfStudents;
};

void Course_controller::printScoresToCSVfile(const string& courseID, const SinglyLinkedList<StudentScore>& scoresOfStudents) {
	ofstream foutput("../Data/" + (this->yearName) + "/" + (this->semesterName) + "/Mark/" + courseID + ".csv");
	foutput << "No,Student ID,Name,Total Mark,Final Mark,Midtern Mark,Orther Mark\n";
	for (const StudentScore& studentScore : scoresOfStudents)
		studentScore.printToCSVfile(foutput);
	foutput.close();
};