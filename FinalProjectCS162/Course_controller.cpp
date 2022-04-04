#include "Course_controller.h"


Course_controller::Course_controller() {};

void Course_controller::loadCourses(const string& yearName, const string& semesterName) {
	(this->yearName) = yearName;
	(this->semesterName) = semesterName;
	if (!(this->courses).readFile("Data/" + yearName + "/" + semesterName + "/Courses.csv"))
		cerr << "There was error in reading data\n";
};

//--
void Course_controller::courseProc(string yearname, string semester) {

	int type = this->courses.viewCourses(yearname, semester);
	while (type != -1) {
		if (type == 1) {
			this->courses.createCourse();
			this->courses.saveCourses(yearName, semester);
			system("cls");
		}
		else {
			this->viewCourseOptions(yearname, semester, type - 2);
			system("cls");
		}
		type = this->courses.inputCoursesTableProc();
	}

}

bool Course_controller::containsCourse(const string& courseID) const {
	return (this->courses).containsCourse(courseID);
};

//*
void Course_controller::updateScore(const string& courseID, const int studentID) {
	if (!(this->containsCourse(courseID))) {
		cout << "There is no course with " << courseID << '\n';
		return;
	}
	double score;
	int id = -1, number = 0;
	StudentScore studentScore;
	SinglyLinkedList<StudentScore> scoresOfStudents = this->getScore(courseID);
	for (const StudentScore& studentScore : scoresOfStudents) {
		if (studentScore.studentID == studentID) {
			id = number;
			break;
		}
		++number;
	}
	if (id < 0) {
		cout << "There was no student with " << studentID << " in the course " << courseID << "\n";
		return;
	}
	studentScore = scoresOfStudents[id];
	do {
		system("cls");
		studentScore.printData(cout);
		cout << "Please enter one of following options\n"
			 << "1. Stop updating score\n"
		 	 << "2. Update total mark\n"
		 	 << "3. Update final mark\n"
		 	 << "4. Update midterm mark\n"
	 		 << "5. Update other mark\n"
			 << "Your option: ";
		cin >> number;
		if (number == 1) {
			scoresOfStudents[id] = studentScore;
			break;
		} else if (number < 1 || number > 5) {
			cout << "Option is invalid\n";
		} else {
			cout << "Please enter new score: ";
			cin >> score;
			switch (number) {
			case 2:
				studentScore.totalMark = score;
				break;
			case 3:
				studentScore.finalMark = score;
				break;
			case 4:
				studentScore.midtermMark = score;
				break;
			case 5:
				studentScore.otherMark = score;
				break;
			}
		}
		system("pause");
	} while (number != 1);
	printScoresToCSVfile(courseID, scoresOfStudents);
};

SinglyLinkedList<StudentScore> Course_controller::getScore(const string& courseID) const {
	SinglyLinkedList<StudentScore> scoresOfStudents;
	ifstream finput("Data/" + (this->yearName) + "/" + (this->semesterName) + "/Mark/" + courseID + ".csv");
	if (finput) {
		StudentScore studentScore;
		finput.ignore(5000, '\n'); //Not read first line
		while (studentScore.readData(finput)) 
			scoresOfStudents.push_back(studentScore);
	}
	finput.close();
	return scoresOfStudents;
};

void Course_controller::printScoresToCSVfile(const string& courseID, const SinglyLinkedList<StudentScore>& scoresOfStudents) const {
	ofstream foutput("Data/" + (this->yearName) + "/" + (this->semesterName) + "/Mark/" + courseID + ".csv");
	foutput << "No,Student ID,Name,Total Mark,Final Mark,Midtern Mark,Orther Mark\n";
	for (const StudentScore& studentScore : scoresOfStudents)
		studentScore.printToCSVfile(foutput);
	foutput.close();
};


void Course_controller::viewScoresOfAStudent(const string studentID) {
	int type = getScoreStudentFromTableProc(stoi(studentID));
};

SinglyLinkedList<pair<int, SinglyLinkedList<string> > > Course_controller::getListOfEnrolledCourses() const {
	SinglyLinkedList<pair<int, SinglyLinkedList<string> > > result;
	ifstream finput("Data/" + (this->yearName) + "/" + (this->semesterName) + "/EnrolledCourses.csv");
	if (finput) {
		SinglyLinkedList<string> coursesID;
		string line, courseID;
		int studentID;
		finput.ignore(1000, '\n'); //ignore first line
		while (getline(finput, line)) {
			stringstream information(line + ',');
			information >> studentID;
			information.ignore(1000, ',');
			coursesID.clear();
			while (getline(information, courseID, ','))
				coursesID.push_back(courseID);
			result.push_back({ studentID, coursesID});
		}
	}
	finput.close();
	return result;
};

SinglyLinkedList<string> Course_controller::getListOfEnrolledCoursesOfStudent(const int studentID) const {
	for (const auto& data : (this->getListOfEnrolledCourses()))
		if (data.first == studentID)
			return data.second;
	return SinglyLinkedList<string>();
};

int Course_controller::countStudentsInCourse(const string& courseID) const {
	int result = 0;
	for (const auto& information : (this->getListOfEnrolledCourses()))
		for (const string& id : information.second)
			if (id == courseID) {
				++result;
				break;
			}
	return result;
};
//*
void Course_controller::displayRegistrationTable(const bool* status, const int* numberOfStudents,const SinglyLinkedList<CourseRegistration>& coursesRegistrations) const {
	int number_length = strlen("no"),
		credits_length = strlen("credits"),
		nameOfCourse_length = strlen("Name of course"),
		courseID_length = strlen("Course ID"),
		totalLength, i = 0;
	const int numberOfStudents_length = 25,
		      status_length = 10,
			  startDate_length = 20,
			  endDate_length = 20,
			  numberOfCourses = (this->courses).size();
	// Find the require length for each information
	for (const Course& course : (this->courses)) {
		number_length = max(number_length, getNumberOfDigits(course.number));
		credits_length = max(credits_length, getNumberOfDigits(course.credits));
		courseID_length = max(courseID_length, (int)course.courseID.size());
		nameOfCourse_length = max(nameOfCourse_length, (int)course.nameOfCourse.size());
	}
	number_length += 2;
	credits_length += 2;
	courseID_length += 2;
	nameOfCourse_length += 2;
	totalLength = 9 + startDate_length + endDate_length + number_length + credits_length + nameOfCourse_length + courseID_length + numberOfStudents_length + status_length;
	cout << string(totalLength, '-') << '\n';
	cout << '|'
		<< setw(number_length) << "No" << '|'
		<< setw(courseID_length) << "Course ID" << '|'
		<< setw(nameOfCourse_length) << "Name of course" << '|'
		<< setw(credits_length) << "Credits" << '|'
		<< setw(startDate_length) << "Registration start" << '|'
		<< setw(endDate_length) << "Registration end" << '|'
		<< setw(numberOfStudents_length) << "Number of students" << '|'
		<< setw(status_length) << "Status" << '|'
		<< '\n';
	cout << string(totalLength, '-') << '\n';
	for (const Course& course : (this->courses)) {
		stringstream studentsNumber;
		studentsNumber << numberOfStudents[i] << '/' << course.maximumStudent;
		cout << '|'
			 << setw(number_length) << course.number << '|'
			 << setw(courseID_length) << course.courseID << '|'
			 << setw(nameOfCourse_length) << course.nameOfCourse << '|'
			 << setw(credits_length) << course.credits << '|'
			 << setw(startDate_length) << coursesRegistrations[i].getStartDate().convert2String() << '|'
			 << setw(endDate_length) << coursesRegistrations[i].getEndDate().convert2String() << '|'
			 << setw(numberOfStudents_length) << studentsNumber.str() << '|'
			 << setw(status_length) << (status[i] ? "Join" : "") << '|'
	 		 << '\n';
		++i;
	}
	cout << string(totalLength, '-') << '\n';
};

void Course_controller::changeEnrolledCourses(const int studentID) {
	const int numberOfCourses = (this->courses).size();
	bool* status = new bool[numberOfCourses];
	/*
	status[i] is true if student has joined course and false otherwise
	*/
	int* numberOfStudents = new int[numberOfCourses];
	SinglyLinkedList<CourseRegistration> coursesRegistrations;
	SinglyLinkedList<string> enrolledCoursesID;
	int option = 0, id;
	string courseID;
	//Load information
	for (int i = 0; i < numberOfCourses; ++i) {
		status[i] = false;
		numberOfStudents[i] = this->countStudentsInCourse((this->courses)[i].courseID);
	}
	for (const Course& course : (this->courses)) {
		CourseRegistration courseRegistration;
		courseRegistration.createRegistration(this->yearName, this->semesterName, course.courseID);
		courseRegistration.loadDates();
		coursesRegistrations.push_back(courseRegistration);
	}
	for (const string& courseID : (this->getListOfEnrolledCoursesOfStudent(studentID)))
		for (int i = 0; i < numberOfCourses; ++i)
			if (courseID == (this->courses)[i].courseID) {
				status[i] = true;
				break;
			}
	//Change information
	while (option != 1) {
		system("cls");
		cout << "Student ID:" << studentID << '\n';
		this->displayRegistrationTable(status, numberOfStudents, coursesRegistrations);
		cout << "1. Escape\n"
			 << "2. Join a course\n"
			 << "3. Remove a course from enrolled course list\n"
			 << "Please enter your option: ";
		if (!readInteger(option) || option < 1 || option > 3) {
			cout << "Option is invalid\n";
			system("pause");
			continue;
		}
		if (option == 1) {
			/*
			if ((this->courses).checkSessionsConflicted(status)) {
				cout << "Warning: There might be two courses whose sessions are conflicted\n";
				system("pause");
			}
			*/
			break;
		}
		cout << "Please enter course id: ";
		getline(cin, courseID);
		if (!(this->containsCourse(courseID))) {
			cout << "There were currently no course with id '" << courseID << "'\n";
			system("pause");
			continue;
		}
		for (int i = 0; i < numberOfCourses; ++i)
			if ((this->courses)[i].courseID == courseID) {
				id = i;
				break;
			}
		if (!coursesRegistrations[id].checkRegistrationDates()) {
			cout << "The course registration is not currently active\n";
			system("pause");
			continue;
		}
		if (option == 2) {
			if (status[id]) {
				cout << "The course has already been in your enrolled course list\n";
			} else if (numberOfStudents[id] >= (this->courses)[id].maximumStudent) {
				cout << "The allowed number of students in this course is maximum\n";
			} else {
				status[id] = true;
				if ((this->courses).checkSessionsConflicted(status)) {
					cout << "Register unsucessfully because the sessions of the course are conflicted with existing enrolled course sessions\n";
					status[id] = false;
				} else {
					cout << "Register sucessfully\n";
					++numberOfStudents[id];
				}
			}
			system("pause");
		} else { // if (option == 3)
			if (status[id]) {
				cout << "Remove sucessfully\n";
				--numberOfStudents[id];
				status[id] = false;
			} else {
				cout << "Student has not joined the course yet\n";
			}
			system("pause");
		}
	}
	for (int i = 0; i < numberOfCourses; ++i)
		if (status[i])
			enrolledCoursesID.push_back((this->courses)[i].courseID);
	this->updateEnrolledCoursesInCSVfile(studentID, enrolledCoursesID);
	delete[] status;
	delete[] numberOfStudents;
};	

void Course_controller::updateEnrolledCoursesInCSVfile(const int studentID, const SinglyLinkedList<string>& enrolledCoursesID) {
	SinglyLinkedList<pair<int, SinglyLinkedList<string> > > coursesID = this->getListOfEnrolledCourses();
	for (auto& data : coursesID)
		if (data.first == studentID) {
			data.second = enrolledCoursesID;
			break;
		}
	this->printEnrolledCoursesInCSVfile(coursesID);
};

void Course_controller::printEnrolledCoursesInCSVfile(const SinglyLinkedList<pair<int, SinglyLinkedList<string> > >& information) {
	ofstream foutput("Data/" + (this->yearName) + "/" + (this->semesterName) + "/EnrolledCourses.csv");
	if (foutput) {
		foutput << "Student ID, Course1, Course2, Course3, Course4, Course5\n";
		for (const auto& data : information) {
			foutput << data.first;
			for (const auto& courseID : data.second)
				foutput << ',' << courseID;
			foutput << '\n';
		}
	}
	foutput.close();
};

SinglyLinkedList<int> Course_controller::getCourseListOfStudentsID(const string& courseID) const {
	SinglyLinkedList<int> result;
	for (const auto &information : (this->getListOfEnrolledCourses()))
		for (const string& id : information.second)
			if (id == courseID) {
				result.push_back(information.first);
				break;
			}
	return result;
};

bool Course_controller::exportListOfStudentsID(const string& courseID) const {
	//Print list of student ID in a course to a CSV file (save file at input path)
	if (!(this->containsCourse(courseID))) {
		cout << "There is no course with " << courseID << '\n';
		return false;
	}
	string path;
	cout << "Please enter the path of the csv file you want to save at: ";
	cin >> path;
	if (_mkdir(path.c_str())) {
		ofstream foutput(path + "/" + courseID + ".csv");
		foutput << "StudentID\n";
		for (const int& studentID : (this->getCourseListOfStudentsID(courseID)))
			foutput << studentID << '\n';
		foutput.close();
		cout << "File was successfully saved\n";
		return true;
	}
	cout << "File was not successfully saved\n";
	return false;
};

void Course_controller::updateCoursesInformation() {
	(this->courses).updateInformation();
	(this->courses).writeFile("Data/" + yearName + "/" + semesterName + "/Courses.csv");
};