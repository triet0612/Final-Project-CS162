#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

#include "SinglyLinkedList.h"
#include "CourseRegistration.h"
#include "helper.h"

void CourseRegistration::createRegistration(const string& yearName, const string& semesterName, const string& courseID) {
	(this->yearName) = yearName;
	(this->semesterName) = semesterName;
	(this->courseID) = courseID;
};

Date CourseRegistration::getStartDate() const {
	return this->startDate;
};

Date CourseRegistration::getEndDate() const {
	return this->endDate;
};

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

bool CourseRegistration::checkRegistrationDates() const {
	/*
		return true if student can enroll in course and false otherwise
	*/
	Date today = Date::getCurrentDate();
	return (this->startDate) <= today && today <= (this->endDate);
};

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
};

void CourseRegistration::changeDates() {
	int option = 0, day, month, year;
	while (option != 1) {
		system("cls");
		cout << "Start date: " << (this->startDate) << '\n'
			 << "End date: " << (this->endDate) << '\n'
			 << "Change course registration session's date\n"
			 << "1. Stop editing\n"
			 << "2. Change start date\n"
			 << "3. Change end date\n"
			 << "Please enter the option you want to choose: ";
		readInteger(option);
		if (option == 1)
			break;
		if (option > 3) {
			cout << "Invalid option\nPlease enter again\n";
			system("pause");
			continue;
		}
		while (true) {
			cout << "Please enter date\n";
			cout << "Please enter day: ";
			if (!readInteger(day)) {
				cout << "Invalid input\nPlease enter again\n";
				continue;
			};
			cout << "Please enter month: ";
			if (!readInteger(month)) {
				cout << "Invalid input\nPlease enter again\n";
				continue;
			};
			cout << "Please enter year: ";
			if (!readInteger(year)) {
				cout << "Invalid input\nPlease enter again\n";
				continue;
			};
			if (!checkValidDate(day, month, year)) {
				cout << "Enter date is invalid\n";
				continue;
			}
			if (option == 2)
				this->startDate = Date(day, month, year);
			else
				this->endDate = Date(day, month, year);
			break;
		}
		if ((this->startDate) > (this->endDate)) {
			cout << "Warning: Start date should not be after end date\n";
			system("pause");
		}
	}
	this->writeDataToFile();
};

string CourseRegistration::getCourseID() const {
	return this->courseID;
};