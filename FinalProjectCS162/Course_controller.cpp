#include "Course_controller.h"


Course_controller::Course_controller() {}
Course_controller::Course_controller(string yearname, string semesterName) {
	this->yearName = yearName;
	this->semesterName = semesterName;
	courseRegsController = CoursesRegistrationsController(yearname, semesterName);
	loadCourses(yearname, semesterName);
}
;

void Course_controller::loadCourses(const string& yearName, const string& semesterName) {
	(this->yearName) = yearName;
	(this->semesterName) = semesterName;
	if (!(this->courses).readFile("Data/" + yearName + "/" + semesterName + "/Courses.csv"))
		cerr << "There was error in reading data\n";
}
string Course_controller::getFinScoreOfStudent(int courseIdx, string stuID) {
	return this->courses[courseIdx].getFinScoreOfStudent(this->yearName, this->semesterName, stuID);
}
void Course_controller::loadCourseStudent(int courseIdx) {
	this->courses[courseIdx].loadScoreCourseStudents(this->yearName, this->semesterName);
}

//--

int Course_controller::chooseOption(Table& table) {
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
void Course_controller::setupCourseOptionsTable(Table& table, string courseID, int offsetY) {
	table = Table(10, 5 + offsetY, 5);

	table.addTitleRow_back(40);
	table.getRow(0).addText(courseID);
	table.addRow_back("View students in course");
	table.addRow_back("Export student list to CSV");
	table.addRow_back("View the scoreboard in course");
	table.addRow_back("Modify/Delete course");
	table.setDefaultType();
	table.render();

	table.setCursorInside();
}
int Course_controller::inputCourseOptionTableProc(string courseID, int offsetY) {
	int type = 0;
	Table table;
	setupCourseOptionsTable(table, courseID, offsetY);
	table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
	return type;
}
void Course_controller::viewCourseOptions(string yearname, string semester, int id) {
	string courseID = this->courses[id].courseID;
	int type = inputCourseOptionTableProc(courseID, id);
	bool isDeleted = false;
	switch (type)
	{
	case 1: viewStu(yearname, semester, id); break;
	case 2: break;
	case 3: viewScoreStu(yearName, semester, id); break;
	case 4: this->courses.modifyCourse(id, isDeleted); system("cls"); break;
	default:
		break;
	}
	this->courses.saveCourses(yearname, semester);
	if (isDeleted) {
		string stuListPath = ("Data/" + this->yearName + "/" + this->semesterName + "/Studentlist/" + courseID + ".csv");
		remove(stuListPath.c_str());
		courseRegsController.delCourseReg(courseID);
		courseRegsController.loadEnrolledCourses();
		courseRegsController.delEnrolledCourseColumn(courseID);
	}
	return;
}
;


//--

void Course_controller::setupCourseStudentsTable(Table& table, int id) {
	system("cls");
	table = Table(0, 0, 30);

	table.addTitleRow_back(12, 16, 14, 20);
	table.getRow(0).addText((string)"No", (string)"ID", (string)"First Name", (string)"Last Name");
	if (courses[id].students.size() == 0) {
		table.addRow_back("Empty");
	}
	int row = 0;
	for (auto i : courses[id].students) {
		++row;
		table.addRow_back(to_string(row), i.ID, i.firstname, i.lastname);
	}

	table.setDefaultType();
	table.render();

	table.setCursorInside();
}

int Course_controller::getCourseStudentFromTableProc(int id) {
	int type = 0;
	Table table;
	setupCourseStudentsTable(table, id);
	table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
	return type;
}

void Course_controller::viewStu(string yearname, string semester, int id) {

	courses[id].loadCourseStudents(yearname, semester);
	int type = getCourseStudentFromTableProc(id);

	while (type != -1) {

		type = getCourseStudentFromTableProc(id);
	}
}

//--
void Course_controller::courseProc(string yearname, string semester) {

	int type = this->courses.viewCourses(yearname, semester);
	while (type != -1) {
		if (type == 1) {
			this->courses.createCourse();
			this->courses.saveCourses(yearName, semester);
			system("cls");
		}
		else {
			this->viewCourseOptions(yearname, semester, type - 2);
			system("cls");
		}
		type = this->courses.inputCoursesTableProc();
	}

}

bool Course_controller::containsCourse(const string& courseID) const {
	return (this->courses).containsCourse(courseID);
}
//--

void Course_controller::setupScoreCourseStudentsTable(Table& table, int id) {
	system("cls");
	table = Table(0, 0, 30);

	table.addTitleRow_back(12, 16, 14, 18, 18, 14, 18);
	table.getRow(0).addText((string)"No", (string)"ID", (string)"Name", (string)"Total Score", (string)"Final Score", (string)"Midterm", (string)"Other Score");
	if (courses[id].scoreStudents.size() == 0) {
		table.addRow_back("Empty");
	}
	int row = 0;
	for (auto i : courses[id].scoreStudents) {
		++row;
		table.addRow_back(to_string(row), i.ID, i.name, i.totScore, i.FinScore, i.midScore, i.otherScore);
	}

	table.setDefaultType();
	table.render();

	table.setCursorInside();
}
int Course_controller::getScoreCourseStudentFromTableProc(int id) {
	int type = 0;
	Table table;
	setupScoreCourseStudentsTable(table, id);
	table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
	return type;
}
void Course_controller::viewScoreStu(string yearname, string semester, int id) {

	courses[id].loadScoreCourseStudents(yearname, semester);
	int type = getScoreCourseStudentFromTableProc(id);

	while (type != -1) {

		type = getScoreCourseStudentFromTableProc(id);
	}
}
;

//*
void Course_controller::updateScore(const string& courseID, const int studentID) {
	if (!(this->containsCourse(courseID))) {
		cout << "There is no course with " << courseID << '\n';
		return;
	}
	double score;
	int id = -1, number = 0;
	StudentScore studentScore;
	SinglyLinkedList<StudentScore> scoresOfStudents = this->getScore(courseID);
	for (const StudentScore& studentScore : scoresOfStudents) {
		if (studentScore.studentID == studentID) {
			id = number;
			break;
		}
		++number;
	}
	if (id < 0) {
		cout << "There was no student with " << studentID << " in the course " << courseID << "\n";
		return;
	}
	studentScore = scoresOfStudents[id];
	do {
		system("cls");
		studentScore.printData(cout);
		cout << "Please enter one of following options\n"
			 << "1. Stop updating score\n"
		 	 << "2. Update total mark\n"
		 	 << "3. Update final mark\n"
		 	 << "4. Update midterm mark\n"
	 		 << "5. Update other mark\n"
			 << "Your option: ";
		cin >> number;
		if (number == 1) {
			scoresOfStudents[id] = studentScore;
			break;
		} else if (number < 1 || number > 5) {
			cout << "Option is invalid\n";
		} else {
			cout << "Please enter new score: ";
			cin >> score;
			switch (number) {
			case 2:
				studentScore.totalMark = score;
				break;
			case 3:
				studentScore.finalMark = score;
				break;
			case 4:
				studentScore.midtermMark = score;
				break;
			case 5:
				studentScore.otherMark = score;
				break;
			}
		}
		system("pause");
	} while (number != 1);
	printScoresToCSVfile(courseID, scoresOfStudents);
}
//--

void Course_controller::setupScoreStudentTable(Table& table, int stuID) {
	system("cls");
	table = Table(0, 0, 30);

	table.addTitleRow_back(16, 20, 16, 16, 16, 16);
	table.getRow(0).addText((string)"Course_ID", (string)"Student's name", (string)"Total Mark",
		(string)"Final Mark", (string)"Midterm mark", (string)"Other mark");

	for (auto course : courses) {
		for (const StudentScore& studentScore : (this->getScore(course.courseID))) {
			if (studentScore.studentID == stuID) {
				table.addRow_back(course.courseID, studentScore.name,
					doubleToStr(studentScore.totalMark, 2), doubleToStr(studentScore.finalMark, 2), doubleToStr(studentScore.midtermMark, 2),
					doubleToStr(studentScore.otherMark, 2));
				break;
			}
		}
	}
	if (table.getTotalRows() == 1) {
		table.addRow_back((string)"Empty");
	}

	table.setDefaultType2();
	table.render();

	table.setCursorInside();
}
int Course_controller::getScoreStudentFromTableProc(int stuID) {
	int type = 0;
	Table table;
	setupScoreStudentTable(table, stuID);
	table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
	return type;
}
;

SinglyLinkedList<StudentScore> Course_controller::getScore(const string& courseID) const {
	SinglyLinkedList<StudentScore> scoresOfStudents;
	ifstream finput("Data/" + (this->yearName) + "/" + (this->semesterName) + "/Mark/" + courseID + ".csv");
	if (finput) {
		StudentScore studentScore;
		finput.ignore(5000, '\n'); //Not read first line
		while (studentScore.readData(finput)) 
			scoresOfStudents.push_back(studentScore);
	}
	finput.close();
	return scoresOfStudents;
};

void Course_controller::printScoresToCSVfile(const string& courseID, const SinglyLinkedList<StudentScore>& scoresOfStudents) const {
	ofstream foutput("Data/" + (this->yearName) + "/" + (this->semesterName) + "/Mark/" + courseID + ".csv");
	foutput << "No,Student ID,Name,Total Mark,Final Mark,Midtern Mark,Orther Mark\n";
	for (const StudentScore& studentScore : scoresOfStudents)
		studentScore.printToCSVfile(foutput);
	foutput.close();
};


void Course_controller::viewScoresOfAStudent(const string studentID) {
	int type = getScoreStudentFromTableProc(stoi(studentID));
}
//--

void Course_controller::renderCaution(string s) {
	TextBox notice = TextBox(5, 20, 40, 3, false, 0, 12).setText(s);
	notice.render();
}
void Course_controller::renderAccept() {
	TextBox notice = TextBox(5, 20, 40, 3, false, 0, 10).setText("Operated successfully, loading ...");
	notice.render();
	Sleep(200);
	notice = TextBox(5, 20, 40, 3, false, 0, 10).setText("                                          ");
	notice.render();
}
void Course_controller::setupEnrollCourseTable(int initRow, Table& table, sll<bool>& enrolled, sll<int>& curNumsStu, CoursesRegistrationsController& courseRegController, CoursesList& validCourse, sll<int>& validRegPos) {
	table = Table(0, 12, 7);
	table.addTitleRow_back(5, 16, 12, 16, 16, 10, 15);
	table.getRow(0).addText((string)"No", (string)"CourseID", (string)"Credits", (string)"Start day", (string)"end day", (string)"Total", (string)"Status");

	for (int i = 0; i < validRegPos.size(); ++i) {
		Course target = validCourse[i];
		CourseRegistration c = courseRegController.coursesRegistrations[validRegPos[i]];
		string status = (enrolled[validRegPos[i]]) ? "Joined" : "Not joined";
		string totalStu = to_string(curNumsStu[validRegPos[i]]) + "/" + to_string(target.maximumStudent);
		table.addRow_back(to_string(i + 1), target.courseID, to_string(target.credits), c.getStartDate().convert2String(), c.getEndDate().convert2String(), totalStu, status);
	}
	if (validRegPos.size() == 0) {
		table.addRow_back("", "Empty");
	}
	table.setDefaultType2();
	table.render();

	table.setCursorOnRow(initRow);
}
int Course_controller::inputEnrollCoursesTableProc(int stuID, sll<int>& curNumsStu, sll<bool>& status, CoursesRegistrationsController& courseRegController, CoursesList& validCourses, sll<int>& validRegPos, int initRow) {
	int type = 0;
	Table table;
	setupEnrollCourseTable(initRow, table, status, curNumsStu, courseRegController, validCourses, validRegPos);
	table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
	return type;
}
void Course_controller::getValidCourses(CoursesRegistrationsController& courseRegController, CoursesList& validCourses, sll<int>& validRegPos) {
	int i = 0;
	for (auto c : courseRegController.coursesRegistrations) {
		++i;
		string id = c.getCourseID();
		int idx = this->courses.findIndex([&](Course target) { return target.courseID == id; });
		if (idx == -1) continue;
		validRegPos.push_back(i - 1);
		validCourses.push_back(this->courses[idx]);
	}

}
void Course_controller::enrollCourseProc(int stuId, string firstname, string lastname) {
	CoursesRegistrationsController courseRegController(this->yearName, this->semesterName);
	courseRegController.loadEnrolledCourses();
	CoursesList validCourses;
	sll<int> validRegPos;
	getValidCourses(courseRegController, validCourses, validRegPos);
	sll<int> curNumsStu;
	sll<bool> status;
	courseRegController.getInfoEnrollmentStudent(stuId, status, curNumsStu);
	int type = 1;
	do {
		type = inputEnrollCoursesTableProc(stuId, curNumsStu, status, courseRegController, validCourses, validRegPos, type);
		if (type != -1) {
			if (type > validCourses.size()) continue;
			int i = type - 1;
			int validIdx = validRegPos[i];
			bool& enrollStatus = status[validRegPos[i]];
			if (!courseRegController.coursesRegistrations[validIdx].checkRegistrationDates()) {
				renderCaution("Timeout !");
				continue;
			}
			if (enrollStatus) {
				enrollStatus = false;
				--curNumsStu[validIdx];
			}
			else {
				int cnt = 0;
				for (auto i : status) cnt += i;

				if (cnt >= 5) {
					renderCaution("Maximum: 5");
					continue;
				}
				if (validCourses[i].maximumStudent <= curNumsStu[validIdx]) {
					renderCaution("Course is full");
					continue;
				}
				if (this->checkSessionsConflicted(status, courseRegController, validCourses, validRegPos)) {
					renderCaution("Conflicted");
					continue;
				}
				enrollStatus = true;
				++curNumsStu[validIdx];
				renderAccept();
			}
		}
		courseRegController.updateStatusEnrolledCourses(stuId, status);
		courseRegController.saveEnrolledCourses();
	} while (type != -1);
	SaveStudentEnrollmentOfCourses(to_string(stuId), lastname, firstname, validCourses, validRegPos, status);

}
bool Course_controller::checkSessionsConflicted(sll<bool> status, CoursesRegistrationsController& CourseRegController, CoursesList& validCourses, sll<int>& validRegPos) {
	const int numberOfCourses = validCourses.size();
	SinglyLinkedList<pair<string, pair<int, int> > > sessions[2];
	for (int i = 0; i < validRegPos.size(); ++i) {
		CourseRegistration cReg = CourseRegController.coursesRegistrations[validRegPos[i]];
		Course c = this->courses[i];
		if (status[validRegPos[i]]) {
			sessions[0].push_back(c.getDaySession1());
			sessions[1].push_back(c.getDaySession2());
		}
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
void Course_controller::SaveStudentEnrollmentOfCourses(string stuId, string lastname, string firstname, CoursesList& validCourses, sll<int>& validRegPos, sll<bool>& status) {
	for (int i = 0; i < validRegPos.size(); ++i) {
		int idx = validRegPos[i];
		validCourses[i].loadCourseStudents(this->yearName, this->semesterName);
		if (status[idx]) validCourses[i].updateStudentOfThisCourse(stuId, lastname, firstname);
		else
			validCourses[i].delStudentOfThisCourse(stuId);
		validCourses[i].saveCourseStudents(this->yearName, this->semesterName);
	}
}
;

SinglyLinkedList<pair<int, SinglyLinkedList<string> > > Course_controller::getListOfEnrolledCourses() const {
	SinglyLinkedList<pair<int, SinglyLinkedList<string> > > result;
	ifstream finput("Data/" + (this->yearName) + "/" + (this->semesterName) + "/EnrolledCourses.csv");
	if (finput) {
		SinglyLinkedList<string> coursesID;
		string line, courseID;
		int studentID;
		finput.ignore(1000, '\n'); //ignore first line
		while (getline(finput, line)) {
			stringstream information(line + ',');
			information >> studentID;
			information.ignore(1000, ',');
			coursesID.clear();
			while (getline(information, courseID, ','))
				coursesID.push_back(courseID);
			result.push_back({ studentID, coursesID});
		}
	}
	finput.close();
	return result;
};

SinglyLinkedList<string> Course_controller::getListOfEnrolledCoursesOfStudent(const int studentID) const {
	for (const auto& data : (this->getListOfEnrolledCourses()))
		if (data.first == studentID)
			return data.second;
	return SinglyLinkedList<string>();
};

int Course_controller::countStudentsInCourse(const string& courseID) const {
	int result = 0;
	for (const auto& information : (this->getListOfEnrolledCourses()))
		for (const string& id : information.second)
			if (id == courseID) {
				++result;
				break;
			}
	return result;
};
//*
void Course_controller::displayRegistrationTable(const bool* status, const int* numberOfStudents,const SinglyLinkedList<CourseRegistration>& coursesRegistrations) const {
	int number_length = strlen("no"),
		credits_length = strlen("credits"),
		nameOfCourse_length = strlen("Name of course"),
		courseID_length = strlen("Course ID"),
		totalLength, i = 0;
	const int numberOfStudents_length = 25,
		      status_length = 10,
			  startDate_length = 20,
			  endDate_length = 20,
			  numberOfCourses = (this->courses).size();
	// Find the require length for each information
	for (const Course& course : (this->courses)) {
		number_length = max(number_length, getNumberOfDigits(course.number));
		credits_length = max(credits_length, getNumberOfDigits(course.credits));
		courseID_length = max(courseID_length, (int)course.courseID.size());
		nameOfCourse_length = max(nameOfCourse_length, (int)course.nameOfCourse.size());
	}
	number_length += 2;
	credits_length += 2;
	courseID_length += 2;
	nameOfCourse_length += 2;
	totalLength = 9 + startDate_length + endDate_length + number_length + credits_length + nameOfCourse_length + courseID_length + numberOfStudents_length + status_length;
	cout << string(totalLength, '-') << '\n';
	cout << '|'
		<< setw(number_length) << "No" << '|'
		<< setw(courseID_length) << "Course ID" << '|'
		<< setw(nameOfCourse_length) << "Name of course" << '|'
		<< setw(credits_length) << "Credits" << '|'
		<< setw(startDate_length) << "Registration start" << '|'
		<< setw(endDate_length) << "Registration end" << '|'
		<< setw(numberOfStudents_length) << "Number of students" << '|'
		<< setw(status_length) << "Status" << '|'
		<< '\n';
	cout << string(totalLength, '-') << '\n';
	for (const Course& course : (this->courses)) {
		stringstream studentsNumber;
		studentsNumber << numberOfStudents[i] << '/' << course.maximumStudent;
		cout << '|'
			 << setw(number_length) << course.number << '|'
			 << setw(courseID_length) << course.courseID << '|'
			 << setw(nameOfCourse_length) << course.nameOfCourse << '|'
			 << setw(credits_length) << course.credits << '|'
			 << setw(startDate_length) << coursesRegistrations[i].getStartDate().convert2String() << '|'
			 << setw(endDate_length) << coursesRegistrations[i].getEndDate().convert2String() << '|'
			 << setw(numberOfStudents_length) << studentsNumber.str() << '|'
			 << setw(status_length) << (status[i] ? "Join" : "") << '|'
	 		 << '\n';
		++i;
	}
	cout << string(totalLength, '-') << '\n';
};

void Course_controller::changeEnrolledCourses(const int studentID) {
	const int numberOfCourses = (this->courses).size();
	bool* status = new bool[numberOfCourses];
	/*
	status[i] is true if student has joined course and false otherwise
	*/
	int* numberOfStudents = new int[numberOfCourses];
	SinglyLinkedList<CourseRegistration> coursesRegistrations;
	SinglyLinkedList<string> enrolledCoursesID;
	int option = 0, id;
	string courseID;
	//Load information
	for (int i = 0; i < numberOfCourses; ++i) {
		status[i] = false;
		numberOfStudents[i] = this->countStudentsInCourse((this->courses)[i].courseID);
	}
	for (const Course& course : (this->courses)) {
		CourseRegistration courseRegistration;
		courseRegistration.createRegistration(this->yearName, this->semesterName, course.courseID);
		courseRegistration.loadDates();
		coursesRegistrations.push_back(courseRegistration);
	}
	for (const string& courseID : (this->getListOfEnrolledCoursesOfStudent(studentID)))
		for (int i = 0; i < numberOfCourses; ++i)
			if (courseID == (this->courses)[i].courseID) {
				status[i] = true;
				break;
			}
	//Change information
	while (option != 1) {
		system("cls");
		cout << "Student ID:" << studentID << '\n';
		this->displayRegistrationTable(status, numberOfStudents, coursesRegistrations);
		cout << "1. Escape\n"
			 << "2. Join a course\n"
			 << "3. Remove a course from enrolled course list\n"
			 << "Please enter your option: ";
		if (!readInteger(option) || option < 1 || option > 3) {
			cout << "Option is invalid\n";
			system("pause");
			continue;
		}
		if (option == 1) {
			/*
			if ((this->courses).checkSessionsConflicted(status)) {
				cout << "Warning: There might be two courses whose sessions are conflicted\n";
				system("pause");
			}
			*/
			break;
		}
		cout << "Please enter course id: ";
		getline(cin, courseID);
		if (!(this->containsCourse(courseID))) {
			cout << "There were currently no course with id '" << courseID << "'\n";
			system("pause");
			continue;
		}
		for (int i = 0; i < numberOfCourses; ++i)
			if ((this->courses)[i].courseID == courseID) {
				id = i;
				break;
			}
		if (!coursesRegistrations[id].checkRegistrationDates()) {
			cout << "The course registration is not currently active\n";
			system("pause");
			continue;
		}
		if (option == 2) {
			if (status[id]) {
				cout << "The course has already been in your enrolled course list\n";
			} else if (numberOfStudents[id] >= (this->courses)[id].maximumStudent) {
				cout << "The allowed number of students in this course is maximum\n";
			} else {
				status[id] = true;
				if ((this->courses).checkSessionsConflicted(status)) {
					cout << "Register unsucessfully because the sessions of the course are conflicted with existing enrolled course sessions\n";
					status[id] = false;
				} else {
					cout << "Register sucessfully\n";
					++numberOfStudents[id];
				}
			}
			system("pause");
		} else { // if (option == 3)
			if (status[id]) {
				cout << "Remove sucessfully\n";
				--numberOfStudents[id];
				status[id] = false;
			} else {
				cout << "Student has not joined the course yet\n";
			}
			system("pause");
		}
	}
	for (int i = 0; i < numberOfCourses; ++i)
		if (status[i])
			enrolledCoursesID.push_back((this->courses)[i].courseID);
	this->updateEnrolledCoursesInCSVfile(studentID, enrolledCoursesID);
	delete[] status;
	delete[] numberOfStudents;
};	

void Course_controller::updateEnrolledCoursesInCSVfile(const int studentID, const SinglyLinkedList<string>& enrolledCoursesID) {
	SinglyLinkedList<pair<int, SinglyLinkedList<string> > > coursesID = this->getListOfEnrolledCourses();
	for (auto& data : coursesID)
		if (data.first == studentID) {
			data.second = enrolledCoursesID;
			break;
		}
	this->printEnrolledCoursesInCSVfile(coursesID);
};

void Course_controller::printEnrolledCoursesInCSVfile(const SinglyLinkedList<pair<int, SinglyLinkedList<string> > >& information) {
	ofstream foutput("Data/" + (this->yearName) + "/" + (this->semesterName) + "/EnrolledCourses.csv");
	if (foutput) {
		foutput << "Student ID, Course1, Course2, Course3, Course4, Course5\n";
		for (const auto& data : information) {
			foutput << data.first;
			for (const auto& courseID : data.second)
				foutput << ',' << courseID;
			foutput << '\n';
		}
	}
	foutput.close();
};

SinglyLinkedList<int> Course_controller::getCourseListOfStudentsID(const string& courseID) const {
	SinglyLinkedList<int> result;
	for (const auto &information : (this->getListOfEnrolledCourses()))
		for (const string& id : information.second)
			if (id == courseID) {
				result.push_back(information.first);
				break;
			}
	return result;
};

bool Course_controller::exportListOfStudentsID(const string& courseID) const {
	//Print list of student ID in a course to a CSV file (save file at input path)
	if (!(this->containsCourse(courseID))) {
		cout << "There is no course with " << courseID << '\n';
		return false;
	}
	string path;
	cout << "Please enter the path of the csv file you want to save at: ";
	cin >> path;
	if (_mkdir(path.c_str())) {
		ofstream foutput(path + "/" + courseID + ".csv");
		foutput << "StudentID\n";
		for (const int& studentID : (this->getCourseListOfStudentsID(courseID)))
			foutput << studentID << '\n';
		foutput.close();
		cout << "File was successfully saved\n";
		return true;
	}
	cout << "File was not successfully saved\n";
	return false;
};

void Course_controller::updateCoursesInformation() {
	(this->courses).updateInformation();
	(this->courses).writeFile("Data/" + yearName + "/" + semesterName + "/Courses.csv");
};