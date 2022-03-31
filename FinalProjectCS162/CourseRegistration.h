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

	void changeRegCourseDates();
	
	//--
	void setupDateRegInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos) {

		inputList.push_back(InputRow(1, 1, 50, 3, 0, 15));
		pos.push_back(inputList.back().getInside());
		inputList.back().setTitleBoxWidth(25).setContentBoxWidth(30);
		inputList.back().setDefaultType();

		for (int i = 0; i < 3; ++i) {
			inputList.push_back(InputRow(25 * i + 1, 5, 10, 3, 0, 15));
			pos.push_back(inputList.back().getInside());
			inputList.back().setTitleBoxWidth(15).setContentBoxWidth(5);
			inputList.back().setDefaultType2();
		}

		for (int i = 0; i < 3; ++i) {
			inputList.push_back(InputRow(25 * i + 1, 10, 10, 3, 0, 15));
			pos.push_back(inputList.back().getInside());
			inputList.back().setTitleBoxWidth(15).setContentBoxWidth(5);
			inputList.back().setDefaultType2();
		}

		Date cur = Date::getCurrentDate();
		inputList[0].setTitle("Course's ID: ").setContent("");
		inputList[1].setTitle("Start Day:").setContent(to_string(cur.getDay())).getContentBox().setNumberMode(true);
		inputList[2].setTitle("Start Month:").setContent(to_string(cur.getMonth())).getContentBox().setNumberMode(true);
		inputList[3].setTitle("Start Year:").setContent(to_string(cur.getYear())).setContentBoxWidth(7).getContentBox().setNumberMode(true);

		inputList[4].setTitle("End Day:").setContent(to_string(cur.getDay())).getContentBox().setNumberMode(true);
		inputList[5].setTitle("End Month:").setContent(to_string(cur.getMonth())).getContentBox().setNumberMode(true);
		inputList[6].setTitle("End Year:").setContent(to_string(cur.getYear())).setContentBoxWidth(7).getContentBox().setNumberMode(true);

		inputList[0].setCursorInside();
		buttonList.push_back(Button(10, 13, 10, 3));
		pos.push_back(buttonList.back().getInside());
		buttonList.back().setText("   OK");
		buttonList.back().setDefaultType();

		for (auto& elem : buttonList) elem.render();
		for (auto& elem : inputList) elem.update();
		for (auto& elem : inputList) elem.render();
	}

	void setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, sll<string>& res, bool& isOver)
	{
		target.setOnClick([&](Button& button) {
			res.clear();
			bool flag = true;
			for (auto elem : inputList) {
				res.push_back(elem.getContentBox().getText());
				if (res.back() == "") flag = false;
			}
			if (flag && (!Date::isValidDay(stoi(res[1]), stoi(res[2]), stoi(res[3])) || !Date::isValidDay(stoi(res[4]), stoi(res[5]), stoi(res[6])))) flag = false;
			if (!flag) renderCaution();
			isOver = flag;
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

	void renderInputDatesRegProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver) {
		int cur = 0;
		ConsoleGraphics& graphics = ConsoleGraphics::getInstance();

		TextBox notice = TextBox(7, 16, 40, 3, false).setText("Press ESC for cancel");
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

	void renderCaution(string s = "Invalid input") {
		TextBox notice = TextBox(5, 12, 40, 3, false, 0, 12).setText(s);
		notice.render();
	}

	void renderAccept() {
		TextBox notice = TextBox(5, 12, 40, 3, false, 0, 10).setText("input successfully, loading ...");
		notice.render();
	}

	sll<string> inputDatesRegProc(bool& isCancel) {
		sll<InputRow> inputList;
		sll<Button> buttonList;
		sll<pair<int, int> > pos;
		sll<string> res;
		bool isOver = false;

		setupDateRegInputList(inputList, buttonList, pos);
		setOnClickSubmitButton(buttonList[0], inputList, res, isOver);

		renderInputDatesRegProc(inputList, buttonList, pos, isOver);
		isCancel = !isOver;
		return res;
	}

	void changeDatesReg() {
		bool isCancel = false;
		system("cls");
		sll<string> res = inputDatesRegProc(isCancel);

		while (!isCancel) {
			res = inputDatesRegProc(isCancel);
		}
		if (isCancel) return;
		this->courseID = res[0];
		this->startDate = Date(stoi(res[1]), stoi(res[2]), stoi(res[3]));
		this->endDate = Date(stoi(res[4]), stoi(res[5]), stoi(res[6]));
		renderAccept();
		Sleep(200);
		return;
	}
};