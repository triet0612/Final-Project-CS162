#pragma once
#include "PeopleController.h"
#include "Student.h"
#include <string>
#include <fstream>
class StudentController : public PeopleController
{
private:
	sll<Student> list;
public:
    StudentController() {
        loadData();
        curId = -1;
    }

	void regProc() override {
		system("cls");
		Student student;
		//student.getGeneralData();
		list.push_back(student);
	}

    void loadData() {
        ifstream ifs("Data/Student_account.txt");
        if (!ifs.is_open()) return;
        string tmp;
        getline(ifs, tmp);
        while (!ifs.eof()) {
            Student s;
            getline(ifs, tmp, ','); s.addUsername(tmp);
            if (tmp == "") break;
            getline(ifs, tmp, ','); s.addPassword(tmp);
            getline(ifs, tmp, ','); s.name = tmp;
            getline(ifs, tmp, ','); s.dob = tmp;
            getline(ifs, tmp, ','); s.gender = tmp;
            getline(ifs, tmp, ','); s.phone = tmp;
            getline(ifs, tmp); s.mail = tmp;
            list.push_back(s);
        }
    }

    bool loginProc(string username, string password) override {
        curId = list.findIndex([&](Student s) {return s.username == username && s.pass == password; });
        return curId != -1;
    }
};