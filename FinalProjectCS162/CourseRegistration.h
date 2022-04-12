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
	CourseRegistration();

	CourseRegistration(const string& yearName, const string& semesterName, const string& courseID);

	CourseRegistration(const string& yearName, const string& semesterName, const string& courseID, const Date& startDate, const Date& endDate);

	void createRegistration(const string &yearName, const string &semesterName, const string &courseID);
	void createRegistration(const string &yearName, const string &semesterName);
	Date getStartDate() const;
	Date getEndDate() const;
	string getCourseID() const;
	bool loadDates();
	bool loadData(ifstream& finput);
	bool checkRegistrationDates() const;

	//--
	int chooseOption(Table& table);;

	void setupCourseRegInfoTable(Table& table, int id, const string& yearname);

	void courseRegInfoTableProc(int id, const string& yearname);

	void viewCourseRegInfoTable(int id, const string& yearname);

	//--
	void setupSemesterOptionsTable(Table& table);

	int inputSemesterOptionTableProc();

	void viewCourseRegOptions(int id, const string& yearname);

	void ModifyRegCourseDates();
	
	//--
};