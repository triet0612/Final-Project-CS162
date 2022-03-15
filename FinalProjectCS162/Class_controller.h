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
		SinglyLinkedList<string> classes_list;
		yearname = year;
		
		ofstream fout;
		fout.open('/' + year + "/class.txt");

		string class_name;
		cout << "Please input the classes you want to create one per each line" << endl;
		cout << "Enter 'stop' after finishing input" << endl;
		cin >> class_name;
		while (class_name != "stop") {
			classes_list.push_back(class_name);
			cin >> class_name;
		}
		cout << "Thank you for input, now add your students csv in the folder" << endl;
		
		cout << "Press any key to continue after you add the students" << endl;
		system("pause");
		Load_Classes();
		cout << "You've completed creating classes" << endl;
		return;
	}

	void Load_Classes() {
		SinglyLinkedList<string> Classes_name = Get_Classes();
		for (auto i : Classes_name) {
			Class c_temp;
			c_temp.addStuByCSV(yearname, i);
			Classes.push_back(c_temp);
		}
		return;
	}

	SinglyLinkedList<string> Get_Classes() {
		SinglyLinkedList<string> Classes_name;
		ifstream fin;
		string temp;
		fin.open('/' + yearname + "/class.txt");
		while (!fin.eof()) {
			fin >> temp;
			Classes_name.push_back(temp);
		}
		return Classes_name;
	}

	void viewClasses(string year) {

	}
	
	void viewScoreOfClass(string class_id) {

	}
};

