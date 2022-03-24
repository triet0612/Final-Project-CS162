#pragma once
#include <iostream>
#include <direct.h>
#include <string.h>
#include "semester.h"
#include "SinglyLinkedList.h"
#include "Date.h"
using namespace std;

class Semester_controller
{
private:
	SinglyLinkedList<semester> semesterlist;
	bool checkSemester(string name) {
		for (auto i : semesterlist) {
			if (i.semester_name == name) {
				return true;
			}
		}
		return false;
	}
	void saveSemester(string yearname) {
		ofstream fout;
		fout.open('/' + yearname + "/semesters.txt");
		for (auto i : semesterlist) {
			fout << i.semester_name << " " << i.startdate << " " << i.endate << endl;
		}
		fout.close();
		return;
	}
public: 
	semester create_semester(string yearname) {
		getSemesterList(yearname);
		viewSemester();
		cout << "Input the semester you want to create" << endl;
		string temp = "";
		while (checkSemester(temp)) {
			cout << "Input: " << endl;
			cin >> temp;
		}
		int day, month, year;
		cin >> day >> month >> year;
		Date d1(day, month, year);
		cin >> day >> month >> year;
		Date d2(day, month, year);
		semester s(temp, d1, d2);
		semesterlist.push_back(s);
		return s;
	}
	
	void getSemesterList(string yearname) {
		ifstream fin;
		fin.open('/' + yearname + "/semesters.txt");
		string temp1;
		string temp2;
		string temp3;
		while (!fin.eof()) {
			fin >> temp1;
			fin >> temp2;
			fin >> temp3;
			Date d1;
			Date d2;
			d1.operator=(temp2);
			d2.operator=(temp3);
			semester t(temp1, d1, d2);
			semesterlist.push_back(t);
		}
		fin.close();
		saveSemester(yearname);
		return;
	}
	
	void viewSemester() {
		cout << "List of semesters:" << endl;
		for (auto i : semesterlist) {
			cout << i.semester_name << " " << i.startdate << " " << i.endate << endl;
		}
		return;
	}
	
	semester& getSemester(string yearname, int num) {
		getSemesterList(yearname);
		for (auto i : semesterlist) {
			if (i.semester_name == "s" + num) {
				return i;
			}
		}
	}
	
	void createCourseReg(semester& s, string yearname) {
		ofstream fout;
		fout.open('/' + yearname + '/' + s.semester_name + "/course_reg.txt");
		string temp;
		cout << "Start date: " << endl;
		cin >> temp;
		fout << temp << " ";
		cout << "End date: " << endl;
		cin >> temp;
		fout << temp << endl;
		fout.close();
		return;
	}
	
	void viewCourse(semester& s) {

	}
};
