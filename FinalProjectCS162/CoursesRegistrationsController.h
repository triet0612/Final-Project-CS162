#pragma once

#include <cstring>
#include <string>

using namespace std;

#include "SinglyLinkedList.h"
#include "CourseRegistration.h"

class CoursesRegistrationsController {
private:
	CourseRegistration& getCourseRegistration(const string& courseID);
	bool containsCourseRegistration(const string& courseID);
public:
	SinglyLinkedList<CourseRegistration> coursesRegistrations;
	string yearName, semesterName;

	CoursesRegistrationsController();
	CoursesRegistrationsController(string yearname, string semestername) {
		this->yearName = yearname;
		this->semesterName = semestername;
		loadData();
	}
	~CoursesRegistrationsController() {
		//writeData();
	};
	void createCoursesRegistration(const string& yearName, const string& semesterName);

	bool loadData();

	bool loadDataFromFile(const string& path);

	bool writeData() const;

	bool writeDataToFile(const string& path) const;

	bool checkExistence(string courseID) {
		return this->coursesRegistrations.findIndex([&](CourseRegistration target) {return target.getCourseID() == courseID; }) != -1;
	}

	//--
	void setupDateRegInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos) {

		inputList.push_back(InputRow(71, 1, 50, 3, 0, 15));
		pos.push_back(inputList.back().getInside());
		inputList.back().setTitleBoxWidth(25).setContentBoxWidth(30);
		inputList.back().setDefaultType();

		for (int i = 0; i < 3; ++i) {
			inputList.push_back(InputRow(25 * i + 71, 5, 10, 3, 0, 15));
			pos.push_back(inputList.back().getInside());
			inputList.back().setTitleBoxWidth(15).setContentBoxWidth(5);
			inputList.back().setDefaultType2();
		}

		for (int i = 0; i < 3; ++i) {
			inputList.push_back(InputRow(25 * i + 71, 10, 10, 3, 0, 15));
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
		buttonList.push_back(Button(80, 13, 10, 3));
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
			if (flag && checkExistence(res[0])) flag = false;
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

		TextBox notice = TextBox(77, 16, 40, 3, false).setText("Press ESC for cancel");
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

	void modifyDatesReg() {
		bool isCancel = false;
		//system("cls");
		sll<string> res = inputDatesRegProc(isCancel);

		if (isCancel) return;
		
		Date startDate = Date(stoi(res[1]), stoi(res[2]), stoi(res[3]));
		Date endDate = Date(stoi(res[4]), stoi(res[5]), stoi(res[6]));
		CourseRegistration courseReg(this->yearName, this->semesterName, res[0], startDate, endDate);
		coursesRegistrations.push_back(courseReg);
		renderAccept();
		Sleep(200);
		return;
	}
	//--
	void setupCourseRegTable(Table& table) {
		system("cls");
		table = Table(0, 0, 20);

		table.addTitleRow_back(36, 16, 16);
		table.getRow(0).addText((string)"Course Registration", (string)"Start day", (string)"End day");
		table.addRow_back("Add...");
		for (const CourseRegistration& courseRegistration : (this->coursesRegistrations)) {
			table.addRow_back(courseRegistration.getCourseID(), courseRegistration.getStartDate().convert2String(), courseRegistration.getEndDate().convert2String());
		}

		table.setDefaultType();
		table.render();

		table.setCursorInside();

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

	int courseRegTableProc() {
		int type = 0;
		Table table;
		setupCourseRegTable(table);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	void viewCourseRegTable() {
		system("cls");
		int type = courseRegTableProc();
		while (type != -1) {
			if (type == 1) {
				modifyDatesReg();
			}
			type = courseRegTableProc();
		}
		writeData();
		return;
	}

	void displayCoursesRegistrationTable();

	void changeDates();
};