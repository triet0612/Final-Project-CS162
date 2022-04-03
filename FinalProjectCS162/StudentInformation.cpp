#include <fstream>

#include "StudentInformation.h"

StudentInformation::StudentInformation() {};

StudentInformation::StudentInformation(const int studentID, const string& className, const string& yearName) {
	this->readData(studentID, className, yearName);
};

bool StudentInformation::readData(const int studentID, const string& className, const string& yearName) {
	// Find information of a student with given id in a class 
	bool result = false;
	ifstream finput("Data/" + yearName + "/" + className + ".csv");
	if (finput) {
		string number;
		int day, month, year;
		finput.ignore(1000, '\n'); //ignore first line
		while (getline(finput, number, ',')) {
			finput >> (this->id);
			finput.ignore(1000, ',');
			getline(finput, this->lastName, ',');
			getline(finput, this->firstName, ',');
			finput >> (this->gender);
			finput.ignore(1000, ',');
			finput >> day;
			finput.ignore(1000, '/');
			finput >> month;
			finput.ignore(1000, '/');
			finput >> year;
			finput.ignore(1000, ',');
			getline(finput, this->socialID, '\n');
			if ((this->id) == studentID) {
				(this->dateOfBirth).setDate(day, month, year);
				result = true;
				break;
			}
		}
	}
	finput.close();
	return result;
};