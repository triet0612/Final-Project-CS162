#pragma once
#include "GeneralPersonalInfo.h"

class Student : public GeneralPersonalInfo {
private:
    string id, stuId, socialId;
public:
    Student(string fName, string lName, string uName, string pWord, string phone, string mail, string gender, Date dob, string id, string stuId, string socialId) : GeneralPersonalInfo(name, uName, pWord, phone, mail, gender, dob) {
        this->id = id;
        this->stuId = stuId;
        this->socialId = socialId;
    }

    Student() : GeneralPersonalInfo() {
        id = "";
        stuId = "";
        socialId = "";
    }

    friend ostream& operator<<(ostream& os, const Student& s) {
        os << s.id << " " << s.name << " " << s.username << " " << s.pass << " " << s.gender << " " << s.dob << " " << s.stuId << " " << s.socialId;
        return os;
    };
};


