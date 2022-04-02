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
class Class_controller
{
public:
	SinglyLinkedList<Class> classes;

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

	void setupClassesTable(Table& table) {
		system("cls");
		table = Table(0, 0, 30);

		table.addTitleRow_back(30);
		table.getRow(0).addText((string)"CLasses");
		table.addRow_back("Add...");
		for (auto i : classes) {
			table.addRow_back(i.class_name);
		}

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int inputClassesProc() {
		int type = 0;
		Table table;
		setupClassesTable(table);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	//--
	void viewClasses(string yearname) {
		loadStudentsOfClasses(yearname);
		int type = inputClassesProc();
		while (type != -1) {
			if (type == 1) {
				createClass(yearname);
			}
			else {
				//schoolYearOptions(sc.yearList[type - 2]);
				classes[type - 2].viewStu(yearname, classes[type - 2].class_name);
			}
			type = inputClassesProc();
		}
	}

	//--
	void setupClassInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos) {
		for (int i = 0; i < 1; ++i) {
			inputList.push_back(InputRow(40, 4 * i + 1, 50, 3, 0, 15));
			pos.push_back(inputList.back().getInside());
			inputList.back().setTitleBoxWidth(20).setContentBoxWidth(30);
			inputList.back().setDefaultType();
		}

		inputList[0].setTitle("Class's name: ").setContent("");

		inputList[0].setCursorInside();
		buttonList.push_back(Button(66, 6, 10, 3));
		pos.push_back(buttonList.back().getInside());
		buttonList.back().setText("   OK");
		buttonList.back().setDefaultType();

		for (auto& elem : buttonList) elem.render();
		for (auto& elem : inputList) elem.update();
		for (auto& elem : inputList) elem.render();
	}

	void setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, string& res, bool& isOver) {
		target.setOnClick([&](Button& button) {
			res = inputList[0].getContentBox().getText();
			isOver = true;
			});
	}

	void setValidPosition(COORD c, int x, int y, int& cur, bool inTxt, bool inBtn, sll<pair<int, int> >& pos, ConsoleGraphics& graphics) {
		if (!inTxt && !inBtn) {
			if (x > 0 || y > 0) cur = (cur + 1) % pos.size();
			else if (x < 0 || y < 0) cur = (cur + pos.size() - 1) % pos.size();
			graphics.gotoXY(pos[cur].first, pos[cur].second, true);
		}
		else if (inTxt) graphics.gotoXY(c.X, c.Y);
	};

	void renderInputProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver) {
		int cur = 0;
		ConsoleGraphics& graphics = ConsoleGraphics::getInstance();

		TextBox notice = TextBox(87, 8, 40, 3, false).setText("Press ESC for cancel");
		notice.render();

		graphics.loopBoolean([&](pair<int, int> input) {
			COORD c = graphics.GetConsoleCursorPosition();
			int x = 0, y = 0;
			bool inBtn = false, inTxt = false;
			if (input.first == INPUT_CODE::ESC) return false;
			graphics.getNextDirection(input, x, y);
			c.X += x; c.Y += y;

			for (auto& elem : inputList) if (elem.checkPosInsideContentBox(c)) inTxt = true;
			for (auto& elem : buttonList) if (elem.isPosInContainer(c)) inBtn = true;

			setValidPosition(c, x, y, cur, inTxt, inBtn, pos, graphics);

			for (auto& elem : inputList) elem.update(input);
			for (auto& elem : buttonList) elem.update(input);

			Sleep(60);

			for (auto& elem : inputList) elem.render();
			for (auto& elem : buttonList) elem.render();
			if (inBtn) graphics.hideCursor();
			else graphics.showCursor();
			graphics.color(0);
			return !isOver;
			});
	}

	void renderCaution() {
		TextBox notice = TextBox(45, 5, 40, 3, false, 0, 12).setText("Do not leave empty");
		notice.render();
	}

	void renderAccept() {
		TextBox notice = TextBox(45, 5, 40, 3, false, 0, 10).setText("input successfully, loading ...");
		notice.render();
	}

	string inputClassProc(bool& isCancel) {
		sll<InputRow> inputList;
		sll<Button> buttonList;
		sll<pair<int, int> > pos;
		string res;
		bool isOver = false;

		setupClassInputList(inputList, buttonList, pos);
		setOnClickSubmitButton(buttonList[0], inputList, res, isOver);

		renderInputProc(inputList, buttonList, pos, isOver);
		isCancel = !isOver;
		return res;
	}

	void createClass(string year) {
		bool cancel;
		string res = inputClassProc(cancel);

		while (!cancel && res == "") {
			if (res == "") renderCaution();
			res = inputClassProc(cancel);
		}
		if (cancel) return;

		Class c;
		c.class_name = res;
		classes.push_back(c);
		saveClasses(year);
		renderAccept();
		Sleep(100);
	}

	void saveClasses(string yearname) {
		ofstream fout;
		fout.open("Data/" + yearname + "/class.txt");
		for (auto i : classes) {
			fout << i.class_name << endl;
		}
		fout.close();
		return;
	}

	void loadStudentsOfClasses(string yearname) {
		classes.clear();
		SinglyLinkedList<string> classname = getClasses(yearname);
		for (auto i : classname) {
			Class c_temp;
			c_temp.addStuByCSV(yearname, i);
			classes.push_back(c_temp);
		}
		return;
	}

	sll<string> getClasses(string yearname) {
		SinglyLinkedList<string> Classes_name;
		ifstream fin;
		string temp;
		fin.open("Data/" + yearname + "/class.txt");
		if (!fin.is_open()) return Classes_name;
		while (!fin.eof()) {
			temp = "";
			getline(fin, temp);
			if (temp == "") return Classes_name;
			Classes_name.push_back(temp);
		}
		fin.close();
		return Classes_name;
	}

	void viewScoreOfClass(Class c, Course co, string semesterName) {
		ifstream fin;
		fin.open("Data/" + c.year_name + '/' + semesterName + "/Mark/" + co.courseID + ".csv");
		string No, Student_ID, Name, Total_Mark, Final_Mark, Midtern_Mark, Orther_Mark;
		while (getline(fin, No, ',')) {
			getline(fin, Student_ID, ',');
			getline(fin, Name, ',');
			getline(fin, Total_Mark, ',');
			getline(fin, Final_Mark, ',');
			getline(fin, Midtern_Mark, ',');
			getline(fin, Orther_Mark, ',');
			if (checkStudentInClass(c, Student_ID)) {
				cout << No << ' ' << Student_ID << ' ' << Name << ' ' << Total_Mark << ' ' << Final_Mark << ' ' << Midtern_Mark << ' ' << Orther_Mark << endl;
			}
		}
		fin.close();
		return;
	}

	bool checkStudentInClass(Class c, string ID) {
		for (auto i : c.students) {
			if (i.ID == ID) {
				return true;
			}
		}
		return false;
	}
};

