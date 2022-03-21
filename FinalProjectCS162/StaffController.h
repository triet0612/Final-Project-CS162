#pragma once
#include "PeopleController.h"
#include "Staff.h"
#include "Table.h"
#include <fstream>
//#include "CourseController.h"
//#include "SemesterController.h"
//#include "SchoolYearController.h"
class StaffController : public PeopleController
{
private:
    //SchoolYearController schoolYears;
    sll<Staff> list;
public:
    StaffController() {
        loadData();
    }

    void loadData() {
        ifstream ifs("Data/Staff_account.txt");
        if (!ifs.is_open()) return;
        string tmp;
        getline(ifs, tmp);
        while (!ifs.eof()) {

            Staff s;
            getline(ifs, tmp, ','); s.addUsername(tmp);
            if (tmp == "") break;
            getline(ifs, tmp, ','); s.addPassword(tmp);
            getline(ifs, tmp, ','); s.name = tmp;
            getline(ifs, tmp, ','); s.dob = tmp;
            getline(ifs, tmp, ','); s.isMale = tmp;
            getline(ifs, tmp, ','); s.phone = tmp;
            getline(ifs, tmp); s.mail = tmp;
            list.push_back(s);
        }
    }

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

    bool loginProc(string username, string password) override {
        Staff ans = list.find([&](Staff s) {return s.username == username && s.pass == password; });
        if (ans.username == "" && ans.pass == "") return false;
        return true;
    }

    int chooseOptions(Table& table) {
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

    void setupOptionsTable(Table& table) {
        system("cls");
        table = Table(0, 0, 4);

        table.addTitleRow_back(30);
        table.getRow(0).addText("WHAT DO YOU WANT ?");
        table.addRow_back("Create School Year");
        table.addRow_back("Show All School Year");
        table.addRow_back("Get me out the here");

        table.setDefaultType();
        table.render();

        table.setCursorInside();
    }

    int inputTypeProc() {
        int type = 0;
        Table table;
        setupOptionsTable(table);
        table.update({ -32, 0 }, [&](Table& table) {type = chooseOptions(table); });
        return type;
    }

    void createSchoolYear() {
        //system("cls");
        //cin.ignore();
        //cout << "Enter name of school year: ";
        //string name;
        //getline(cin, name);
        //SchoolYear schoolYear(name);
        //schoolYears.addSchoolYear(name);
        //cout << "School year is created" << endl;
        //cin.get();
    };

    void showAllSchoolYears() {
        //system("cls");
        //cout << "School years: \n";
        //const auto& list = schoolYears.getSchoolYears();
        //size_t sz = schoolYears.getSize();
        //cout << "Total: " << sz << "\n\n";
        //for (int i = 0; i < sz; i++)
        //{
        //    cout << i << ". " << list[i].getName() << "\n";
        //}
        //cin.get();
        //cin.get();

    };

    void proc() {
        int option;
        while (true) {
            option = inputTypeProc();
            switch (option) {
            case 1:
                createSchoolYear();
                break;
            case 2:
                showAllSchoolYears();
                break;
            default:
                return;
            }
        }

    };


};
