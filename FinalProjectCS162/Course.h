#pragma once

#include <fstream>
#include <string>
#include "SinglyLinkedList.h"

using namespace std;

class Course {
private:
	struct CourseStudent {
		string no, ID, lastname, firstname;
	};
public:
	sll<CourseStudent> students;
	int number, credits, maximumStudent;
	string courseID, nameOfCourse, nameOfTeacher, daySession1, daySession2;

	Course();
	bool readData(ifstream& finput);
	void writeData(ofstream& foutput) const;
	bool updateCourse();
	bool checkConflicted(const Course& course) const;
	pair<string, pair<int, int> > getDaySession1() const;
	pair<string, pair<int, int> > getDaySession2() const;
	void getCourseInformation();

	void getCourseStudents(string yearname, string semester) {
		string tmp;
		ifstream ifs("Data/" + yearname + '/' + semester + '/' + "Studentlist" + '/' + courseID +".csv");
		if (!ifs.is_open()) return;
		getline(ifs, tmp);
		while (!ifs.eof()) {
			CourseStudent stu;
			tmp = "";
			getline(ifs, tmp, ',');
			if (tmp == "") return;
			stu.no = tmp;
			getline(ifs, tmp, ',');
			stu.ID = tmp;
			getline(ifs, tmp, ',');
			stu.lastname = tmp;
			getline(ifs, tmp);
			stu.firstname = tmp;
			students.push_back(stu);
		}

		ifs.close();
	}
};
