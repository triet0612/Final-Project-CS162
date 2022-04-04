#pragma once

#include <fstream>
#include <string>
#include "SinglyLinkedList.h"

using namespace std;

class Course {
private:
	struct CourseStudent {
		string ID, lastname, firstname;
	};
	struct ScoreStudent {
		string ID, name;
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

	void loadCourseStudents(string yearname, string semester) {
		string tmp;
		ifstream ifs("Data/" + yearname + '/' + semester + '/' + "Studentlist" + '/' + courseID + ".csv");
		if (!ifs.is_open()) return;
		getline(ifs, tmp);
		while (!ifs.eof()) {
			CourseStudent stu;
			tmp = "";
			getline(ifs, tmp, ',');
			if (tmp == "") return;
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
	
	void saveCourseStudents(string yearname, string semester) {
		string tmp;
		ofstream ofs("Data/" + yearname + '/' + semester + '/' + "Studentlist" + '/' + courseID + ".csv");
		int row = 0;
		ofs << "No,ID,Last name,First name";
		for (auto elem : this->students) {
			ofs << "\n" << to_string(++row) << ","<< elem.ID << "," << elem.lastname << "," << elem.firstname;
		}

		ofs.close();
	}

	void delStudentOfThisCourse(string stuId) {
		int idx = students.findIndex([&](CourseStudent target) {return target.ID == stuId; });
		if (idx == -1) return;
		students.deleteAt(idx);

	}

	void updateStudentOfThisCourse(string stuId, string lastname, string firstname) {
		int idx = students.findIndex([&](CourseStudent target) {return target.ID == stuId; });
		CourseStudent tmp;
		tmp.ID = stuId;
		tmp.firstname = firstname;
		tmp.lastname = lastname;
		if (idx == -1) students.push_back(tmp);
		else students[idx] = tmp;
	}

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
