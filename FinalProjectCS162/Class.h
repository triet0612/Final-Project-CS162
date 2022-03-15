#pragma once
#include <iostream>
#include <fstream>
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
		fin.open('/' + yearname + '/' + name + '.csv');
		
	}
};

