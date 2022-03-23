#pragma once
#include "Schoolyear.h"

class Schoolyear_controller : public Schoolyear {
private:
	bool CheckYear(string yearname) {
		for (auto i : yearList) {
			if (i == yearname) {
				return true;
			}
		}
		return false;
	}
	
	void saveYearList() {
		ofstream fout;
		fout.open("SchoolYear.txt");
		for (auto i : yearList) {
			fout << i << endl;
		}
		fout.close();
		return;
	}
public:
	void createSchoolYear() {
		getYearList();
		viewSchoolYear();

		cout << "Select the year to create: " << endl;
		cout << "Example: 2020-2021" << endl;
		
		while (CheckYear(this_year)) {
			cout << "Input:" << endl;
			cin >> this_year;
		}
		yearList.push_back(this_year);
		
		int check = mkdir(('/' + this_year).c_str());
		saveYearList();
		cout << "Year create completed!" << endl;
	}
	
	void viewSchoolYear() {
		cout << "List of years: " << endl;
		for (auto i : yearList) {
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
			yearList.push_back(temp);
		}
		fin.close();
		return;
	}
	
	void loadSchoolYear() {
		cout << "Choose the year you want to use" << endl;
		getYearList();
		viewSchoolYear();
		string name = "";
		while (CheckYear(name)) {
			cout << "Input: " << endl;
			cin >> name;
		}
		this_year = name;
		ifstream fin;
		fin.open('/' + this_year + "/semesters.txt");
		while (!fin.eof()) {
			fin >> 
		}
	}
};