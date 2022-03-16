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
	//load class list
	void Load_Classes() {
		SinglyLinkedList<string> Classes_name = Get_Classes();
		for (auto i : Classes_name) {
			Class c_temp;
			c_temp.addStuByCSV(yearname, i);
			Classes.push_back(c_temp);
		}
		return;
	}
	//load class list from /yearname/class.txt
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
};

