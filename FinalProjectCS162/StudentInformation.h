#pragma once

#include <string>
#include <cstring>

#include "Date.h"

class StudentInformation {
public:
	int id;
	char gender;
	Date dateOfBirth;
	string lastName, firstName, socialID;

	StudentInformation();
	StudentInformation(const int studentID, const string& className, const string& yearName);

	bool readData(const int studentID, const string& className, const string& yearName);

};