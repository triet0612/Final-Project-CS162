#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Class.h"
#include "SinglyLinkedList.h"
#include "Course_controller.h"
class Class_controller
{
public:
	SinglyLinkedList<Class> Classes;
	void createClass(string year) {
		ofstream fout;
		fout.open("Data/" + year + "/class.txt");

		string class_name;
		cout << "Please input the classes you want to create one per each line" << endl;
		cout << "Enter 'stop' after finishing input" << endl;
		cin >> class_name;
		while (class_name != "stop") {
			fout << class_name << endl;
			cin >> class_name;
		}

		fout.close();
		cout << "Thank you for input" << endl;
		return;
	}
	//load student data of classes
	void Load_Classes(string yearname) {
		SinglyLinkedList<string> Classes_name = Get_Classes(yearname);
		for (auto i : Classes_name) {
			Class c_temp;
			c_temp.addStuByCSV(yearname, i);
			Classes.push_back(c_temp);
		}
		return;
	}
	//load class name list from /yearname/class.txt
	SinglyLinkedList<string> Get_Classes(string yearname) {
		SinglyLinkedList<string> Classes_name;
		ifstream fin;
		string temp;
		fin.open("Data/" + yearname + "/class.txt");
		while (!fin.eof()) {
			fin >> temp;
			Classes_name.push_back(temp);
		}
		fin.close();
		return Classes_name;
	}
	void viewClasses(string name) {
		for (auto i : Classes) {
			cout << i.class_name << endl;
		}
		return;
	}
	void viewScoreOfClass(Class c, Course co, string semesterName) {
		ifstream fin;
		fin.open("Data/" + c.year_name + '/' + semesterName + "/Mark/" + co.courseID + ".csv");
		string No, Student_ID, Name, Total_Mark, Final_Mark, Midtern_Mark, Orther_Mark;
		while (getline(fin, No, ',')) {
			getline(fin, Student_ID, ',');
			getline(fin, Name, ',');
			getline(fin, Total_Mark, ',');
			getline(fin, Final_Mark, ',');
			getline(fin, Midtern_Mark, ',');
			getline(fin, Orther_Mark, ',');
			if (checkStudentInClass(c, Student_ID)) {
				cout << No << ' ' << Student_ID << ' ' << Name << ' ' << Total_Mark << ' ' << Final_Mark << ' ' << Midtern_Mark << ' ' << Orther_Mark << endl;
			}
		}
		fin.close();
		return;
	}
	bool checkStudentInClass(Class c, string ID) {
		for (auto i : c.students) {
			if (i.ID == ID) {
				return true;
			}
		}
		return false;
	}
};

