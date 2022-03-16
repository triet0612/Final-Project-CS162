#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "SinglyLinkedList.h"
using namespace std;
class Class
{
private:
	struct student {
		string NO;
		string ID;
		string First_name;
		string Last_name;
		string Gender;
		string DOB;
		string Social_ID;
	};
public:
	string class_name;
	SinglyLinkedList<student> students;

	void addStuByCSV(string yearname, string name) {
		class_name = name;
		ifstream fin;
		fin.open('/' + yearname + '/' + name + ".csv", ios::in);
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
};

