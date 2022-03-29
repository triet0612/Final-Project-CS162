#pragma once
#include <iostream>
#include <direct.h>
#include <string.h>
#include "semester.h"
#include "SinglyLinkedList.h"
#include "Date.h"
#include "Table.h"
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
		fout.open('/' + yearname + "/semesters.txt");
		for (auto i : semesterlist) {
			fout << i.semester_name << " " << i.startdate << " " << i.endate << endl;
		}
		fout.close();
		return;
	}

	void create_semester(string yearname, string semestername) {
		cout << "Input start date: " << endl;
		int day, month, year;
		cin >> day >> month >> year;
		Date start(day, month, year);
		cout << "Input end date: " << endl;
		cin >> day >> month >> year;
		Date end(day, month, year);
		semester s(semestername, start, end);
		semesterlist.push_back(s);
		cur_semester = s;
		int checker = _mkdir(("Data/" + yearname + '/' + semestername).c_str());
		checker = _mkdir(("Data/" + yearname + '/' + semestername + "Mark").c_str());
		checker = _mkdir(("Data/" + yearname + '/' + semestername + "Studentlist").c_str());
		return;
	}
	
	void getSemesterList(string yearname) {
		ifstream fin;
		string path = "Data/" + yearname + "/semesters.txt";
		fin.open(path);
		string temp1;
		string temp2;
		string temp3;
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
			semester t(temp1, d1, d2);
			semesterlist.push_back(t);
		}
		fin.close();
		saveSemester(yearname);
		return;
	}

	int chooseSemester(Table& table) {
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

	void setupSchoolYearTable(Table& table) {
		system("cls");
		table = Table(0, 0, 4);

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

	int inputSemesterProc() {
		int type = 0;
		Table table;
		setupSchoolYearTable(table);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseSemester(table); });
		return type;
	}
	
	void viewSemester(string yearname) {
		getSemesterList(yearname);
		int type = inputSemesterProc();
		while (type != -1) {
			if (type == 1){
				//addSemesterToSchoolYear(yearname);
			}
			type = inputSemesterProc();
		}
		return;
	}
	
	semester& getSemester(string yearname, int num) {
		getSemesterList(yearname);
		semester ans;
		for (auto i : semesterlist) {
			if (i.semester_name == "s" + num) {
				ans = i;
				break;
			}
		}
		return ans;
	}
	
	void createCourseReg(semester& s, string yearname) {
		s.course_reg.changeDates();
		return;
	}
	
	void viewCourse(semester& s) {
		s.course.viewListOfCourses();
	}

	void addSemesterToSchoolYear(string yearname) {
		getSemesterList(yearname);
		string semestername;
		cout << "Input semester: " << endl;
		cin >> semestername;
		while (!checkSemester(semestername)) {
			cout << "Semester already there, input again: " << endl;
			cin >> semestername;
		}
		create_semester(yearname, semestername);
		return;
	}
};
