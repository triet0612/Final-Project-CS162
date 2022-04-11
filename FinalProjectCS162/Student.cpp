#include "Student.h"

Student::Student(string fName, string lName, string uName, string pWord, string phone, string mail, string gender, Date dob, string id, string stuId, string socialId) : GeneralPersonalInfo(name, uName, pWord, phone, mail, gender, dob) {
    this->id = id;
    this->stuId = stuId;
    this->socialId = socialId;
}

Student::Student() : GeneralPersonalInfo() {
    id = "";
    stuId = "";
    socialId = "";
}
