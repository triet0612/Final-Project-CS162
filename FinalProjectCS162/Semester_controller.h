#pragma once
#include <iostream>
#include <direct.h>
#include <string.h>
#include "semester.h"
#include "SinglyLinkedList.h"
using namespace std;

class Semester_controller : public semester
{
public: 
	void create_semester(string yearname) {
		string n;
		cout << "Please enter the semester name: [s1] [s2] [s3]" << endl;
		cin >> n;
		semester_name = n;
		string path = "/" + yearname + "/" + n;
		//int a = mkdir(path.c_str());
		return;
	}
};

