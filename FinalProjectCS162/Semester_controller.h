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
	
	bool checkSemester(string name) {
		for (auto i : semesterlist) {
			if (i.semester_name == name) {
				return true;
			}
		}
		return false;
	}
	
	void saveSemester(string yearname) {
		ofstream fout;
		fout.open("Data/" + yearname + "/semesters.txt");
		for (auto i : semesterlist) {
			fout << i.semester_name << " " << i.startdate << " " << i.endate << endl;
		}
		fout.close();
		return;
	}

	void create_semester(string yearname, sll<string> data) {

		semester s("s" + data[0], yearname, Date(stoi(data[1]), stoi(data[2]), stoi(data[3])), Date(stoi(data[4]), stoi(data[5]), stoi(data[6])));
		semesterlist.push_back(s);
		cur_semester = s;
		int checker = _mkdir(("Data/" + yearname + '/' + data[0]).c_str());
		checker = _mkdir(("Data/" + yearname + '/' + data[0] + "/Mark").c_str());
		checker = _mkdir(("Data/" + yearname + '/' + data[0] + "/Studentlist").c_str());
		saveSemester(yearname);

		ofstream ofs("Data/CurrentSemester.txt");
		ofs << yearname << "\n";
		ofs << s.semester_name << "\n";
		ofs.close();
		return;
	}
	
	void loadSemesterList(string yearname) {
		ifstream fin;
		string path = "Data/" + yearname + "/semesters.txt";
		fin.open(path);
		string temp1;
		string temp2;
		string temp3;
		semesterlist.clear();
		while (!fin.eof()) {
			temp1 = temp2 = temp3 = "";
			fin >> temp1;
			fin >> temp2;
			fin >> temp3;
			Date d1;
			Date d2;
			if (temp2 == "" || temp3 == "") break;
			d1 = temp2;
			d2 = temp3;
			semester t(temp1, yearname, d1, d2);
			semesterlist.push_back(t);
		}
		fin.close();
		saveSemester(yearname);
		return;
	}

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

	void setupSemestersTable(Table& table) {
		system("cls");
		table = Table(0, 0, 5);

		table.addTitleRow_back(15, 17, 17);
		table.getRow(0).addText((string)" SEMESTERS", (string)" Start date", (string)" End date");
		table.addRow_back((string)"Add...");
		for (auto i : semesterlist) {
			table.addRow_back(i.semester_name, i.startdate.convert2String(), i.endate.convert2String());
		}

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int inputSemesterTableProc() {
		int type = 0;
		Table table;
		setupSemestersTable(table);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}
	
	void viewSemesters(string yearname) {
		loadSemesterList(yearname);
		int type = inputSemesterTableProc();
		while (type != -1) {
			if (type == 1){
				addSemesterToSchoolYear(yearname);
			}
			else {
				viewSemesterOptions(type - 2, yearname);
			}
			type = inputSemesterTableProc();
		}
		return;
	}
	
	void createCourseReg(semester& s) {
		s.courseRegs.modifyDatesReg();
		//s.course_reg.ModifyRegCourseDates();
		return;
	}

	//--

	void setupSemesterInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos) {

		inputList.push_back(InputRow(1, 1, 50, 3, 0, 15));
		pos.push_back(inputList.back().getInside());
		inputList.back().setTitleBoxWidth(25).setContentBoxWidth(4);
		inputList.back().setDefaultType();

		for (int i = 0; i < 3; ++i) {
			inputList.push_back(InputRow(25*i + 1, 5, 10, 3, 0, 15));
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

		inputList[0].setTitle("Semester's number: ").setContent("").getContentBox().setNumberMode(true);
		Date cur = Date::getCurrentDate();
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

	void setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, sll<string>& res, bool& isOver) {
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

	void renderInputSemesterProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver) {
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

	sll<string> inputSemesterProc(bool& isCancel) {
		sll<InputRow> inputList;
		sll<Button> buttonList;
		sll<pair<int, int> > pos;
		sll<string> res;
		bool isOver = false;

		setupSemesterInputList(inputList, buttonList, pos);
		setOnClickSubmitButton(buttonList[0], inputList, res, isOver);

		renderInputSemesterProc(inputList, buttonList, pos, isOver);
		isCancel = !isOver;
		return res;
	}

	//--
	void addSemesterToSchoolYear(string yearname) {
		bool isCancel = false;
		system("cls");
		sll<string> res = inputSemesterProc(isCancel);

		loadSemesterList(yearname);

		while (!isCancel && checkSemester("s" + res[0])) {
			//cout << "Semester already there, input again: " << endl;
			renderCaution("Already exist");
			res = inputSemesterProc(isCancel);
		}
		if (isCancel) return;
		create_semester(yearname, res);
		renderAccept();
		Sleep(200);
		return;
	}

	//--
	void setupSemesterInfoTable(Table& table, int id, string yearname) {
		system("cls");
		table = Table(0, 0, 3);

		table.addTitleRow_back(30);
		table.getRow(0).addText((string)" SEMESTER " + to_string(id + 1) + " Of " + yearname);

		table.addRow_back("Start: " + semesterlist[id].startdate.convert2String());
		table.addRow_back("End: " + semesterlist[id].endate.convert2String());

		table.setDefaultType();
		table.render();

	}

	void semesterInfoTableProc(int id, string yearname) {
		Table table;
		setupSemesterInfoTable(table, id, yearname);
	}

	void viewSemesterInfoTable(int id, string yearname) {
		system("cls");
		semesterInfoTableProc(id, yearname);
		return;
	}

	//--
	void setupSemesterOptionsTable(Table& table) {
		table = Table(0, 7, 5);

		table.addTitleRow_back(40);
		table.getRow(0).addText((string)" OPTIONS");
		table.addRow_back("Create course registration");
		table.addRow_back("View courses");
		table.addRow_back("View Score of Class");

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

	void viewScoreClass(string semestername, string yearname) {
		Class_controller classController;
		classController.loadAllClasses();
		int idx = classController.inputClassesProc(false) - 1;
		classController.viewScoreOfClass(idx,semestername, yearname);
	}

	void viewSemesterOptions(int id, string yearname) {
		viewSemesterInfoTable(id, yearname);
		int type = inputSemesterOptionTableProc();
		
		while (type != -1) {
			switch (type)
			{
			case 1:
				semesterlist[id].courseRegs.displayCoursesRegistrationTable(); break;
			case 2:
				semesterlist[id].courses.courseProc(yearname, "s" + to_string(id + 1)); break;
			case 3:
				viewScoreClass("s" + to_string(id + 1),yearname);
				break;
			default:
				break;
			}
			viewSemesterInfoTable(id, yearname);
			type = inputSemesterOptionTableProc();
		}
		return;
	}


};
