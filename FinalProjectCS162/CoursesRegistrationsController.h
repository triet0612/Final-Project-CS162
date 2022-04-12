#pragma once

#include <cstring>
#include <string>
#include <sstream>

using namespace std;

#include "SinglyLinkedList.h"
#include "CourseRegistration.h"

class CoursesRegistrationsController {
private:
	CourseRegistration& getCourseRegistration(const string& courseID);
	bool containsCourseRegistration(const string& courseID);
public:
	SinglyLinkedList<CourseRegistration> coursesRegistrations;
	sll<sll<string>> rawRegsData;
	string yearName, semesterName;

	CoursesRegistrationsController();
	CoursesRegistrationsController(const string& yearname, const string& semestername);
	
	~CoursesRegistrationsController();

	void createCoursesRegistration(const string& yearName, const string& semesterName);

	void delCourseReg(const string& courseID);

	void delEnrolledCourseColumn(const string& courseID);

	void loadEnrolledCourses();

	void getInfoEnrollmentStudent(int stuId, sll<bool>& status, sll<int>& curNumsStu);

	void updateStatusEnrolledCourses(int stuId, sll<bool>& status);

	void saveEnrolledCourses();

	bool loadCreatedCourseRegs();

	bool loadCreatedCoursesRegsFromPath(const string& path);

	bool writeData() const;

	bool saveCreatedCourseRegs(const string& path) const;

	bool checkExistence(const string& courseID) const;

	//--
	void setupDateRegInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos);

	void setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, sll<string>& res, bool& isOver);

	void setValidPosition(COORD c, int x, int y, int& cur, bool inTxt, bool inBtn, sll<pair<int, int> >& pos, ConsoleGraphics& graphics);;

	void renderInputDatesRegProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver);

	void renderCaution(const string& s = "Invalid input");

	void renderAccept();

	sll<string> inputDatesRegProc(bool& isCancel);

	void modifyDatesReg();
	//--
	void setupCourseRegTable(Table& table);

	int chooseOption(Table& table);

	int courseRegTableProc();

	void viewCourseRegTable();

};