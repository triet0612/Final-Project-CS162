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
	struct ScoreStudent {
		string no, ID, name;
		string totScore, FinScore, midScore, otherScore;
	};
public:
	sll <string> timeset;
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
	sll<ScoreStudent> scoreStudents;

	void getCourseStudents(string yearname, string semester) {
		string tmp;
		ifstream ifs("Data/" + yearname + '/' + semester + '/' + "Studentlist" + '/' + courseID + ".csv");
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
	};

	void loadScoreCourseStudents(string yearname, string semester) {
		string tmp;
		ifstream ifs("Data/" + yearname + '/' + semester + '/' + "Mark" + '/' + courseID + ".csv");
		if (!ifs.is_open()) return;
		getline(ifs, tmp);
		while (!ifs.eof()) {
			ScoreStudent stu;
			tmp = "";
			getline(ifs, tmp, ',');
			if (tmp == "") return;
			stu.no = tmp;
			getline(ifs, tmp, ',');
			stu.ID = tmp;
			getline(ifs, tmp, ',');
			stu.name = tmp;
			getline(ifs, tmp, ',');
			stu.totScore = tmp;
			getline(ifs, tmp, ',');
			stu.FinScore = tmp;
			getline(ifs, tmp, ',');
			stu.midScore = tmp;
			getline(ifs, tmp);
			stu.otherScore = tmp;
			scoreStudents.push_back(stu);
		}

		ifs.close();
	}

	string getFinScoreOfStudent(string yearname, string semester, string stuID) {
		int id = scoreStudents.findIndex([&](ScoreStudent target) { return target.ID == stuID; });
		if (id == -1) return "X";
		return scoreStudents[id].FinScore;
	}

	int getTimesetId(string s) {
		return this->timeset.findIndex([&](string target) {return target == s; });
	}
};
