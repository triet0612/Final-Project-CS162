#include "StudentScore.h"
#include "helper.h"

bool StudentScore::readData(ifstream& finput) {
	if (finput >> (this->number)) {
		finput.ignore(1, ',');
		finput >> (this->studentID);
		finput.ignore(1, ',');
		getline(finput, this->name, ',');
		finput >> (this->totalMark);
		finput.ignore(1, ',');
		finput >> (this->finalMark);
		finput.ignore(1, ',');
		finput >> (this->midtermMark);
		finput.ignore(1, ',');
		finput >> (this->otherMark);
		adjustString(this->name);
		return true;
	}
	return false;
};

void StudentScore::printData(ostream& outputStream) const {
	outputStream << "Student ID: " << (this->studentID) << '\n'
				 << "Student name: " << (this->name) << '\n'
			   	 << "Total mark: " << (this->totalMark) << '\n'
			  	 << "Final mark: " << (this->finalMark) << '\n'
			 	 << "Midterm mark: " << (this->midtermMark) << '\n'
				 << "Other mark: " << (this->otherMark) << '\n';
};

void StudentScore::printToCSVfile(ofstream& foutput) const {
	foutput << (this->number) << ',' << (this->studentID) << ',' << (this->name) << ',' << (this->totalMark) << ',' << (this->finalMark) << ',' << (this->midtermMark) << ',' << (this->otherMark) << '\n';
};