#pragma once
#include "PeopleController.h"
#include "Student.h"
class StudentController : public PeopleController
{
private:
	sll<Student> list;
public:
	void regProc() override {
		system("cls");
		Student student;
		//student.getGeneralData();
		list.push_back(student);
	}

	bool loginProc() override {
		string username, password;
		pair<string, string> ans = inputLoginProc();
		username = ans.first;
		password = ans.second;

		return false;
	}
};