#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "SinglyLinkedList.h"
using namespace std;
class Class
{
public:
	struct student {
		string NO;
		string ID;
		string First_name;
		string Last_name;
		string Gender;
		string DOB;
		string Social_ID;
	};
	string class_name;
	string year_name;
	SinglyLinkedList<student> students;

	void addStuByCSV(string yearname, string classname) {
		class_name = classname;
		ifstream fin;
		fin.open('/' + yearname + '/' + classname + ".csv", ios::in);
		student temp;
		while (getline(fin, temp.NO, ',')) {
			getline(fin, temp.ID, ',');
			getline(fin, temp.First_name, ',');
			getline(fin, temp.Last_name, ',');
			getline(fin, temp.Gender, ',');
			getline(fin, temp.DOB, ',');
			getline(fin, temp.Social_ID, ',');
			students.push_back(temp);
		}
		fin.close();
		return;
	}

	void viewStu() {
		cout << "List of students in class " << class_name << endl;
		for (auto i : students) {
			cout << i.NO << " " 
				 << i.ID << " " 
				 << i.First_name << " "
				 << i.Last_name << " " 
				 << i.Gender << " " 
				 << i.DOB << " " 
				 << i.Social_ID << endl;
		}
	}
	bool checkStu(string ID) {
		for (auto i : students) {
			if (i.ID == ID) {
				return true;
			}
		}
		return false;
	}
};

