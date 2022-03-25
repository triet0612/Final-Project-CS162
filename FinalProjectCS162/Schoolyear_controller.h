#pragma once
#include "Schoolyear.h"

class Schoolyear_controller {
private:
	bool CheckYear(string yearname) {
		for (auto i : sc.yearList) {
			if (i == yearname) {
				return true;
			}
		}
		return false;
	}
	
public:
	Schoolyear sc;

	void saveYearList() {
		ofstream fout;
		fout.open("SchoolYear.txt");
		for (auto i : sc.yearList) {
			fout << i << endl;
		}
		fout.close();
		return;
	}
	
	void createSchoolYear() {
		getYearList();
		viewSchoolYear();

		cout << "Select the year to create: " << endl;
		cout << "Example: 2020-2021" << endl;
		
		while (CheckYear(sc.this_year)) {
			cout << "Input:" << endl;
			cin >> sc.this_year;
		}
		sc.yearList.push_back(sc.this_year);
		
		int check = mkdir(('/' + sc.this_year).c_str());
		saveYearList();
		cout << "Year create completed!" << endl;
	}
	
	void viewSchoolYear() {
		cout << "List of years: " << endl;
		for (auto i : sc.yearList) {
			cout << i << endl;
		}
		return;
	}
	
	void getYearList() {
		ifstream fin;
		fin.open("SchoolYear.txt");
		string temp;
		while (!fin.eof()) {
			fin >> temp;
			sc.yearList.push_back(temp);
		}
		fin.close();
		return;
	}
	
	Schoolyear getSchoolYear(string name) {
		getYearList();
		sc.this_year = name;
		ifstream fin;
		sc.semester_control.getSemesterList(sc.this_year);
		return sc;
	}

	void addSemesterToSchoolYear(string yearname) {
		sc.semester_control.getSemesterList(yearname);
		viewSemestersInYear();
		string semestername;
		cout << "Input semester: " << endl;
		cin >> semestername;
		while (!sc.semester_control.checkSemester(semestername)) {
			cout << "Semester already there, input again: " << endl;
			cin >> semestername;
		}
		sc.semester_control.create_semester(yearname, semestername);
		return;
	}
	
	void viewSemestersInYear() {
		sc.semester_control.viewSemester();
	}
};