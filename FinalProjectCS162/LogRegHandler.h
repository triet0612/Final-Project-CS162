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

	int inputTypeProc() {
		int type = 0;
		Table table;
		setupTypeTable(table);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseType(table); });
		return type;
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

	int inputLogRegProc(int type) {
		if (type < 1 || type > 2) return -1;
		int logReg = 0;
		Table table;
		setupLogRegTable(table, type);
		table.update({ -32, 0 }, [&](Table& table) {logReg = chooseType(table); });
		return logReg;
	}

	void logRegProc() {
		while (true) {
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
	}

	void setupLoginInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos) {
		for (int i = 0; i < 2; ++i) {
			inputList.push_back(InputRow(1, 4 * i + 1, 50, 3, 0, 15));
			pos.push_back(inputList.back().getInside());
			inputList.back().setTitleBoxWidth(12).setContentBoxWidth(30);
			inputList.back().setDefaultType();
		}

		inputList[0].setTitle("Username:").setContent("");
		inputList[1].getContentBox().setTxtEncoded(true);
		inputList[1].setTitle("Password:").setContent("");

		inputList[0].setCursorInside();
		buttonList.push_back(Button(2, 8, 10, 3));
		pos.push_back(buttonList.back().getInside());
		buttonList.back().setText("   OK");
		buttonList.back().setDefaultType();

		for (auto& elem : buttonList) elem.render();
		for (auto& elem : inputList) elem.update();
		for (auto& elem : inputList) elem.render();
	}

	void setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, pair<string, string>& res, bool& isOver) {
		target.setOnClick([&](Button& button) {
			res.first = inputList[0].getContentBox().getText();
			res.second = inputList[1].getContentBox().getText();
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

	void renderLogProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver) {
		int cur = 0;
		ConsoleGraphics& graphics = ConsoleGraphics::getInstance();

		TextBox notice = TextBox(15, 8, 40, 3, false).setText("Press ESC for cancel");
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
		TextBox notice = TextBox(5, 10, 40, 3, false, 0, 12).setText("Wrong username or password");
		notice.render();
	}

	void renderAccept() {
		TextBox notice = TextBox(5, 10, 40, 3, false, 0, 10).setText("Login successfully, loading ...");
		notice.render();
	}

	pair<string, string> inputLoginProc(bool& isCancel) {
		sll<InputRow> inputList;
		sll<Button> buttonList;
		sll<pair<int, int> > pos;
		pair<string, string> res;
		bool isOver = false;

		setupLoginInputList(inputList, buttonList, pos);
		setOnClickSubmitButton(buttonList[0], inputList, res, isOver);

		renderLogProc(inputList, buttonList, pos, isOver);
		isCancel = !isOver;
		return res;
	}

	void logProc(int type) {
		bool isCancel;
		string username, password;
		system("cls");
		pair<string, string> ans = inputLoginProc(isCancel);
		username = ans.first;
		password = ans.second;

		switch (type)
		{
		case 1:
			while (!staffController.loginProc(username, password) && !isCancel) {
				renderCaution();
				ans = inputLoginProc(isCancel);
				username = ans.first;
				password = ans.second;
			};
			if (isCancel) return;
			else {
				renderAccept();
				Sleep(1500);
				staffController.proc();
			}
			break;
		case 2:
			while (!studentController.loginProc(username, password) && !isCancel) {
				renderCaution();
				ans = inputLoginProc(isCancel);
				username = ans.first;
				password = ans.second;
			};
			if (isCancel) return;
			else {
				renderAccept();
				Sleep(1500);
				return;
				staffController.proc();
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

