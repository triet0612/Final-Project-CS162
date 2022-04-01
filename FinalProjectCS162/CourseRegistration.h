#pragma once

#include <string>
#include <cstring>
#include <fstream>

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

#include "SinglyLinkedList.h"
#include "helper.h"
#include "Date.h"
#include "Table.h"
#include "InputRow.h"
#include "Button.h"

class CourseRegistration {
private:
	string yearName, semesterName, courseID;
	Date startDate, endDate;
	bool writeDataToFile();
public:
	CourseRegistration() {
		yearName = semesterName = courseID = "";
		startDate = Date::getCurrentDate();
		endDate = Date::getCurrentDate();
	}

	CourseRegistration(string yearName, string semesterName, string courseID) {
		this->yearName = yearName;
		this->semesterName = semesterName;
		this->courseID = courseID;
		startDate = Date::getCurrentDate();
		endDate = Date::getCurrentDate();
	}

	CourseRegistration(string yearName, string semesterName, string courseID, Date startDate, Date endDate) {
		this->yearName = yearName;
		this->semesterName = semesterName;
		this->courseID = courseID;
		this->startDate = startDate;
		this->endDate = endDate;
	}

	void createRegistration(const string yearName, const string semesterName, const string courseID);
	void createRegistration(const string yearName, const string semesterName);
	Date getStartDate() const;
	Date getEndDate() const;
	string getCourseID() const;
	bool loadDates();
	bool loadData(ifstream& finput);
	bool checkRegistrationDates() const;

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

	void setupCourseRegInfoTable(Table& table, int id, string yearname) {
		system("cls");
		table = Table(0, 0, 3);

		table.addTitleRow_back(50);
		table.getRow(0).addText((string)" Course Registration Semester" + to_string(id + 1) + " Of " + yearname);

		table.addRow_back("Start: " + this->startDate.convert2String());
		table.addRow_back("End: " + this->endDate.convert2String());

		table.setDefaultType();
		table.render();

	}

	void courseRegInfoTableProc(int id, string yearname) {
		Table table;
		setupCourseRegInfoTable(table, id, yearname);
	}

	void viewCourseRegInfoTable(int id, string yearname) {
		system("cls");
		courseRegInfoTableProc(id, yearname);
		return;
	}

	//--
	void setupSemesterOptionsTable(Table& table) {
		table = Table(0, 7, 5);

		table.addTitleRow_back(40);
		table.getRow(0).addText((string)" OPTIONS");
		table.addRow_back("Change date");

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int inputSemesterOptionTableProc() {
		int type = 0;
		Table table;
		setupSemesterOptionsTable(table);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	void viewCourseRegOptions(int id, string yearname) {
		viewCourseRegInfoTable(id, yearname);
		int type = inputSemesterOptionTableProc();
		while (type != -1) {
			if (type == 1) {
				//createCourseReg(semesterlist[id], yearname);

			}
			else {
				//semesterlist[id].course.viewListOfCourses(yearname, "s" + to_string(id + 1));
			}
			viewCourseRegInfoTable(id, yearname);
			type = inputSemesterOptionTableProc();
		}
		return;
	}

	void ModifyRegCourseDates();
	
	//--
};