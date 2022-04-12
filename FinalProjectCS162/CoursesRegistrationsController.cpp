#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "CoursesRegistrationsController.h"
#include "helper.h"

CoursesRegistrationsController::CoursesRegistrationsController() {}

CoursesRegistrationsController::CoursesRegistrationsController(const string& yearname, const string& semestername) {
	this->yearName = yearname;
	this->semesterName = semestername;
	loadCreatedCourseRegs();
};

CoursesRegistrationsController::~CoursesRegistrationsController() {
	//writeData();
};

bool CoursesRegistrationsController::saveCreatedCourseRegs(const string& path) const {
	ofstream foutput;
	foutput.open(path);
	for (const CourseRegistration& courseRegistration : (this->coursesRegistrations)) {
		foutput << courseRegistration.getCourseID() << '\n';
		printDates(foutput, courseRegistration.getStartDate(), " ");
		foutput << " ";
		printDates(foutput, courseRegistration.getEndDate(), " ");
		foutput << '\n';
	}
	foutput.close();


	return true;
}
bool CoursesRegistrationsController::checkExistence(const string& courseID) const {
	return this->coursesRegistrations.findIndex([&](CourseRegistration target) {return target.getCourseID() == courseID; }) != -1;
}

//--

void CoursesRegistrationsController::setupDateRegInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos) {

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
void CoursesRegistrationsController::setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, sll<string>& res, bool& isOver)
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
void CoursesRegistrationsController::setValidPosition(COORD c, int x, int y, int& cur, bool inTxt, bool inBtn, sll<pair<int, int>>& pos, ConsoleGraphics& graphics) {
	if (!inTxt && !inBtn) {
		if (x > 0 || y > 0) cur = (cur + 1) % pos.size();
		else if (x < 0 || y < 0) cur = (cur + pos.size() - 1) % pos.size();
		graphics.gotoXY(pos[cur].first, pos[cur].second, true);
	}
	else if (inTxt) graphics.gotoXY(c.X, c.Y);
}
void CoursesRegistrationsController::renderInputDatesRegProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver) {
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
void CoursesRegistrationsController::renderCaution(const string& s) {
	TextBox notice = TextBox(5, 12, 40, 3, false, 0, 12).setText(s);
	notice.render();
}
void CoursesRegistrationsController::renderAccept() {
	TextBox notice = TextBox(5, 12, 40, 3, false, 0, 10).setText("input successfully, loading ...");
	notice.render();
}
sll<string> CoursesRegistrationsController::inputDatesRegProc(bool& isCancel) {
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
void CoursesRegistrationsController::modifyDatesReg() {
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

void CoursesRegistrationsController::setupCourseRegTable(Table& table) {
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
int CoursesRegistrationsController::chooseOption(Table& table) {
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
int CoursesRegistrationsController::courseRegTableProc() {
	int type = 0;
	Table table;
	setupCourseRegTable(table);
	table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
	return type;
}
void CoursesRegistrationsController::viewCourseRegTable() {
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
;

bool CoursesRegistrationsController::loadCreatedCoursesRegsFromPath(const string& path) {
	ifstream finput(path);
	if (finput) {
		CourseRegistration courseRegistration;
		(this->coursesRegistrations).clear();
		courseRegistration.createRegistration(this->yearName, this->semesterName);
		while (courseRegistration.loadData(finput)) 
			(this->coursesRegistrations).push_back(courseRegistration);
		finput.close();
		return true;
	}
	finput.close();
	return false;
};

bool CoursesRegistrationsController::loadCreatedCourseRegs() {
	return this->loadCreatedCoursesRegsFromPath("Data/" + (this->yearName) + "/" + (this->semesterName) + "/coursesRegistrationsDates.txt");
};

bool CoursesRegistrationsController::writeData() const {
	ofstream ofs( "Data/" + (this->yearName) + "/" + (this->semesterName) + "/EnrolledCourses.csv");
	ofs << "Student ID";
	for (const CourseRegistration& courseRegistration : (this->coursesRegistrations)) {
		ofs << "," << courseRegistration.getCourseID();
	}

	ofs.close();
	return this->saveCreatedCourseRegs("Data/" + (this->yearName) + "/" + (this->semesterName) + "/coursesRegistrationsDates.txt");
};

CourseRegistration& CoursesRegistrationsController::getCourseRegistration(const string& courseID) {
	for (CourseRegistration& courseRegistration : (this->coursesRegistrations))
		if (courseRegistration.getCourseID() == courseID)
			return courseRegistration;
};

void CoursesRegistrationsController::createCoursesRegistration(const string& yearName, const string& semesterName) {
	(this->yearName) = yearName;
	(this->semesterName) = semesterName;
}
void CoursesRegistrationsController::delCourseReg(const string& courseID) {
	int id = this->coursesRegistrations.findIndex([&](CourseRegistration target) {return target.getCourseID() == courseID; });
	if (id == -1) return;
	this->coursesRegistrations.deleteAt(id);
	this->saveCreatedCourseRegs("Data/" + (this->yearName) + "/" + (this->semesterName) + "/coursesRegistrationsDates.txt");
}
void CoursesRegistrationsController::delEnrolledCourseColumn(const string& courseID) {
	if (this->rawRegsData.size() <= 0) return;
	int id = this->rawRegsData[0].findIndex([&](string target) {return target == courseID; });
	if (id == -1) return;
	for (auto& x : rawRegsData) {
		x.deleteAt(id);
	}
	this->saveEnrolledCourses();
}
void CoursesRegistrationsController::loadEnrolledCourses() {
	this->rawRegsData.clear();
	ifstream ifs("Data/" + this->yearName + "/" + this->semesterName + "/" + "EnrolledCourses.csv");
	string tmp;
	stringstream ss;
	while (!ifs.eof()) {
		sll<string> row;
		tmp = "";
		getline(ifs, tmp);
		if (tmp == "") break;
		ss.clear();
		ss.str(tmp);
		while (getline(ss, tmp, ',')) {
			row.push_back(tmp);
		}
		this->rawRegsData.push_back(row);
	}
	ifs.close();
}
void CoursesRegistrationsController::getInfoEnrollmentStudent(int stuId, sll<bool>& status, sll<int>& curNumsStu) {
	int numSubjects = this->rawRegsData[0].size() - 1;
	for (int i = 0; i < numSubjects; ++i) {
		curNumsStu.push_back(0);
		status.push_back(false);
	}
	for (auto row : this->rawRegsData) {
		for (int i = 0; i < numSubjects; ++i) {
			if (row[1 + i] == "1") {
				if (row[0] == to_string(stuId)) {
					status[i] = true;
				}
				++curNumsStu[i];
			}

		}

	}
}
void CoursesRegistrationsController::updateStatusEnrolledCourses(int stuId, sll<bool>& status) {
	int idx = this->rawRegsData.findIndex([&](sll<string> target) {return target[0] == to_string(stuId); });
	sll<string> tmp;
	tmp.push_back(to_string(stuId));
	for (auto elem : status) {
		if (elem) tmp.push_back("1");
		else tmp.push_back("0");
	}
	if (idx != -1) this->rawRegsData[idx] = tmp;
	else this->rawRegsData.push_back(tmp);
}
void CoursesRegistrationsController::saveEnrolledCourses() {
	ofstream ofs("Data/" + this->yearName + "/" + this->semesterName + "/" + "EnrolledCourses.csv");
	for (auto row : this->rawRegsData) {
		int numComma = row.size() - 1;
		for (auto elem : row) {
			ofs << elem;
			if (numComma > 0) ofs << ",", --numComma;
			else ofs << "\n";
		}
	}
	ofs.close();

}
;

bool CoursesRegistrationsController::containsCourseRegistration(const string& courseID) {
	for (const CourseRegistration& courseRegistration : (this->coursesRegistrations))
		if (courseRegistration.getCourseID() == courseID)
			return true;
	return false;
};
