#pragma once
#include "GeneralPersonalInfo.h"

class Student : public GeneralPersonalInfo {
public:
    string id, stuId, socialId, lastname, firstname;
    Student(string fName, string lName, string uName, string pWord, string phone, string mail, string gender, Date dob, string id, string stuId, string socialId);

    Student();

    friend ostream& operator<<(ostream& os, const Student& s) {
        os << s.id << " " << s.name << " " << s.username << " " << s.pass << " " << s.gender << " " << s.dob << " " << s.stuId << " " << s.socialId;
        return os;
    };
};



