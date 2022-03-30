#pragma once

#include "SinglyLinkedList.h"
#include "Course.h"
#include "Table.h"
#include "InputRow.h"
#include "Button.h"

class CoursesList : public SinglyLinkedList<Course> {
public:
	bool readFile(const string& path);
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

	void setupCoursesTable(Table& table) {
		system("cls");
		table = Table(0, 0, 30);

		table.addTitleRow_back(12, 16, 40, 30, 13, 18, 20, 20);
		table.getRow(0).addText((string)"No", (string)"Course ID", (string)"Name of course", (string)"Name of teacher", (string)"credits", (string)"Max student"
			, (string)"Day session 1", (string)"Day session 2");
		table.addRow_back((string)"Add...");
		for (const Course& course : (*this)) {
			table.addRow_back(to_string(course.number), course.courseID, course.nameOfCourse, course.nameOfTeacher,
				to_string(course.credits), to_string(course.maximumStudent), course.daySession1, course.daySession2);
		}

		table.setDefaultType();
		table.render();

		table.setCursorInside();
	}

	int inputCoursesProc() {
		int type = 0;
		Table table;
		setupCoursesTable(table);
		table.update({ -32, 0 }, [&](Table& table) {type = chooseOption(table); });
		return type;
	}

	//--
	void viewCourses(string yearname, string semester) {
		readFile("Data/" + yearname + "/" + semester + "/Courses.csv");
		int type = inputCoursesProc();
		while (type != -1) {
			if (type == 1) {
				//createClass(yearname);
			}
			else {
				//schoolYearOptions(sc.yearList[type - 2]);
			}
			type = inputCoursesProc();
		}
		system("cls");
	}

	void displayListOfCourses() const;
	bool containsCourse(const string& courseID) const;
	void updateInformation();
	bool writeFile(const string& path) const;
	bool checkSessionsConflicted(const bool *enrolled) const;
	Course& getCourse(const string& courseID);
};