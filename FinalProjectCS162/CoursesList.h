#pragma once

#include <sstream>
#include "SinglyLinkedList.h"
#include "Course.h"
#include "Table.h"
#include "InputRow.h"
#include "Button.h"

class CoursesList : public SinglyLinkedList<Course> {
private: 
	void reNumberingCourses();
public:
	bool readFile(const string& path);

	bool loadCourse(string yearname, string semester);
	//--
	int chooseOption(Table& table);

	void setupCoursesTable(Table& table);

	int inputCoursesTableProc();

	//--
	int viewCourses(const string& yearname, const string& semester);

	void displayListOfCourses() const;

	bool containsCourse(const string& courseID) const;

	void updateInformation();

	void saveCourses(const string& yearname, const string& semester);

	bool writeFile(const string& path) const;

	bool checkSessionsConflicted(const bool *enrolled) const;

	Course& getCourse(const string& courseID);;

	//--
	void setupCourseInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, sll<string> initvalues, bool modify = false);

	void setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, sll<string>& res, bool& isOver);

	void setValidPosition(COORD c, int x, int y, int& cur, bool inTxt, bool inBtn, sll<pair<int, int> >& pos, ConsoleGraphics& graphics);;

	void renderInputCourseProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver);

	void renderCaution(string s = "Invalid input");

	void renderAccept();

	sll<string> inputCourseProc(bool& isCancel, sll<string> initvalues);

	void createCourse();

	//--
	void setOnClickDeleteButton(Button& target, sll<InputRow>& inputList, bool& isOver, bool& isDeleted);

	void buildInitValues(sll<string>& initvalues, Course& c);

	sll<string> modifyCourseProc(bool& isCancel, bool& isDeleted, sll<string> initvalues);

	void modifyCourse(int id, bool& isDeleted);
};