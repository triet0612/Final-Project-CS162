#pragma once
#include "Schoolyear.h"
#include "Class_controller.h"

class Schoolyear_controller {
private:
	bool CheckYear(string yearname) {
		for (auto i : sc.yearList) {
			if (i == yearname) {
				return true;
			}
		}
		return false;
	}
	Class_controller classes;
public:
	Schoolyear sc;

	void saveYearList() {
		ofstream fout;
		fout.open("Data/SchoolYear.txt");
		for (auto i : sc.yearList) {
			fout << i << endl;
		}
		fout.close();
		return;
	}

	void loadYearList() {
		ifstream ifs;
		ifs.open("Data/SchoolYear.txt");
		string tmp;
		sc.yearList.clear();
		while (!ifs.eof()) {
			tmp = "";
			getline(ifs, tmp);
			if (tmp == "") break;
			sc.yearList.push_back(tmp);
		}
		ifs.close();
		return;
	}
	//--
	void setupSchoolYearInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos) {
		for (int i = 0; i < 1; ++i) {
			inputList.push_back(InputRow(40, 4 * i + 1, 50, 3, 0, 15));
			pos.push_back(inputList.back().getInside());
			inputList.back().setTitleBoxWidth(41).setContentBoxWidth(30);
			inputList.back().setDefaultType();
		}

		inputList[0].setTitle("School Year's name (Ex: 2020-2021): ").setContent("");

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

		TextBox notice = TextBox(17, 8, 40, 3, false).setText("Press ESC for cancel");
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

	string inputSchoolYearProc(bool& isCancel) {
		sll<InputRow> inputList;
		sll<Button> buttonList;
		sll<pair<int, int> > pos;
		string res;
		bool isOver = false;

		setupSchoolYearInputList(inputList, buttonList, pos);
		setOnClickSubmitButton(buttonList[0], inputList, res, isOver);

		renderInputProc(inputList, buttonList, pos, isOver);
		isCancel = !isOver;
		return res;
	}

	//--
	void createSchoolYear() {
		bool cancel;
		string res = inputSchoolYearProc(cancel);

		while (!cancel && res == "") {
			if(res == "") renderCaution();
			res = inputSchoolYearProc(cancel);
		}
		if (cancel) return;
		sc.this_year = res;
		sc.yearList.push_front(sc.this_year);
		
		int check = _mkdir(("Data/" + sc.this_year).c_str());
		renderAccept();
		Sleep(100);
		saveYearList();
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

	void setupSchoolYearsTable(Table& table) {
		system("cls");
		table = Table(0, 0, 10);

		table.addTitleRow_back(30);
		table.getRow(0).addText((string)"SCHOOL YEAR");
		table.addRow_back("Add...");
		for (auto i : sc.yearList) {
			table.addRow_back(i);
		}

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int inputSchoolYearProc() {
		int type = 0;
		Table table;
		setupSchoolYearsTable(table);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	void viewSchoolYear() {
		loadYearList();
		int type = inputSchoolYearProc();
		while (type != -1) {
			if (type == 1) {
				createSchoolYear();
			}
			else {
				schoolYearOptions(sc.yearList[type - 2]);
			}
			type = inputSchoolYearProc();
		}
	}
	
	Schoolyear getSchoolYear(string name) {
		loadYearList();
		sc.this_year = name;
		sc.semester_control.loadSemesterList(sc.this_year);
		return sc;
	}

	void addSemesterToSchoolYear(string yearname) {
		sc.semester_control.addSemesterToSchoolYear(yearname);
	}
	
	void viewSemestersInYear() {
		//sc.semester_control.viewSemester();
	}

	//--

	void setupSchoolYearOptionsTable(Table& table, string yearname) {
		system("cls");
		table = Table(0, 0, 10);

		table.addTitleRow_back(30);
		table.getRow(0).addText(yearname);
		table.addRow_back((string)"View Semesters");
		table.addRow_back((string)"View 1st year Classes");

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int inputSchoolYearOptionProc(string yearname) {
		int type = 0;
		Table table;
		setupSchoolYearOptionsTable(table, yearname);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	void schoolYearOptions(string yearname) {
		int type = inputSchoolYearOptionProc(yearname);
		while (type != -1) {
			switch (type)
			{
			case 1: sc.semester_control.viewSemesters(yearname); break;
			case 2: classes.viewClasses(yearname); break;
			default:
				break;
			}
			type = inputSchoolYearOptionProc(yearname);
		}
	}

};