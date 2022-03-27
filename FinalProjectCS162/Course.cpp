#include <iostream>

using namespace std;

#include "Course.h"
#include "helper.h"

bool Course::readData(ifstream& finput) {
	if (finput >> (this->number)) {
		finput.ignore(1, ',');
		getline(finput, this->courseID, ',');
		getline(finput, this->nameOfCourse, ',');
		getline(finput, this->nameOfTeacher, ',');
		finput >> (this->credits);
		finput.ignore(1, ',');
		finput >> (this->maximumStudent);
		finput.ignore(1, ',');
		getline(finput, this->daySession1, ',');
		getline(finput, this->daySession2, '\n');
		adjustString(this->courseID);
		adjustString(this->nameOfCourse);
		adjustString(this->nameOfTeacher);
		adjustString(this->daySession1);
		adjustString(this->daySession2);
		return true;
	}
	return false;
};

void Course::writeDate(ofstream& foutput) const {
	foutput << (this->number) << ',' 
		    << (this->courseID) << ',' 
			<< (this->nameOfCourse) << ',' 
		    << (this->nameOfTeacher) << ','
		    << (this->credits) << ','
		    << (this->maximumStudent) << ','
		    << (this->daySession1) << ','
		    << (this->daySession2) << '\n';
};

bool Course::updateCourse() {
	/*
		Function should be repreated (in a loop)
		Function return false if it should be stoped being repeated and true otherwise
	*/
	int option;
	cout << "1. Escape\n"
		 << "2. Course ID\n"
		 << "3. Name of course\n"
		 << "4. Name of teacher\n"
		 << "5. Credits\n"
		 << "6. Maximum number of students in course\n"
		 << "7. Day-session 1\n"
		 << "8. Day-session 2\n"
		 << "Please enter your option: ";
	if (!readInteger(option) || option < 1 || option > 8) {
		cout << "Invalid option\nPlease enter again\n";
		system("pause");
		return true;
	}
	if (option == 1)
		return false;
	switch (option) {
	case 2:
		cout << "Please enter new course id: ";
		cin >> (this->courseID);
		break;
	case 3:
		cout << "Please enter new name of course: ";
		getline(cin, this->nameOfCourse);
		break;
	case 4:
		cout << "Please enter name of teacher: ";
		getline(cin, this->nameOfTeacher);
		break;
	case 5:
		cout << "Please enter new number of credits: ";
		if (!readInteger(this->credits))
			cout << "Input number is invalid\n";
		else if ((this->credits) <= 0) {
			cout << "Warning: the number of credits is not positive\n";
			system("pause");
		}
		break;
	case 6:
		cout << "Please enter the maximum number of students in a course:";
		if (!readInteger(this->maximumStudent))
			cout << "Input number is invalid\n";
		else if ((this->maximumStudent) <= 0) {
			cout << "Warning: the number is not positive\n";
			system("pause");
		}
		break;
	case 7:
		cout << "Please enter day-session 1: ";
		getline(cin, this->daySession1);
		break;
	case 8:
		cout << "Please enter day-session 2: ";
		getline(cin, this->daySession2);
		break;
	}
	return true;
};