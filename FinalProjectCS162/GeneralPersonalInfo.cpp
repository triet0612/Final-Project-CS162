#include "GeneralPersonalInfo.h"

GeneralPersonalInfo::GeneralPersonalInfo(string name, string uName, string pWord, string phone, string mail, string gender, Date dob) {
    this->name = name;
    this->username = uName;
    this->pass = pWord;
    this->phone = phone;
    this->gender = gender;
    this->mail = mail;
    this->dob = dob;
}

GeneralPersonalInfo::GeneralPersonalInfo() {
    name = "";
    username = "";
    pass = "";
    mail = "";
    phone = "";
    gender = "Male";
    dob = Date();
}

GeneralPersonalInfo GeneralPersonalInfo::addUsername(string uName) {
    username = uName;
    return *this;
}

GeneralPersonalInfo GeneralPersonalInfo::addPassword(string pWord) {
    pass = pWord;
    return *this;
}

bool GeneralPersonalInfo::checkDefault() {
    GeneralPersonalInfo nullGPI;
    return *this == nullGPI;
}

void GeneralPersonalInfo::getLoginData() {
    cin.ignore();
    std::cout << "Enter your username: \n";
    getline(cin, username);
    std::cout << "Enter your password: \n";
    getline(cin, pass);
}
