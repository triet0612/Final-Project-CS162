#include <iostream>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

#include "CoursesList.h"
#include "helper.h"


//--

int CoursesList::viewCourses(const string& yearname, const string& semester) {
	loadCourse(yearname, semester);
	return inputCoursesTableProc();
}

void CoursesList::displayListOfCourses() const {
	int number_length = strlen("no"),
		credits_length = strlen("credits"),
		maximumStudent_length = strlen("Maximum student width"),
		nameOfCourse_length = strlen("Name of course"),
		courseID_length = strlen("Course ID"),
		nameOfTeacher_length = strlen("Name of teacher"),
		daySession1_length = strlen("Day session 1"),
		daySession2_length = strlen("Day session 2"),
		totalLength;
	// Find the require length for each information
	for (const Course& course : (*this)) {
		number_length = max(number_length, getNumberOfDigits(course.number));
		credits_length = max(credits_length, getNumberOfDigits(course.credits));
		maximumStudent_length = max(maximumStudent_length, getNumberOfDigits(course.maximumStudent));
		courseID_length = max(courseID_length, (int)course.courseID.size());
		nameOfTeacher_length = max(nameOfTeacher_length, (int)course.nameOfTeacher.size());
		nameOfCourse_length = max(nameOfCourse_length, (int)course.nameOfCourse.size());
		daySession1_length = max(daySession1_length, (int)course.daySession1.size());
		daySession2_length = max(daySession2_length, (int)course.daySession2.size());
	}
	number_length += 2;
	credits_length += 2;
	maximumStudent_length += 2;
	courseID_length += 2;
	nameOfTeacher_length += 2;
	nameOfCourse_length += 2;
	daySession1_length += 2;
	daySession2_length += 2;
	totalLength = number_length + credits_length + maximumStudent_length + courseID_length + nameOfCourse_length + nameOfTeacher_length + daySession1_length + daySession2_length + 9;
	cout << string(totalLength, '-') << '\n';
	cout << '|'
		<< setw(number_length) << "No" << '|'
		<< setw(courseID_length) << "Course ID" << '|'
		<< setw(nameOfCourse_length) << "Name of course" << '|'
		<< setw(nameOfTeacher_length) << "Name of teacher" << '|'
		<< setw(credits_length) << "Credits" << '|'
		<< setw(maximumStudent_length) << "Maximum student" << '|'
		<< setw(daySession1_length) << "Day session 1" << '|'
		<< setw(daySession2_length) << "Day session 2" << '|'
		<< '\n';
	cout << string(totalLength, '-') << '\n';
	for (const Course& course : (*this))
		cout << '|'
		<< setw(number_length) << course.number << '|'
		<< setw(courseID_length) << course.courseID << '|'
		<< setw(nameOfCourse_length) << course.nameOfCourse << '|'
		<< setw(nameOfTeacher_length) << course.nameOfTeacher << '|'
		<< setw(credits_length) << course.credits << '|'
		<< setw(maximumStudent_length) << course.maximumStudent << '|'
		<< setw(daySession1_length) << course.daySession1 << '|'
		<< setw(daySession2_length) << course.daySession2 << '|'
		<< '\n';
	cout << string(totalLength, '-') << '\n';
};

bool CoursesList::containsCourse(const string& courseID) const {
	for (const Course& course : (*this))
		if (course.courseID == courseID)
			return true;
	return false;
};

void CoursesList::updateInformation() {
	/*
	Remember to write file (outside of the function) after updating information of courses list
	*/
	int option;
	string courseID;
	while (true) {
		system("cls");
		this->displayListOfCourses();
		cout << "1. Escape (stop updating courses information)\n"
			<< "2. Update course information\n"
			<< "3. Remove a course\n"
			<< "4. Add new course\n"
			<< "Please enter your option: ";
		if (!readInteger(option) || option < 1 || option > 4) {
			cout << "Invalid option\n";
			system("pause");
			continue;
		}
		if (option == 1)
			break;
		if (option == 2) {
			cout << "Please enter the id of course you want to update information: ";
			getline(cin, courseID);
			if (!(this->containsCourse(courseID))) {
				cout << "There was no course with course id " << courseID << '\n';
				system("pause");
				continue;
			}
			else {
				for (Course& course : (*this))
					if (course.courseID == courseID) {
						course.updateCourse();
						cout << "Information is updated successfully\n";
						system("pause");
						break;
					}
			}
		}
		else if (option == 3) {
			cout << "Please enter the id of course you want to remove: ";
			getline(cin, courseID);
			if (!(this->containsCourse(courseID))) {
				cout << "There was no course with course id " << courseID << '\n';
				system("pause");
				continue;
			}
			else {
				this->deleteNode([&](const Course& course) -> bool {
					return course.courseID == courseID;
					});
				cout << "Course is removed successfully\n";
				system("pause");
			}
		}
		else if (option == 4) {
			cout << "Please enter the id of the new course you want to add: ";
			getline(cin, courseID);
			if ((this->containsCourse(courseID))) {
				cout << "There has been already a course with course id " << courseID << " in the courses list\n";
				system("pause");
				continue;
			}
			else {
				Course course;
				course.courseID = courseID;
				//course.getCourseInformation();
				this->push_back(course);
				cout << "New course is added successfully\n";
				system("pause");
			}
		}
	}
}

void CoursesList::saveCourses(const string& yearname, const string& semester) {
	writeFile("Data/" + yearname + '/' + semester + "/Courses.csv");
}
;

void CoursesList::reNumberingCourses() {
	int id = 1;
	for (auto& elem : (*this)) {
		elem.number = id++;
	}
}

bool CoursesList::readFile(const string& path) {
	ifstream finput(path);
	this->clear();
	if (finput) {
		Course course;
		finput.ignore(5000, '\n'); //ignore first line
		while (course.readData(finput))
			this -> push_back(course);
		finput.close();
		return true;
	}
	finput.close();
	return false;
}

bool CoursesList::loadCourse(string yearname, string semester) {
	return readFile("Data/" + yearname + "/" + semester + "/Courses.csv");
}

//--

int CoursesList::chooseOption(Table& table) {
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
void CoursesList::setupCoursesTable(Table& table) {
	system("cls");
	table = Table(0, 0, 10);

	table.addTitleRow_back(12, 16, 40, 30, 13, 18, 20); table.addTitleRow_back(20);
	table.getRow(0).addText((string)"No", (string)"Course ID", (string)"Name of course", (string)"Name of teacher", (string)"credits", (string)"Max student"
		, (string)"Day session 1", (string)"Day session 2");
	table.addRow_back((string)"Add...");
	for (const Course& course : (*this)) {
		table.addRow_back(to_string(course.number), course.courseID, course.nameOfCourse, course.nameOfTeacher,
			to_string(course.credits), to_string(course.maximumStudent), course.daySession1, course.daySession2);
	}

	table.setDefaultType();
	table.render();

	table.setCursorInside();
}
int CoursesList::inputCoursesTableProc() {
	int type = 0;
	Table table;
	setupCoursesTable(table);
	table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
	return type;
}
;

bool CoursesList::writeFile(const string& path) const {
	ofstream foutput(path);
	if (foutput) {
		foutput << "No,CourseID,NameOfCourse,NameOfTeacher,Credits,MaximumStudent,Day-Session1,Day-Session2\n";
		for (const Course& course : (*this))
			course.writeData(foutput);
		return true;
	}
	foutput.close();
	return false;
};

bool CoursesList::checkSessionsConflicted(const bool* enrolled) const {
	const int numberOfCourses = this->size();
	SinglyLinkedList<pair<string, pair<int, int> > > sessions[2];
	for (int i = 0; i < numberOfCourses; ++i)
		if (enrolled[i]) {
			sessions[0].push_back((*this)[i].getDaySession1());
			sessions[1].push_back((*this)[i].getDaySession2());
		}
	const int numberOfEnrolledCourses = sessions[0].size();
	for (int i = 1; i < numberOfEnrolledCourses; ++i)
		for (int j = 0; j < i; ++j)
			for (int x = 0; x < 2; ++x)
				for (int y = 0; y < 2; ++y)
					if (sessions[x][i].first == sessions[y][j].first && checkIntersection(sessions[x][i].second, sessions[y][j].second))
						return true;
	return false;
}

Course& CoursesList::getCourse(const string& courseID) {
	for (Course& course : (*this))
		if (course.courseID == courseID)
			return course;
}
//--

void CoursesList::setupCourseInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, sll<string> initvalues, bool modify) {

	inputList.push_back(InputRow(56, 12, 50, 3, 0, 15));
	pos.push_back(inputList.back().getInside());
	inputList.back().setTitleBoxWidth(25).setContentBoxWidth(30);
	inputList.back().setDefaultType();

	for (int i = 0; i < 2; ++i) {
		inputList.push_back(InputRow(56, 16 + 3 * i, 10, 3, 0, 15));
		pos.push_back(inputList.back().getInside());
		inputList.back().setTitleBoxWidth(20).setContentBoxWidth(40);
		inputList.back().setDefaultType2();
	}


	for (int i = 0; i < 2; ++i) {
		inputList.push_back(InputRow(34 * i + 56, 22, 10, 3, 0, 15));
		pos.push_back(inputList.back().getInside());
		inputList.back().setTitleBoxWidth(20).setContentBoxWidth(6);
		inputList.back().setDefaultType2();
	}


	for (int i = 0; i < 2; ++i) {
		inputList.push_back(InputRow(34 * i + 56, 25, 10, 3, 0, 15));
		pos.push_back(inputList.back().getInside());
		inputList.back().setTitleBoxWidth(20).setContentBoxWidth(6 - 2 * i);
		inputList.back().setDefaultType2();
	}

	for (int i = 0; i < 2; ++i) {
		inputList.push_back(InputRow(34 * i + 56, 28, 10, 3, 0, 15));
		pos.push_back(inputList.back().getInside());
		inputList.back().setTitleBoxWidth(20).setContentBoxWidth(6 - 2 * i);
		inputList.back().setDefaultType2();
	}

	while (initvalues.size() < inputList.size()) initvalues.push_back("");

	inputList[0].setTitle("Course ID: ").setContent(initvalues[0]);

	inputList[1].setTitle("Course's Name:").setContent(initvalues[1]).getContentBox();
	inputList[2].setTitle("Teacher:").setContent(initvalues[2]).getContentBox();

	inputList[3].setTitle("Credit:").setContent(initvalues[3]).getContentBox().setNumberMode(true);
	inputList[4].setTitle("Max:").setContent(initvalues[4]).getContentBox().setNumberMode(true);

	inputList[5].setTitle("Session 1 - Date:").setContent(initvalues[5]).getContentBox();
	inputList[6].setTitle("S (1, 2, 3, 4)").setContent(initvalues[6]).setContentBoxWidth(4).getContentBox().setNumberMode(true);

	inputList[7].setTitle("Session 2 - Date:").setContent(initvalues[7]).getContentBox();
	inputList[8].setTitle("S (1, 2, 3, 4)").setContent(initvalues[8]).setContentBoxWidth(4).getContentBox().setNumberMode(true);

	inputList[0].setCursorInside();
	buttonList.push_back(Button(65, 31, 10, 3));
	pos.push_back(buttonList.back().getInside());
	buttonList.back().setText("   OK");
	buttonList.back().setDefaultType();

	if (modify) {
		buttonList.push_back(Button(77, 31, 10, 3));
		pos.push_back(buttonList.back().getInside());
		buttonList.back().setText(" Delete");
		buttonList.back().setDefaultType();
	}

	for (auto& elem : buttonList) elem.render();
	for (auto& elem : inputList) elem.update();
	for (auto& elem : inputList) elem.render();
}
void CoursesList::setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, sll<string>& res, bool& isOver) {
	target.setOnClick([&](Button& button) {
		res.clear();
		bool flag = true;
		for (auto elem : inputList) {
			res.push_back(elem.getContentBox().getText());
			if (res.back() == "") flag = false;
		}
		if (!flag) {
			renderCaution("Do not leave empty");
		}
		if (flag && (res[5] != "MON" && res[5] != "TUE" && res[5] != "WED" && res[5] != "THU" && res[5] != "FRI" && res[5] != "SAT")) {
			renderCaution("Wrong date format");
			flag = false;
		}

		if (flag && (res[7] != "MON" && res[7] != "TUE" && res[7] != "WED" && res[7] != "THU" && res[7] != "FRI" && res[7] != "SAT")) {
			renderCaution("Wrong date format");
			flag = false;
		}

		if (flag && (stoi(res[6]) <= 0 || stoi(res[6]) > 4)) {
			renderCaution("Time set in range[1, 4]");
			flag = false;
		}
		if (flag && (stoi(res[8]) <= 0 || stoi(res[8]) > 4)) {
			renderCaution("Time set in range[1, 4]");
			flag = false;
		}
		isOver = flag;
		});
}
void CoursesList::setValidPosition(COORD c, int x, int y, int& cur, bool inTxt, bool inBtn, sll<pair<int, int>>& pos, ConsoleGraphics& graphics) {
	if (!inTxt && !inBtn) {
		if (x > 0 || y > 0) cur = (cur + 1) % pos.size();
		else if (x < 0 || y < 0) cur = (cur + pos.size() - 1) % pos.size();
		graphics.gotoXY(pos[cur].first, pos[cur].second, true);
	}
	else if (inTxt) graphics.gotoXY(c.X, c.Y);
}
void CoursesList::renderInputCourseProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver) {
	int cur = 0;
	ConsoleGraphics& graphics = ConsoleGraphics::getInstance();

	TextBox notice = TextBox(77, 33, 40, 3, false).setText("Press ESC for cancel");
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
void CoursesList::renderCaution(string s) {
	TextBox notice = TextBox(5, 32, 40, 3, false, 0, 12).setText(s);
	notice.render();
}
void CoursesList::renderAccept() {
	TextBox notice = TextBox(5, 32, 40, 3, false, 0, 10).setText("input successfully, loading ...");
	notice.render();
}
sll<string> CoursesList::inputCourseProc(bool& isCancel, sll<string> initvalues) {
	sll<InputRow> inputList;
	sll<Button> buttonList;
	sll<pair<int, int> > pos;
	sll<string> res;
	bool isOver = false;
	setupCourseInputList(inputList, buttonList, pos, initvalues);
	setOnClickSubmitButton(buttonList[0], inputList, res, isOver);

	renderInputCourseProc(inputList, buttonList, pos, isOver);
	isCancel = !isOver;
	return res;
}
void CoursesList::createCourse() {
	bool isCancel = false;
	//system("cls");
	sll<string> initvalues;
	for (int i = 0; i < 9; ++i) initvalues.push_back("");
	initvalues[4] = "50";
	sll<string> res = inputCourseProc(isCancel, initvalues);

	if (isCancel) return;
	//create_semester(yearname, res);
	Course c;
	c.number = this->size() + 1;
	c.courseID = res[0]; c.nameOfCourse = res[1]; c.nameOfTeacher = res[2]; c.credits = stoi(res[3]); c.maximumStudent = stoi(res[4]);
	c.daySession1 = res[5] + " " + c.timeset[stoi(res[6]) - 1];
	c.daySession2 = res[7] + " " + c.timeset[stoi(res[8]) - 1];
	this->push_back(c);
	renderAccept();
	Sleep(200);
	return;
}

//--

void CoursesList::setOnClickDeleteButton(Button& target, sll<InputRow>& inputList, bool& isOver, bool& isDeleted) {
	target.setOnClick([&](Button& button) {
		isOver = true;
		isDeleted = true;
		});
}
void CoursesList::buildInitValues(sll<string>& initvalues, Course& c) {
	//initvalues.push_back(to_string(c.number));
	initvalues.push_back(c.courseID);
	initvalues.push_back(c.nameOfCourse);
	initvalues.push_back(c.nameOfTeacher);
	initvalues.push_back(to_string(c.credits));
	initvalues.push_back(to_string(c.maximumStudent));
	stringstream ss(c.daySession1 + " " + c.daySession2);
	string tmp = "";
	while (getline(ss, tmp, ' ')) initvalues.push_back(tmp);
	initvalues[6] = to_string(c.getTimesetId(initvalues[6]) + 1);
	initvalues[8] = to_string(c.getTimesetId(initvalues[8]) + 1);

}
sll<string> CoursesList::modifyCourseProc(bool& isCancel, bool& isDeleted, sll<string> initvalues) {
	sll<InputRow> inputList;
	sll<Button> buttonList;
	sll<pair<int, int> > pos;
	sll<string> res;
	bool isOver = false;
	setupCourseInputList(inputList, buttonList, pos, initvalues, true);
	setOnClickSubmitButton(buttonList[0], inputList, res, isOver);
	setOnClickDeleteButton(buttonList[1], inputList, isOver, isDeleted);

	renderInputCourseProc(inputList, buttonList, pos, isOver);
	isCancel = !isOver;
	return res;
}
void CoursesList::modifyCourse(int id, bool& isDeleted) {
	bool isCancel = false;
	isDeleted = false;
	//system("cls");
	sll<string> initvalues;
	buildInitValues(initvalues, (*this)[id]);

	sll<string> res = modifyCourseProc(isCancel, isDeleted, initvalues);

	if (isCancel) return;
	if (isDeleted) {
		this->deleteAt(id);
		reNumberingCourses();
		return;
	}
	Course& c = (*this)[id];
	c.courseID = res[0]; c.nameOfCourse = res[1]; c.nameOfTeacher = res[2]; c.credits = stoi(res[3]); c.maximumStudent = stoi(res[4]);
	c.daySession1 = res[5] + " " + c.timeset[stoi(res[6]) - 1];
	c.daySession2 = res[7] + " " + c.timeset[stoi(res[8]) - 1];

	renderAccept();
	Sleep(200);
	return;
}
;
