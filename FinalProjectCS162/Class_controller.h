#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Class.h"
#include "SinglyLinkedList.h"
class Class_controller: public Class
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
		for (auto i : classes_list) {
			Class c;
			c.addStuByCSV();
		}
	}
	void viewClasses(string year) {

	}
	void viewScoreOfClass(string class_id) {

	}
};

