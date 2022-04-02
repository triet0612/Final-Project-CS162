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
#include "CourseRegistration.h"
#include "CoursesList.h"
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
	Course_controller();
	Course_controller(string yearname, string semesterName) {
		this->yearName = yearName;
		this->semesterName = semesterName;
		loadCourses(yearname, semesterName);
	};
	
	void loadCourses(const string& yearName, const string& semesterName);
	//--
	int chooseOption(Table& table) {
		ConsoleGraphics* graphics = &ConsoleGraphics::getInstance();
		int type = -1;
		graphics->loopBoolean([&](pair<int, int> input) {
			int y = 0, x = 0;
			if (input.first == INPUT_CODE::ESC) return false;
			if (input.first == INPUT_CODE::ENTER) {
				table.defaultPressAnimation();
				type = table.getCurRow();
				return false;
			}
			else if (input.first == INPUT_CODE::DIRECTION) {
				graphics->getNextDirection(input, x, y);

				table.switchPage(table.getCurPage() + x);
				table.focusRow(table.getCurRow() + y);

				graphics->hideCursor();
			}
			return true;

			});
		return type;
	};

	void setupCourseOptionsTable(Table& table, string courseID, int offsetY = 0) {
		table = Table(10, 5 + offsetY, 5);

		table.addTitleRow_back(40);
		table.getRow(0).addText(courseID);
		table.addRow_back("View students in course");
		table.addRow_back("Export student list to CSV");
		table.addRow_back("View the scoreboard in course");
		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int inputCourseOptionTableProc(string courseID, int offsetY = 0) {
		int type = 0;
		Table table;
		setupCourseOptionsTable(table, courseID, offsetY);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	void viewCourseOptions(string yearname, string semester, int id) {
		string courseID = this->courses[id].courseID;
		int type = inputCourseOptionTableProc(courseID, id);
		while (type != -1) {
			switch (type)
			{
			case 1:
				viewStu(yearname, semester, id); break;
			case 2: break;
			case 3: 
				viewScoreStu(yearName, semester, id); break;
			default:
				break;
			}
			type = inputCourseOptionTableProc(courseID, id);
		}
		return;
	};

	void setupCourseStudentsTable(Table& table, int id) {
		system("cls");
		table = Table(0, 0, 30);

		table.addTitleRow_back(12, 16, 14, 20);
		table.getRow(0).addText((string)"No", (string)"ID", (string)"First Name", (string)"Last Name");
		if (courses[id].students.size() == 0) {
			table.addRow_back("Empty");
		}
		for (auto i : courses[id].students) {
			table.addRow_back(i.no, i.ID, i.firstname, i.lastname);
		}

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int getCourseStudentFromTableProc(int id) {
		int type = 0;
		Table table;
		setupCourseStudentsTable(table, id);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	void viewStu(string yearname, string semester, int id) {

		courses[id].getCourseStudents(yearname, semester);
		int type = getCourseStudentFromTableProc(id);

		while (type != -1) {

			type = getCourseStudentFromTableProc(id);
		}
	}

	void viewListOfCourses(string yearname, string semester);

	bool containsCourse(const string& courseID) const;

	//--
	void setupScoreCourseStudentsTable(Table& table, int id) {
		system("cls");
		table = Table(0, 0, 30);

		table.addTitleRow_back(12, 16, 14, 18, 18, 14, 18);
		table.getRow(0).addText((string)"No", (string)"ID", (string)"Name", (string)"Total Score", (string)"Final Score", (string)"Midterm", (string)"Other Score");
		if (courses[id].scoreStudents.size() == 0) {
			table.addRow_back("Empty");
		}
		for (auto i : courses[id].scoreStudents) {
			table.addRow_back(i.no, i.ID, i.name, i.totScore, i.FinScore, i.midScore, i.otherScore);
		}

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int getScoreCourseStudentFromTableProc(int id) {
		int type = 0;
		Table table;
		setupScoreCourseStudentsTable(table, id);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	void viewScoreStu(string yearname, string semester, int id) {

		courses[id].getScoreCourseStudents(yearname, semester);
		int type = getScoreCourseStudentFromTableProc(id);

		while (type != -1) {

			type = getScoreCourseStudentFromTableProc(id);
		}
	}

	bool viewScore(const string& courseID) const;
	void updateScore(const string& courseID, const int studentID);
	void addStudentToEnrolledCourses(const int studentID, const SinglyLinkedList<string> enrolledCourses);
	void viewScoresOfStudents(const string& courseID, const int studentID) const;
	SinglyLinkedList<pair<int, SinglyLinkedList<string> > > getListOfEnrolledCourses() const;
	SinglyLinkedList<string> getListOfEnrolledCoursesOfStudent(const int studentID) const;
	int countStudentsInCourse(const string& courseID) const;
	void changeEnrolledCourses(const int studentID);
	SinglyLinkedList<int> getCourseListOfStudentsID(const string& courseID) const;
	bool exportListOfStudentsID(const string& courseID) const;
	void updateCoursesInformation();
};