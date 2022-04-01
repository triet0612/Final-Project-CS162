#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "SinglyLinkedList.h"
#include "Button.h"
#include "InputRow.h"
#include "table.h"
using namespace std;
class Class
{
public:
	struct student {
		string NO;
		string ID;
		string First_name;
		string Last_name;
		string Gender;
		string DOB;
		string Social_ID;
	};
	string class_name;
	string year_name;
	SinglyLinkedList<student> students;

	void addStuByCSV(string yearname, string classname) {
		class_name = classname;
		ifstream fin;
		fin.open("Data/" + yearname + '/' + classname + ".csv", ios::in);
		student temp;
		string tmp;
		students.clear();
		getline(fin, tmp ,'\n');
		while (!fin.eof()) {
			getline(fin, temp.NO, ',');
			if (temp.NO == "") return;
			getline(fin, temp.ID, ',');
			getline(fin, temp.First_name, ',');
			getline(fin, temp.Last_name, ',');
			getline(fin, temp.Gender, ',');
			getline(fin, temp.DOB, ',');
			getline(fin, temp.Social_ID);
			students.push_back(temp);
		}
		fin.close();
		return;
	}

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

	void setupStudentsTable(Table& table) {
		system("cls");
		table = Table(0, 0, 30);

		table.addTitleRow_back(12, 16, 14, 20, 13, 18, 20);
		table.getRow(0).addText((string)"No", (string)"ID", (string)"First Name", (string)"Last Name", (string)"Gender", (string)"Dob"
			, (string)"Social ID");
		if (students.size() == 0) {
			table.addRow_back("Empty");
		}
		for (auto i : students) {
			table.addRow_back(i.NO, i.ID, i.First_name, i.Last_name, i.Gender, i.DOB, i.Social_ID);
		}

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int getStudentFromTableProc() {
		int type = 0;
		Table table;
		setupStudentsTable(table);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	void viewStu(string yearname, string classname) {

		addStuByCSV(yearname, classname);
		int type = getStudentFromTableProc();

		while (type != -1) {

			type = getStudentFromTableProc();
		}
	}
	
	bool checkStu(string ID) {
		for (auto i : students) {
			if (i.ID == ID) {
				return true;
			}
		}
		return false;
	}
};

