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
public:

	SinglyLinkedList<semester> semesterlist;

	semester cur_semester;
	
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

	void create_semester(string yearname, string semestername) {
		cout << "Input start date: " << endl;
		int day, month, year;
		cin >> day >> month >> year;
		Date d1(day, month, year);
		cout << "Input end date: " << endl;
		cin >> day >> month >> year;
		Date d2(day, month, year);
		semester s(semestername, d1, d2);
		semesterlist.push_back(s);
		cur_semester = s;
		int checker = _mkdir(('/' + yearname + '/' + semestername).c_str());
		checker = _mkdir(('/' + yearname + '/' + semestername + "Mark").c_str());
		checker = _mkdir(('/' + yearname + '/' + semestername + "Studentlist").c_str());
		return;
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
			d1 = temp2;
			d2 = temp3;
			semester t(temp1, d1, d2);
			semesterlist.push_back(t);
		}
		fin.close();
		saveSemester(yearname);
		return;
	}
	
	void viewSemester() {
		if (semesterlist.size() == 0) {
			cout << "No semester created" << endl;
			return;
		}
		cout << "List of semesters:" << endl;
		for (auto i : semesterlist) {
			cout << i.semester_name << " " << i.startdate << " " << i.endate << endl;
		}
		return;
	}
	
	semester& getSemester(string yearname, int num) {
		getSemesterList(yearname);
		semester ans;
		for (auto i : semesterlist) {
			if (i.semester_name == "s" + num) {
				ans = i;
				break;
			}
		}
		return ans;
	}
	
	void createCourseReg(semester& s, string yearname) {
		s.course_reg.changeDates();
		return;
	}
	
	void viewCourse(semester& s) {
		s.course.viewListOfCourses();
	}
};
