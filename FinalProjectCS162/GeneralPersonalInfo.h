#pragma once
#include <string>
#include <iostream>

#include "Date.h"

using namespace std;
class GeneralPersonalInfo
{
public:
    string username;
    string pass;
    string name;

    string phone;
    string mail;
    string gender;
    Date dob;

    GeneralPersonalInfo(string name, string uName, string pWord, string phone, string mail, string gender, Date dob);

    GeneralPersonalInfo();

    GeneralPersonalInfo addUsername(string uName);

    GeneralPersonalInfo addPassword(string pWord);

    virtual bool checkDefault();


    void getLoginData();


    friend ostream& operator<<(ostream& os, const GeneralPersonalInfo& g) {
        os << g.name << " " << g.username << " " << g.pass << " " << g.gender << " " << g.dob;
        return os;
    }

    friend bool operator==(const GeneralPersonalInfo& g1, const GeneralPersonalInfo& g2) {
        return (g1.name == g2.name && g1.username == g2.username && g1.pass == g2.pass && g1.gender == g2.gender && g1.dob == g2.dob);
    }
};
