#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Class.h"
#include "SinglyLinkedList.h"
class Class_controller
{
public:
	string yearname;
	SinglyLinkedList<Class> Classes;
	void createClass(string year) {
		yearname = year;
		
		ofstream fout;
		fout.open('/' + year + "/class.txt");

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
	//load data of classes list
	void Load_Classes() {
		SinglyLinkedList<string> Classes_name = Get_Classes();
		for (auto i : Classes_name) {
			Class c_temp;
			c_temp.addStuByCSV(yearname, i);
			Classes.push_back(c_temp);
		}
		return;
	}
	//load class name list from /yearname/class.txt
	SinglyLinkedList<string> Get_Classes() {
		SinglyLinkedList<string> Classes_name;
		ifstream fin;
		string temp;
		fin.open('/' + yearname + "/class.txt");
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
	void viewScoreOfClass(string semester, string coursename) {
		ifstream fin;
		string NO, stuID, name, totalm, finalm, midm,othem;
		fin.open('/' + yearname + '/' + semester + "/Mark/" + coursename + ".csv");
		while (getline(fin, NO, ',')) {
			getline(fin, stuID, ',');
			getline(fin, name, ',');
			getline(fin, totalm, ',');
			getline(fin, finalm, ',');
			getline(fin, midm, ',');
			getline(fin, othem, ',');
			cout << NO << stuID << name << totalm << finalm << midm << othem << endl;
		}
		return;
	}
};

