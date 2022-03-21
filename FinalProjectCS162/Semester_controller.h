#pragma once
#include <iostream>
#include <direct.h>
#include <string.h>
#include "semester.h"
#include "SinglyLinkedList.h"
#include "Date.h"
using namespace std;

class Semester_controller : public semester
{
public: 
	void create_semester() {
		cout << "Choose the year to add the semester: " << endl;
		cin >> yearName;
		ifstream fin;
		fin.open('/' + yearName + "/semesters.txt");
		SinglyLinkedList<string> lst;
		while (fin.eof()) {
			string temp;
			fin >> temp;
			lst.push_back(temp);
		}
		cout << "Current created semesters in year: " << yearName << ": ";
		for (auto i : lst) {
			cout << i << " ";
		}
		cout << endl << "Input the semester you want to add: " << endl;
		cin >> semester_name;
		string path = '/' + yearName + '/' + semesterName;
		int a = mkdir(path.c_str());
		return;
	}
	void getSemester(int num) {
		semesterName = 's'+num;
	}
	Date createCourseReg() {
		Date d;
		d.defaultInputDate();
		return d;
	}
	void viewCourse() {
		ifstream fin;
		fin.open('/' + yearName + '/' + semesterName + "Courses.csv");
		string temp;
		while (getline(fin, temp, ',')) {
			getline(fin, temp, ',');
			cout << temp << " ";
		}
	}
};
