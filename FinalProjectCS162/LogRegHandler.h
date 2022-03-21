#pragma once
#include <functional>
#include "StaffController.h"
#include "StudentController.h"
#include "Table.h"
class LogRegHandler
{
private:
	StaffController staffController;
	StudentController studentController;
	Table table;
public:
	LogRegHandler() {

	};

	~LogRegHandler() {

	};

	int chooseType(Table& table) {
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

	void setupTypeTable(Table& table) {
		system("cls");
		table = Table(0, 0, 4);

		table.addTitleRow_back(30);
		table.getRow(0).addText("YOU ARE ?");
		table.addRow_back("Staff");
		table.addRow_back("Student");
		table.addRow_back("I want to get out of here");

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	void setupLogRegTable(Table& table, int type) {
		system("cls");
		table = Table(0, 0, 4);

		table.addTitleRow_back(40);
		if (type == 1)  table.getRow(0).addText("YOU ARE STAFF, YOU WANT TO ?");
		else table.getRow(0).addText("YOU ARE STUDENT, YOU WANT TO ?");
		table.addRow_back("Login");
		table.addRow_back("Register");
		table.addRow_back("Oops, wrong way, let's return");

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int inputTypeProc() {
		int type = 0;
		setupTypeTable(table);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseType(table); });
		return type;
	}

	int inputLogRegProc(int type) {
		if (type < 1 || type > 2) return -1;
		int logReg = 0;

		setupLogRegTable(table, type);
		table.update({ -32, 0 }, [&](Table& table) {logReg = chooseType(table); });
		return logReg;
	}

	void logRegProc() {

		int type = -1;
		int logReg = 3;
		while (logReg == 3) {
			type = inputTypeProc();
			logReg = inputLogRegProc(type);
		}
		if (logReg == -1) return;


		switch (logReg)
		{
		case 1: logProc(type); break;
		case 2: regProg(type); break;
		default:
			break;
		}

	}

	void logProc(int type) {
		switch (type)
		{
		case 1:
			if (!staffController.loginProc()) {
				cout << "Wrong password or username\n";
			}
			else {
				cout << "Correct\n";
				staffController.proc();
			}
			break;
		case 2:
			if (!studentController.loginProc()) {
				cout << "Wrong password or username\n";
			}
			else {
				cout << "Correct\n";
			}
			break;
		default:
			break;
		}
	};

	void regProg(int type) {
		switch (type)
		{
		case 1:
			staffController.regProc(); break;
		case 2:
			studentController.regProc(); break;
		default:
			break;
		}
	};
};

