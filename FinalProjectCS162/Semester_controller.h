#pragma once
#include <iostream>
#include <direct.h>
#include <string>
#include "semester.h"
#include "SinglyLinkedList.h"
#include "Class_controller.h"
#include "Date.h"
#include "Table.h"
#include "InputRow.h"
#include "Button.h"
using namespace std;

class Semester_controller
{
public:
	SinglyLinkedList<semester> semesterlist;

	semester cur_semester;
	
	bool checkSemester(string name);
	
	void saveSemester(string yearname);

	void create_semester(string yearname, sll<string> data);
	
	void loadSemesterList(string yearname);

	//--

	int chooseOption(Table& table);;

	void setupSemestersTable(Table& table);

	int inputSemesterTableProc();
	
	void viewSemesters(string yearname);
	
	void createCourseReg(semester& s);

	//--

	void setupSemesterInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos);

	void setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, sll<string>& res, bool& isOver);

	void setValidPosition(COORD c, int x, int y, int& cur, bool inTxt, bool inBtn, sll<pair<int, int> >& pos, ConsoleGraphics& graphics);;

	void renderInputSemesterProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver);

	void renderCaution(string s = "Invalid input");

	void renderAccept();

	sll<string> inputSemesterProc(bool& isCancel);

	//--
	void addSemesterToSchoolYear(string yearname);

	//--
	void setupSemesterInfoTable(Table& table, int id, string yearname);

	void semesterInfoTableProc(int id, string yearname);

	void viewSemesterInfoTable(int id, string yearname);

	//--
	void setupSemesterOptionsTable(Table& table);

	int inputSemesterOptionTableProc();

	void viewScoreClass(string semestername, string yearname);

	void setCurrentSemester(string yearname, string semester);

	void viewSemesterOptions(int id, string yearname);


};
