#pragma once
#include "PeopleController.h"
#include "Schoolyear_controller.h"
#include "Student.h"
#include "Table.h"
#include <string>
#include <fstream>

class StudentController : public PeopleController {
private:
	sll<Student> list;
public:
    StudentController();

    ~StudentController();

    void regProc() override;

    void loadData();

    void exportData();

    void getCur(string& yearname, string& semester);;

    bool loginProc(string username, string password) override;

    //--
    int chooseOptions(Table& table);;

    void setupOptionsTable(Table& table);

    int inputTypeProc();

    //----------------
    void setupProfileTable(Table& table);

    void viewProfileProc();


    //----------------
    void setupVerifPassInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos);

    void setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, string& res, bool& isOver);

    void setValidPosition(COORD c, int x, int y, int& cur, bool inTxt, bool inBtn, sll<pair<int, int> >& pos, ConsoleGraphics& graphics);;

    void renderInputProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver);

    void renderCaution();

    void renderAccept();

    string inputVerifPassProc(bool& isCancel);

    bool verifPassProc();

    //-----
    void setupChangePassInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos);

    void setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, pair<string, string>& res, bool& isOver);

    pair<string, string> inputChangePassProc(bool& isCancel);

    void renderMismatchCaution();

    void changePassProc();

    //--

    void viewScores(string stuID);

    //--

    void enrollCourseProc();

    void proc();;
};