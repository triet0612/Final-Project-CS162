#pragma once
#include <string>
#include <iostream>

#include "Date.h"

using namespace std;
class GeneralPersonalInfo
{
protected:
    string name;
    string username;
    string pass;
    string phone;
    string mail;
    bool isMale;
    Date dob;
    friend class PeopleController;
public:

    GeneralPersonalInfo(string name, string uName, string pWord, string phone, string mail, bool isMale, Date dob) {
        this->name = name;
        this->username = uName;
        this->pass = pWord;
        this->phone = phone;
        this->isMale = isMale;
        this->mail = mail;
        this->dob = dob;
    }

    GeneralPersonalInfo() {
        name = "";
        username = "";
        pass = "";
        mail = "";
        phone = "";
        isMale = true;
        dob = Date();
    }

    GeneralPersonalInfo addUsername(string uName) {
        username = uName;
        return *this;
    }

    GeneralPersonalInfo addPassword(string pWord) {
        pass = pWord;
        return *this;
    }

    virtual bool checkDefault() {
        GeneralPersonalInfo nullGPI;
        return *this == nullGPI;
    }


    void getLoginData() {
        cin.ignore();
        std::cout << "Enter your username: \n";
        getline(cin, username);
        std::cout << "Enter your password: \n";
        getline(cin, pass);
    }


    friend ostream& operator<<(ostream& os, const GeneralPersonalInfo& g) {
        os << g.name << " " << g.username << " " << g.pass << " " << g.isMale << " " << g.dob;
        return os;
    }

    friend bool operator==(const GeneralPersonalInfo& g1, const GeneralPersonalInfo& g2) {
        return (g1.name == g2.name && g1.username == g2.username && g1.pass == g2.pass && g1.isMale == g2.isMale && g1.dob == g2.dob);
    }
};
