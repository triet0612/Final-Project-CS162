#pragma once
#include "Schoolyear.h"
#include "Class_controller.h"

class Schoolyear_controller {
private:
	bool CheckYear(string yearname);
	Class_controller classes;
public:
	Schoolyear sc;

	void saveYearList();

	void loadYearList();
	//--
	void setupSchoolYearInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos);

	void setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, string& res, bool& isOver);

	void setValidPosition(COORD c, int x, int y, int& cur, bool inTxt, bool inBtn, sll<pair<int, int> >& pos, ConsoleGraphics& graphics);;

	void renderInputProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver);

	void renderCaution();

	void renderAccept();

	string inputSchoolYearProc(bool& isCancel);

	//--
	void createSchoolYear();
	
	int chooseOption(Table& table);;

	void setupSchoolYearsTable(Table& table);

	int inputSchoolYearProc();

	void viewSchoolYear();
	
	Schoolyear getSchoolYear(string name);

	void addSemesterToSchoolYear(string yearname);
	
	void viewSemestersInYear();

	//--

	void setupSchoolYearOptionsTable(Table& table, string yearname);

	int inputSchoolYearOptionProc(string yearname);

	void schoolYearOptions(string yearname);

};