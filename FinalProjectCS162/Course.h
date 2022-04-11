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

	void loadCourseStudents(const string& yearname, const string& semester);
	
	void saveCourseStudents(const string& yearname, const string& semester);

	void delStudentOfThisCourse(const string& stuId);

	void updateStudentOfThisCourse(const string& stuId, const string& lastname, const string& firstname);

	void loadScoreCourseStudents(const string& yearname, const string& semester);

	string getFinScoreOfStudent(const string& yearname, const string& semester, const string& stuID);

	int getTimesetId(const string& s) const;
};
