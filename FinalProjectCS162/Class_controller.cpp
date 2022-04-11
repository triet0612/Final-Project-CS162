#include "Class_controller.h"

//--

int Class_controller::chooseOption(Table& table) {
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
}

void Class_controller::setupClassesTable(Table& table, bool adding) {
	system("cls");
	table = Table(0, 0, 30);

	table.addTitleRow_back(30);
	table.getRow(0).addText((string)"CLasses");
	if (adding) table.addRow_back("Add...");
	for (auto i : classes) {
		table.addRow_back(i.class_name);
	}

	table.setDefaultType();
	table.render();

	table.setCursorInside();
}

int Class_controller::inputClassesProc(bool adding) {
	int type = 0;
	Table table;
	setupClassesTable(table, adding);
	table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
	return type;
}

//--

void Class_controller::viewClasses(string yearname) {
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

void Class_controller::setupClassInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos) {
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

void Class_controller::setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, string& res, bool& isOver) {
	target.setOnClick([&](Button& button) {
		res = inputList[0].getContentBox().getText();
		isOver = true;
		});
}

void Class_controller::setValidPosition(COORD c, int x, int y, int& cur, bool inTxt, bool inBtn, sll<pair<int, int>>& pos, ConsoleGraphics& graphics) {
	if (!inTxt && !inBtn) {
		if (x > 0 || y > 0) cur = (cur + 1) % pos.size();
		else if (x < 0 || y < 0) cur = (cur + pos.size() - 1) % pos.size();
		graphics.gotoXY(pos[cur].first, pos[cur].second, true);
	}
	else if (inTxt) graphics.gotoXY(c.X, c.Y);
}

void Class_controller::renderInputProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver) {
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

void Class_controller::renderCaution() {
	TextBox notice = TextBox(45, 5, 40, 3, false, 0, 12).setText("Do not leave empty");
	notice.render();
}

void Class_controller::renderAccept() {
	TextBox notice = TextBox(45, 5, 40, 3, false, 0, 10).setText("input successfully, loading ...");
	notice.render();
}

string Class_controller::inputClassProc(bool& isCancel) {
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

void Class_controller::createClass(string year) {
	bool cancel;
	string res = inputClassProc(cancel);

	while (!cancel && res.empty()) {
		if (res.empty()) renderCaution();
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

void Class_controller::saveClasses(string yearname) {
	ofstream fout;
	fout.open("Data/" + yearname + "/class.txt");
	for (auto i : classes) {
		fout << i.class_name << endl;
	}
	fout.close();
	return;
}

void Class_controller::loadStudentsOfClasses(string yearname) {
	classes.clear();
	SinglyLinkedList<string> classname = getClasses(yearname);
	for (auto i : classname) {
		Class c_temp;
		c_temp.addStuByCSV(yearname, i);
		classes.push_back(c_temp);
	}
	return;
}

void Class_controller::loadAllClasses() {
	this->classes.clear();
	getAllClasses(this->classes);
}

//--

void Class_controller::setupScoresClassTable(Table& table, int classIdx, Course_controller& coursesController) {
	system("cls");
	table = Table(0, 0, 30);

	int sz = coursesController.courses.size();
	table.addTitleRow_back(4, 16, 16, 16);
	for (int i = 0; i < sz; ++i) table.addTitleRow_back(12);
	table.addTitleRow_back(12);

	table.getRow(0).addText((string)"No", (string)"First Name", (string)"Last Name", (string)"ID");

	for (int i = 0; i < sz; ++i) {
		table.getRow(0).setBoxText(i + 4, coursesController.courses[i].courseID);
		coursesController.loadCourseStudent(i);
	}

	table.getRow(0).setBoxText(sz + 4, "GPA");
	int stuNo = 1, rowIdx = 0, totSubjects = 0, totScore = 0;
	for (auto stu : classes[classIdx].students) {
		table.addRow_back(to_string(stuNo++), stu.First_name, stu.Last_name, stu.ID);
		++rowIdx;
		for (int i = 0; i < sz; ++i) {
			string tmp = coursesController.getFinScoreOfStudent(i, stu.ID);
			table.getRow(rowIdx).setBoxText(i + 4, tmp);
			if (tmp != "X") {
				++totSubjects;
				totScore += stoi(tmp);
			}
		}
		if (totSubjects == 0) table.getRow(rowIdx).setBoxText(sz + 4, "N/A");
		else table.getRow(rowIdx).setBoxText(sz + 4, doubleToStr((double)4 * totScore / totSubjects / 10, 2));
		totSubjects = 0;
		totScore = 0;
	}
	if (classes[classIdx].students.size() == 0) {
		table.addRow_back("", "Empty");
	}

	table.setDefaultType();
	table.render();

	table.setCursorInside();
}

int Class_controller::inputScoresClasseProc(int classIdx, Course_controller& coursesController) {
	int type = 0;
	Table table;
	setupScoresClassTable(table, classIdx, coursesController);
	table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
	return type;
}

void Class_controller::viewScoreOfClass(int classIdx, string semesterName, string yearname) {
	Course_controller coursesController(yearname, semesterName);
	inputScoresClasseProc(classIdx, coursesController);
}

bool Class_controller::checkStudentInClass(Class c, string ID) {
	for (auto i : c.students) {
		if (i.ID == ID) {
			return true;
		}
	}
	return false;
}
