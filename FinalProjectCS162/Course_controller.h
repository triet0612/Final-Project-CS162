#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <direct.h>
#include <string>

#include "helper.h"
#include "StudentScore.h"

#include "SinglyLinkedList.h"
#include "Course.h"
#include "StudentScore.h"
#include "CoursesRegistrationsController.h"
#include "CoursesList.h"
#include "helper.h"
using namespace std;


class Course_controller {
private:
	SinglyLinkedList<StudentScore> getScore(const string& courseID) const;
	void printScoresToCSVfile(const string&courseID, const SinglyLinkedList<StudentScore>& scoresOfStudents) const;
	void displayRegistrationTable(const bool* status, const int* numberOfStudents, const SinglyLinkedList<CourseRegistration> &coursesRegistrations) const;
	void updateEnrolledCoursesInCSVfile(const int studentID, const SinglyLinkedList<string>& enrolledCoursesID);
	void printEnrolledCoursesInCSVfile(const SinglyLinkedList<pair<int, SinglyLinkedList<string> > > &information);
public:
	string yearName, semesterName;
	CoursesList courses;
	Course_controller();
	Course_controller(string yearname, string semesterName) {
		this->yearName = yearName;
		this->semesterName = semesterName;
		loadCourses(yearname, semesterName);
	};
	
	void loadCourses(const string& yearName, const string& semesterName);

	string getFinScoreOfStudent(int courseIdx, string stuID) {
		return this->courses[courseIdx].getFinScoreOfStudent(this->yearName, this->semesterName, stuID);
	}

	void loadCourseStudent(int courseIdx) {
		this->courses[courseIdx].loadScoreCourseStudents(this->yearName, this->semesterName);
	}
	//--
	int chooseOption(Table& table) {
		ConsoleGraphics* graphics = &ConsoleGraphics::getInstance();
		int type = -1;
		graphics->loopBoolean([&](pair<int, int> input) {
			int y = 0, x = 0;
			if (input.first == INPUT_CODE::ESC) return false;
			if (input.first == INPUT_CODE::ENTER) {
				table.defaultPressAnimation();
				type = table.getCurRow();
				return false;
			}
			else if (input.first == INPUT_CODE::DIRECTION) {
				graphics->getNextDirection(input, x, y);

				table.switchPage(table.getCurPage() + x);
				table.focusRow(table.getCurRow() + y);

				graphics->hideCursor();
			}
			return true;

			});
		return type;
	};

	void setupCourseOptionsTable(Table& table, string courseID, int offsetY = 0) {
		table = Table(10, 5 + offsetY, 5);

		table.addTitleRow_back(40);
		table.getRow(0).addText(courseID);
		table.addRow_back("View students in course");
		table.addRow_back("Export student list to CSV");
		table.addRow_back("View the scoreboard in course");
		table.addRow_back("Modify/Delete course");
		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int inputCourseOptionTableProc(string courseID, int offsetY = 0) {
		int type = 0;
		Table table;
		setupCourseOptionsTable(table, courseID, offsetY);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	void viewCourseOptions(string yearname, string semester, int id) {
		string courseID = this->courses[id].courseID;
		int type = inputCourseOptionTableProc(courseID, id);
		switch (type)
		{
		case 1: viewStu(yearname, semester, id); break;
		case 2: break;
		case 3: viewScoreStu(yearName, semester, id); break;
		case 4: this->courses.modifyCourse(id); system("cls"); break;
		default:
			break;
		}
		//type = inputCourseOptionTableProc(courseID, id);
		this->courses.saveCourses(yearname, semester);
		return;
	};

	//--
	void setupCourseStudentsTable(Table& table, int id) {
		system("cls");
		table = Table(0, 0, 30);

		table.addTitleRow_back(12, 16, 14, 20);
		table.getRow(0).addText((string)"No", (string)"ID", (string)"First Name", (string)"Last Name");
		if (courses[id].students.size() == 0) {
			table.addRow_back("Empty");
		}
		int row = 0;
		for (auto i : courses[id].students) {
			++row;
			table.addRow_back(to_string(row), i.ID, i.firstname, i.lastname);
		}

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int getCourseStudentFromTableProc(int id) {
		int type = 0;
		Table table;
		setupCourseStudentsTable(table, id);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	void viewStu(string yearname, string semester, int id) {

		courses[id].loadCourseStudents(yearname, semester);
		int type = getCourseStudentFromTableProc(id);

		while (type != -1) {

			type = getCourseStudentFromTableProc(id);
		}
	}

	void courseProc(string yearname, string semester);

	bool containsCourse(const string& courseID) const;

	//--
	void setupScoreCourseStudentsTable(Table& table, int id) {
		system("cls");
		table = Table(0, 0, 30);

		table.addTitleRow_back(12, 16, 14, 18, 18, 14, 18);
		table.getRow(0).addText((string)"No", (string)"ID", (string)"Name", (string)"Total Score", (string)"Final Score", (string)"Midterm", (string)"Other Score");
		if (courses[id].scoreStudents.size() == 0) {
			table.addRow_back("Empty");
		}
		int row = 0;
		for (auto i : courses[id].scoreStudents) {
			++row;
			table.addRow_back(to_string(row), i.ID, i.name, i.totScore, i.FinScore, i.midScore, i.otherScore);
		}

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int getScoreCourseStudentFromTableProc(int id) {
		int type = 0;
		Table table;
		setupScoreCourseStudentsTable(table, id);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	void viewScoreStu(string yearname, string semester, int id) {

		courses[id].loadScoreCourseStudents(yearname, semester);
		int type = getScoreCourseStudentFromTableProc(id);

		while (type != -1) {

			type = getScoreCourseStudentFromTableProc(id);
		}
	}


	void updateScore(const string& courseID, const int studentID);

	//--
	void setupScoreStudentTable(Table& table, int stuID) {
		system("cls");
		table = Table(0, 0, 30);

		table.addTitleRow_back(16, 20, 16, 16, 16, 16);
		table.getRow(0).addText((string)"Course_ID", (string)"Student's name", (string)"Total Mark",
			(string)"Final Mark", (string)"Midterm mark", (string)"Other mark");

		for (auto course : courses) {
			for (const StudentScore& studentScore : (this->getScore(course.courseID))) {
				if (studentScore.studentID == stuID) {
					table.addRow_back(course.courseID, studentScore.name,
						doubleToStr(studentScore.totalMark, 2), doubleToStr(studentScore.finalMark, 2), doubleToStr(studentScore.midtermMark, 2),
						doubleToStr(studentScore.otherMark, 2));
					break;
				}
			}
		}
		if (table.getTotalRows() == 1) {
			table.addRow_back((string)"Empty");
		}

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int getScoreStudentFromTableProc(int stuID) {
		int type = 0;
		Table table;
		setupScoreStudentTable(table, stuID);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	void viewScoresOfAStudent(const string studentID);

	//--
	void renderCaution(string s = "Invalid input") {
		TextBox notice = TextBox(5, 20, 40, 3, false, 0, 12).setText(s);
		notice.render();
	}

	void renderAccept() {
		TextBox notice = TextBox(5, 20, 40, 3, false, 0, 10).setText("Operated successfully, loading ..."); 
		notice.render();
		Sleep(200);
		notice = TextBox(5, 20, 40, 3, false, 0, 10).setText("                                          ");
		notice.render();
	}

	void setupEnrollCourseTable(int initRow, Table& table, sll<bool>& enrolled, sll<int>& curNumsStu, CoursesRegistrationsController& courseRegController, CoursesList& validCourse, sll<int>& validRegPos) {
		table = Table(0, 12, 7);
		table.addTitleRow_back(5,16,12,16,16,10,15);
		table.getRow(0).addText((string)"No", (string)"CourseID", (string)"Credits", (string)"Start day", (string)"end day", (string)"Total", (string)"Status");

		for (int i = 0; i < validRegPos.size(); ++i) {
			Course target = validCourse[i];
			CourseRegistration c = courseRegController.coursesRegistrations[validRegPos[i]];
			string status = (enrolled[validRegPos[i]]) ? "Joined" : "Not joined";
			string totalStu = to_string(curNumsStu[validRegPos[i]]) + "/" + to_string(target.maximumStudent);
			table.addRow_back(to_string(i + 1), target.courseID, to_string(target.credits), c.getStartDate().convert2String(), c.getEndDate().convert2String(), totalStu, status);
		}
		table.setDefaultType();
		table.render();

		table.setCursorOnRow(initRow);
	}

	int inputEnrollCoursesTableProc(int stuID, sll<int>& curNumsStu, sll<bool>& status, CoursesRegistrationsController& courseRegController, CoursesList& validCourses, sll<int>& validRegPos, int initRow = 1) {
		int type = 0;
		Table table;
		setupEnrollCourseTable(initRow, table, status, curNumsStu, courseRegController, validCourses, validRegPos);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	void getValidCourses(CoursesRegistrationsController& courseRegController, CoursesList& validCourses, sll<int>& validRegPos) {
		int i = 0;
		for (auto c : courseRegController.coursesRegistrations) {
			++i;
			string id = c.getCourseID();
			int idx = this->courses.findIndex([&](Course target) { return target.courseID == id; });
			if (idx == -1) continue;
			validRegPos.push_back(i - 1);
			validCourses.push_back(this->courses[idx]);
		}

	}

	void enrollCourseProc(int stuId, string firstname, string lastname) {
		CoursesRegistrationsController courseRegController(this->yearName, this->semesterName);
		courseRegController.loadEnrolledCourses();
		CoursesList validCourses;
		sll<int> validRegPos;
		getValidCourses(courseRegController, validCourses, validRegPos);
		sll<int> curNumsStu;
		sll<bool> status;
		courseRegController.getInfoEnrollmentStudent(stuId, status, curNumsStu);
		int type = 1;
		do {
			type = inputEnrollCoursesTableProc(stuId, curNumsStu, status, courseRegController,validCourses, validRegPos, type);
			if (type != -1) {
				int i = type - 1;
				int validIdx = validRegPos[i];
				bool& enrollStatus = status[validRegPos[i]];
				if (!courseRegController.coursesRegistrations[validIdx].checkRegistrationDates()) {
					renderCaution("Timeout !");
					continue;
				}
				if (enrollStatus) {
					enrollStatus = false;
					--curNumsStu[validIdx];
				}
				else {
					int cnt = 0;
					for (auto i : status) cnt += i;

					if (cnt >= 5) {
						renderCaution("Maximum: 5");
						continue;
					}
					if (validCourses[i].maximumStudent <= curNumsStu[validIdx]) {
						renderCaution("Course is full");
						continue;
					}
					if (this->checkSessionsConflicted(status, courseRegController, validCourses, validRegPos)) {
						renderCaution("Conflicted");
						continue;
					}
					enrollStatus = true;
					++curNumsStu[validIdx];
					renderAccept();
				}
			}
			courseRegController.updateStatusEnrolledCourses(stuId, status);
			courseRegController.saveEnrolledCourses();
		} while (type != -1);
		SaveStudentEnrollmentOfCourses(to_string(stuId), lastname, firstname, validCourses, validRegPos, status);

	}

	bool checkSessionsConflicted(sll<bool> status, CoursesRegistrationsController& CourseRegController, CoursesList& validCourses, sll<int>& validRegPos) {
		const int numberOfCourses = validCourses.size();
		SinglyLinkedList<pair<string, pair<int, int> > > sessions[2];
		for (int i = 0; i < validRegPos.size(); ++i) {
			CourseRegistration cReg = CourseRegController.coursesRegistrations[validRegPos[i]];
			Course c = this->courses[i];
			if (status[validRegPos[i]]) {
				sessions[0].push_back(c.getDaySession1());
				sessions[1].push_back(c.getDaySession2());
			}
		}

		const int numberOfEnrolledCourses = sessions[0].size();
		for (int i = 1; i < numberOfEnrolledCourses; ++i)
			for (int j = 0; j < i; ++j)
				for (int x = 0; x < 2; ++x)
					for (int y = 0; y < 2; ++y)
						if (sessions[x][i].first == sessions[y][j].first && checkIntersection(sessions[x][i].second, sessions[y][j].second))
							return true;
		return false;
	};

	void SaveStudentEnrollmentOfCourses(string stuId, string lastname, string firstname, CoursesList& validCourses, sll<int>& validRegPos, sll<bool>& status) {
		for (int i = 0; i < validRegPos.size(); ++i) {
			int idx = validRegPos[i];
			validCourses[i].loadCourseStudents(this->yearName, this->semesterName);
			if (status[idx]) validCourses[i].updateStudentOfThisCourse(stuId, lastname, firstname);
			else 
				validCourses[i].delStudentOfThisCourse(stuId);
			validCourses[i].saveCourseStudents(this->yearName, this->semesterName);
		}
	}

	//--

	
	SinglyLinkedList<pair<int, SinglyLinkedList<string> > > getListOfEnrolledCourses() const;

	SinglyLinkedList<string> getListOfEnrolledCoursesOfStudent(const int studentID) const;

	int countStudentsInCourse(const string& courseID) const;

	void changeEnrolledCourses(const int studentID);

	SinglyLinkedList<int> getCourseListOfStudentsID(const string& courseID) const;

	bool exportListOfStudentsID(const string& courseID) const;

	void updateCoursesInformation();
};