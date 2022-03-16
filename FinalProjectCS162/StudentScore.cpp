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