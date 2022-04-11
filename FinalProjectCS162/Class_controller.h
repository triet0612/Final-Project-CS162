#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Class.h"
#include "SinglyLinkedList.h"
#include "Course_controller.h"
#include "Table.h"
#include "InputRow.h"
#include "Button.h"
#include "helper.h"
class Class_controller
{
public:
	SinglyLinkedList<Class> classes;

	//--
	int chooseOption(Table& table);;

	void setupClassesTable(Table& table, bool adding = true);

	int inputClassesProc(bool adding = true);

	//--
	void viewClasses(string yearname);

	//--
	void setupClassInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos);

	void setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, string& res, bool& isOver);

	void setValidPosition(COORD c, int x, int y, int& cur, bool inTxt, bool inBtn, sll<pair<int, int> >& pos, ConsoleGraphics& graphics);;

	void renderInputProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver);

	void renderCaution();

	void renderAccept();

	string inputClassProc(bool& isCancel);

	void createClass(string year);

	void saveClasses(string yearname);

	void loadStudentsOfClasses(string yearname);

	static void loadStudentsOfClasses(string yearname, sll<Class>& res) {
		SinglyLinkedList<string> classname = getClasses(yearname);
		for (auto i : classname) {
			Class c_temp;
			c_temp.addStuByCSV(yearname, i);
			res.push_back(c_temp);
		}
		return;
	}

	static sll<string> getClasses(string yearname) {
		SinglyLinkedList<string> Classes_name;
		ifstream fin;
		string temp;
		fin.open("Data/" + yearname + "/class.txt");
		if (!fin.is_open()) return Classes_name;
		while (!fin.eof()) {
			temp = "";
			getline(fin, temp, '\n');
			if (temp == "") return Classes_name;
			Classes_name.push_back(temp);
		}
		fin.close();
		return Classes_name;
	}

	static void getClasses(string yearname, sll<string>& classNames) {
		ifstream fin;
		string temp;
		fin.open("Data/" + yearname + "/class.txt");
		if (!fin.is_open()) return;
		while (!fin.eof()) {
			temp = "";
			getline(fin, temp);
			if (temp == "") return ;
			classNames.push_back(temp);
		}
		fin.close();
		return;
	}

	static void getAllClasses(sll<Class>& res) {
		string path = "Data/SchoolYear.txt";
		ifstream ifs(path);
		if (!ifs.is_open()) return;
		while (!ifs.eof()) {
			string yearname;
			ifs >> yearname;
			if (yearname == "") return;
			loadStudentsOfClasses(yearname, res);
		}
	}

	void loadAllClasses();

	//--
	void setupScoresClassTable(Table& table, int classIdx, Course_controller& coursesController);

	int inputScoresClasseProc(int classIdx, Course_controller& coursesController);


	void viewScoreOfClass(int classIdx, string semesterName, string yearname);

	bool checkStudentInClass(Class c, string ID);
};

