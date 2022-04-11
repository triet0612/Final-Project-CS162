#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <direct.h>
#include <string>

#include "helper.h"
#include "StudentScore.h"

#include "SinglyLinkedList.h"
#include "Course.h"
#include "StudentScore.h"
#include "CoursesRegistrationsController.h"
#include "CoursesList.h"
#include "helper.h"
using namespace std;


class Course_controller {
private:
	SinglyLinkedList<StudentScore> getScore(const string& courseID) const;
	void printScoresToCSVfile(const string&courseID, const SinglyLinkedList<StudentScore>& scoresOfStudents) const;
	void displayRegistrationTable(const bool* status, const int* numberOfStudents, const SinglyLinkedList<CourseRegistration> &coursesRegistrations) const;
	void updateEnrolledCoursesInCSVfile(const int studentID, const SinglyLinkedList<string>& enrolledCoursesID);
	void printEnrolledCoursesInCSVfile(const SinglyLinkedList<pair<int, SinglyLinkedList<string> > > &information);
public:
	string yearName, semesterName;
	CoursesList courses;
	CoursesRegistrationsController courseRegsController;
	Course_controller();
	Course_controller(string yearname, string semesterName);
	
	void loadCourses(const string& yearName, const string& semesterName);

	string getFinScoreOfStudent(int courseIdx, string stuID);

	void loadCourseStudent(int courseIdx);
	//--
	int chooseOption(Table& table);;

	void setupCourseOptionsTable(Table& table, string courseID, int offsetY = 0);

	int inputCourseOptionTableProc(string courseID, int offsetY = 0);

	void viewCourseOptions(string yearname, string semester, int id);;

	//--
	void setupCourseStudentsTable(Table& table, int id);

	int getCourseStudentFromTableProc(int id);

	void viewStu(string yearname, string semester, int id);

	void courseProc(string yearname, string semester);

	bool containsCourse(const string& courseID) const;

	//--
	void setupScoreCourseStudentsTable(Table& table, int id);

	int getScoreCourseStudentFromTableProc(int id);

	void viewScoreStu(string yearname, string semester, int id);


	void updateScore(const string& courseID, const int studentID);

	//--
	void setupScoreStudentTable(Table& table, int stuID);

	int getScoreStudentFromTableProc(int stuID);

	void viewScoresOfAStudent(const string studentID);

	//--
	void renderCaution(string s = "Invalid input");

	void renderAccept();

	void setupEnrollCourseTable(int initRow, Table& table, sll<bool>& enrolled, sll<int>& curNumsStu, CoursesRegistrationsController& courseRegController, CoursesList& validCourse, sll<int>& validRegPos);

	int inputEnrollCoursesTableProc(int stuID, sll<int>& curNumsStu, sll<bool>& status, CoursesRegistrationsController& courseRegController, CoursesList& validCourses, sll<int>& validRegPos, int initRow = 1);

	void getValidCourses(CoursesRegistrationsController& courseRegController, CoursesList& validCourses, sll<int>& validRegPos);

	void enrollCourseProc(int stuId, string firstname, string lastname);

	bool checkSessionsConflicted(sll<bool> status, CoursesRegistrationsController& CourseRegController, CoursesList& validCourses, sll<int>& validRegPos);;

	void SaveStudentEnrollmentOfCourses(string stuId, string lastname, string firstname, CoursesList& validCourses, sll<int>& validRegPos, sll<bool>& status);

	//--

	
	SinglyLinkedList<pair<int, SinglyLinkedList<string> > > getListOfEnrolledCourses() const;

	SinglyLinkedList<string> getListOfEnrolledCoursesOfStudent(const int studentID) const;

	int countStudentsInCourse(const string& courseID) const;

	void changeEnrolledCourses(const int studentID);

	SinglyLinkedList<int> getCourseListOfStudentsID(const string& courseID) const;

	bool exportListOfStudentsID(const string& courseID) const;

	void updateCoursesInformation();
};