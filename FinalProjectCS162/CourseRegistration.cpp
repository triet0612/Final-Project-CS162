#include "CourseRegistration.h"

void CourseRegistration::createRegistration(const string &yearName, const string &semesterName, const string &courseID) {
	(this->yearName) = yearName;
	(this->semesterName) = semesterName;
	(this->courseID) = courseID;
};

void CourseRegistration::createRegistration(const string &yearName, const string &semesterName) {
	(this->yearName) = yearName;
	(this->semesterName) = semesterName;
	//courseID should be assigned later
};

Date CourseRegistration::getStartDate() const {
	return this->startDate;
};

Date CourseRegistration::getEndDate() const {
	return this->endDate;
}
string CourseRegistration::getCourseID() const
{
	return this->courseID;
}
;

bool CourseRegistration::loadDates() {
	/*
		return true if dates are loaded successfully and false otherwise
	*/
	ifstream finput("Data/" + (this->yearName) + "/" + semesterName + "/coursesRegistrationsDates.txt");
	if (finput) {
		string id;
		int day, month, year;
		Date start, end;
		while (finput >> id) {
			finput >> day >> month >> year;
			start.setDate(day, month, year);
			finput >> day >> month >> year;
			end.setDate(day, month, year);
			if (id == (this->courseID)) {
				finput.close();
				this->startDate = start;
				this->endDate = end;
				return true;
			}
		}
	}
	finput.close();
	return false;
};

bool CourseRegistration::loadData(ifstream& finput) {
	string id;
	int day, month, year;
	if (finput >> id) {
		(this->courseID) = id;
		finput >> day >> month >> year;
		(this->startDate).setDate(day, month, year);
		finput >> day >> month >> year;
		(this->endDate).setDate(day, month, year);
		return true;
	}
	return false;
};

bool CourseRegistration::checkRegistrationDates() const {
	/*
		return true if student can enroll in course and false otherwise
	*/
	Date today = Date::getCurrentDate();
	return (this->startDate) <= today && today <= (this->endDate);
}
//--

int CourseRegistration::chooseOption(Table& table) {
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
void CourseRegistration::setupCourseRegInfoTable(Table& table, int id, const string& yearname) {
	system("cls");
	table = Table(0, 0, 3);

	table.addTitleRow_back(50);
	table.getRow(0).addText((string)" Course Registration Semester" + to_string(id + 1) + " Of " + yearname);

	table.addRow_back("Start: " + this->startDate.convert2String());
	table.addRow_back("End: " + this->endDate.convert2String());

	table.setDefaultType();
	table.render();

}
void CourseRegistration::courseRegInfoTableProc(int id, const string& yearname) {
	Table table;
	setupCourseRegInfoTable(table, id, yearname);
}
void CourseRegistration::viewCourseRegInfoTable(int id, const string& yearname) {
	system("cls");
	courseRegInfoTableProc(id, yearname);
	return;
}

//--

void CourseRegistration::setupSemesterOptionsTable(Table& table) {
	table = Table(0, 7, 5);

	table.addTitleRow_back(40);
	table.getRow(0).addText((string)" OPTIONS");
	table.addRow_back("Change date");

	table.setDefaultType();
	table.render();

	table.setCursorInside();
}
int CourseRegistration::inputSemesterOptionTableProc() {
	int type = 0;
	Table table;
	setupSemesterOptionsTable(table);
	table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
	return type;
}
void CourseRegistration::viewCourseRegOptions(int id, const string& yearname) {
	viewCourseRegInfoTable(id, yearname);
	int type = inputSemesterOptionTableProc();
	while (type != -1) {
		if (type == 1) {
			//createCourseReg(semesterlist[id], yearname);

		}
		else {
			//semesterlist[id].course.viewListOfCourses(yearname, "s" + to_string(id + 1));
		}
		viewCourseRegInfoTable(id, yearname);
		type = inputSemesterOptionTableProc();
	}
	return;
}
;

bool CourseRegistration::writeDataToFile() {
	ifstream finput("Data/" + (this->yearName) + "/" + semesterName + "/coursesRegistrationsDates.txt");
	if (finput) {
		bool flag = false;
		string id, dates;
		SinglyLinkedList<string> lines;
		while (getline(finput, id)) {
			lines.push_back(id);
			getline(finput, dates);
			if (id == (this->courseID)) {
				stringstream line;
				line << (this->startDate).getDay() << ' ' << (this->startDate).getMonth() << ' ' << (this->startDate).getYear() << ' '
					 << (this->endDate).getDay() << ' ' << (this->endDate).getMonth() << ' ' << (this->endDate).getYear() << '\n';
				flag = true;
				getline(line, dates);
			}
			lines.push_back(dates);
		}
		finput.close();
		ofstream foutput("Data/" + (this->yearName) + "/" + semesterName + "/coursesRegistrationsDates.txt");
		for (const string& line : lines)
			foutput << line << '\n';
		foutput.close();
		return flag;
	}
	finput.close();
	return false;
}

CourseRegistration::CourseRegistration() {
	yearName = semesterName = courseID = "";
	startDate = Date::getCurrentDate();
	endDate = Date::getCurrentDate();
}
CourseRegistration::CourseRegistration(const string& yearName, const string& semesterName, const string& courseID) {
	this->yearName = yearName;
	this->semesterName = semesterName;
	this->courseID = courseID;
	startDate = Date::getCurrentDate();
	endDate = Date::getCurrentDate();
}
CourseRegistration::CourseRegistration(const string& yearName, const string& semesterName, const string& courseID, const Date& startDate, const Date& endDate) {
	this->yearName = yearName;
	this->semesterName = semesterName;
	this->courseID = courseID;
	this->startDate = startDate;
	this->endDate = endDate;
}
;

void CourseRegistration::ModifyRegCourseDates() {

	//this->changeDatesReg();


	//int option = 0, day, month, year;
	//while (option != 1) {
	//	system("cls");
	//	cout << "Start date: " << (this->startDate) << '\n'
	//		 << "End date: " << (this->endDate) << '\n'
	//		 << "Change course registration session's date\n"
	//		 << "1. Stop editing\n"
	//		 << "2. Change start date\n"
	//		 << "3. Change end date\n"
	//		 << "Please enter the option you want to choose: ";
	//	readInteger(option);
	//	if (option == 1)
	//		break;
	//	if (option > 3) {
	//		cout << "Invalid option\nPlease enter again\n";
	//		system("pause");
	//		continue;
	//	}
	//	while (true) {
	//		cout << "Please enter date\n";
	//		cout << "Please enter day: ";
	//		if (!readInteger(day)) {
	//			cout << "Invalid input\nPlease enter again\n";
	//			continue;
	//		};
	//		cout << "Please enter month: ";
	//		if (!readInteger(month)) {
	//			cout << "Invalid input\nPlease enter again\n";
	//			continue;
	//		};
	//		cout << "Please enter year: ";
	//		if (!readInteger(year)) {
	//			cout << "Invalid input\nPlease enter again\n";
	//			continue;
	//		};
	//		if (!checkValidDate(day, month, year)) {
	//			cout << "Enter date is invalid\n";
	//			continue;
	//		}
	//		if (option == 2)
	//			this->startDate = Date(day, month, year);
	//		else
	//			this->endDate = Date(day, month, year);
	//		break;
	//	}
	//	if ((this->startDate) > (this->endDate)) {
	//		cout << "Warning: Start date should not be after end date\n";
	//		system("pause");
	//	}
	//}
	//this->writeDatesToFile();
};