#pragma once
#include "Schoolyear.h"

class Schoolyear_controller : public Schoolyear {
public:
	void createSchoolYear() {
		ofstream fout;
		fout.open("SchoolYear.txt", ios_base::app);
		cout << "Current created years: " << endl;
		viewSchoolYear();
		cout << endl << "Input the year you want to create" << endl;
		cin >> this_year;
		fout << this_year;
		int a = mkdir(('/'+ this_year).c_str());
		fout.close();
		return;
	}
	void viewSchoolYear() {
		ifstream fin;
		fin.open("SchoolYear.txt");
		string temp;
		while (!fin.eof()) {
			fin >> temp;
			cout << temp << " ";
		}
		cout << endl;
		fin.close();
		return;
	}
	void addSemesterToSchoolYear() {
		yearName = this_year;
		create_semester();
	}
};