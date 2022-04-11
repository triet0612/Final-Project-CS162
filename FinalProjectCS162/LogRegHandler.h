#pragma once
#include <functional>
#include "StaffController.h"
#include "StudentController.h"
#include "BackgroundController.h"
#include "Table.h"
class LogRegHandler
{
private:
	StaffController staffController;
	StudentController studentController;
public:
	LogRegHandler();;

	~LogRegHandler();;

	int chooseType(Table& table);;

	void setupTypeTable(Table& table);

	int inputTypeProc();

	//---

	void setupLogRegTable(Table& table, int type);

	//---

	int inputLogRegProc(int type);

	void logRegProc();

	void setupLoginInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, int type);

	void setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, pair<string, string>& res, bool& isOver);

	void setValidPosition(COORD c, int x, int y, int& cur, bool inTxt, bool inBtn, sll<pair<int, int> >& pos, ConsoleGraphics& graphics);;

	void renderLogProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver);

	void renderCaution();

	void renderAccept();

	pair<string, string> inputLoginProc(bool& isCancel, int type);

	void logProc(int type);;

	void regProg(int type);;
};

