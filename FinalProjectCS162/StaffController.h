#pragma once
#include "PeopleController.h"
#include "Staff.h"
//#include "CourseController.h"
//#include "SemesterController.h"
//#include "SchoolYearController.h"
class StaffController : public PeopleController
{
private:
    //SchoolYearController schoolYears;
    sll<Staff> list;
public:
    void regProc() override {
        //Staff staff;
        //system("cls");
        //staff.getLoginData();
        //GeneralPersonalInfo ans = findByUsername(staff);
        //if (ans.checkDefault()) {
        //    list.push_back(staff);
        //}
        //else {
        //    cout << "Username is already exist" << endl;
        //}

        //staff.getGeneralData();

        //list.push_back(staff);
    };

    bool loginProc() override {
        string username, password;
        pair<string, string> ans = inputLoginProc();
        username = ans.first;
        password = ans.second;

    }

    void showOptions() {
        system("cls");
        cout << "0. Back" << endl;
        cout << "1. Create School Year" << endl;
        cout << "2. Show All School Years" << endl;
    };

    //void createSchoolYear() {
    //    system("cls");
    //    cin.ignore();
    //    cout << "Enter name of school year: ";
    //    string name;
    //    getline(cin, name);
    //    SchoolYear schoolYear(name);
    //    schoolYears.addSchoolYear(name);
    //    cout << "School year is created" << endl;
    //    cin.get();
    //};
    //void showAllSchoolYears() {
    //    system("cls");
    //    cout << "School years: \n";
    //    const auto& list = schoolYears.getSchoolYears();
    //    size_t sz = schoolYears.getSize();
    //    cout << "Total: " << sz << "\n\n";
    //    for (int i = 0; i < sz; i++)
    //    {
    //        cout << i << ". " << list[i].getName() << "\n";
    //    }
    //    cin.get();
    //    cin.get();

    //};

    //void proc() {
    //    int option;
    //    while (true) {
    //        showOptions();
    //        cout << "Enter option: ";
    //        cin >> option;
    //        switch (option) {
    //        case 0:
    //            return;
    //        case 1:
    //            createSchoolYear();
    //            break;
    //        case 2:
    //            showAllSchoolYears();
    //            break;
    //        default:
    //            cout << "Invalid option" << endl;
    //            cin.get();
    //            cin.get();
    //            break;
    //        }
    //    }

    //};


};
