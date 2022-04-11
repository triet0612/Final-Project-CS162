#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "SinglyLinkedList.h"
#include "Button.h"
#include "InputRow.h"
#include "table.h"
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

	void addStuByCSV(string yearname, string classname);

	int chooseOption(Table& table);;

	void setupStudentsTable(Table& table);

	int getStudentFromTableProc();

	void viewStu(string yearname, string classname);
	
	bool checkStu(string ID);
};

